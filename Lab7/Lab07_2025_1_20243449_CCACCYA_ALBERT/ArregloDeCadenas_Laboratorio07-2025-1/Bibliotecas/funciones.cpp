//
// Created by aml on 5/06/2026.
//

#include "funciones.h"


void modificarCadena(char * str, int cant_caract) {
    for (int i=0; str[i]; i++) {
        str[i]-=(str[i]>='a' and str[i]<='z')*('a'-'A');
    }
}

char * leerCadenaTexto( ifstream & input,char c) {
    char* str,buffer[100]{};
    int cantCaract;
    input.getline(buffer,50,c);
    if (input.eof()) return nullptr;
    cantCaract=strlen(buffer);
    modificarCadena(buffer,cantCaract);
    str=new char[cantCaract+1];
    strcpy(str,buffer);
    return str;
}

void lecturaEmpresasRegistradas(const char * file_name, int * dni, char ** nombres, char * *distrito, int& cant_person) {
    ifstream input; leerArchivo(file_name, input);
    // 77763722,farfan salazar margot,La Molina
    int dniPer;
    char c;
    while (true) {
        input>>dniPer;
        if (input.eof()) break;
        input>>c;
        nombres[cant_person]=leerCadenaTexto(input,',');
        distrito[cant_person]=leerCadenaTexto(input,'\n');
        dni[cant_person]=dniPer;
        cant_person++;
    }
}

int buquedaDni(int dni_per, int * dni, int cant_person) {
    for (int i=0; i<cant_person; i++) {
        if (dni[i]==dni_per) {
            return i;
        }
    }
    return -1;
}


bool verificaSiEstaLaPlaca(char * listaDePlacas, char * placa) {
    int i=0;
    if (listaDePlacas==nullptr) return false;
    char placaExtraida[9];
    while (listaDePlacas[i]) {
        strncpy(placaExtraida,&listaDePlacas[i],8);
        placaExtraida[8]='\0';
        if (strcmp(placaExtraida,placa)==0) return true;
        i=i+9;
    }
    return false;
}


void lecturaPlacasRegistradas(const char *file_name, char **placas, int *dni, int cant_person) {
    ifstream input; leerArchivo(file_name, input);
    // 90467829
    int dniPer,i;
    char *placaExtraida;
    while (true) {
        input>>dniPer;
        if (input.eof()) break;
        input>>ws;
        placaExtraida=leerCadenaTexto(input,'\n');
        i=buquedaDni(dniPer,dni,cant_person);
        if (i==-1) continue;
        if (not verificaSiEstaLaPlaca(placas[i],placaExtraida)) {
            if (placas[i]== nullptr) {
                placas[i]=new char[200]{};
                strcpy(placas[i],placaExtraida);
            }
            else {
                strcat(placas[i],"/");
                strcat(placas[i],placaExtraida);
            }
        }
        delete [] placaExtraida;
    }
}
void reportPlacasRegistradas(const char * file_name, char ** placas, int * dni, int cant_person,char ** nombres,char * * distrito) {
    ofstream output; escribirArchivo(file_name, output);
    output<<"PLACAS REGISTRADAS POR REPRESENTANTE LEGAL"<<endl;
    generarSimbolos(output,'=');
    output<<setw(6)<<"DNI"<<setw(23)<<"NOMBRE"<<setw(32)<<"DISTRITO"<<setw(38)<<"PLACAS"<<endl;
    generarSimbolos(output,'-');
    for (int i=0; i<cant_person; i++) {
        int contadorNombre=strlen(nombres[i]),contadorDistrito=strlen(distrito[i]);
        output<<setfill('0')<<setw(8)<<dni[i]<<setfill(' ')<<setw(5)<<""<<nombres[i]<<setw(ANCHONOMBRE-contadorNombre)<<""<<distrito[i]<<setw(ANCHODISTRI-contadorDistrito)<<""<<placas[i]<<endl;
    }
}

char * asignarCadena(char * codigo_infraccion) {
    char *str;
    str=new char[strlen(codigo_infraccion)+1];
    strcpy(str,codigo_infraccion);
    return str;
}

void lecturaTablaInfrac(const char * file_name, char ** codInfracc, double * multaInfrac, int &cantInfra) {
    // M1011,567.15,Conducir vehiculos sin parachoque.
    ifstream input; leerArchivo(file_name, input);
    char c;
    while (true) {
        char *codigoInfraccion;
        codigoInfraccion=leerCadenaTexto(input,',');
        if (input.eof()) break;
        input>>multaInfrac[cantInfra]>>c;
        input.ignore(200,'\n');
        codInfracc[cantInfra]=codigoInfraccion;
        cantInfra++;
    }

}
void reportTablaInfrac(const char * file_name, char ** codInfracc, double * multa_infrac, int cant_infra) {
    ofstream output; escribirArchivo(file_name, output);
    output<<"TABLA DE INFRACCIONES"<<endl;
    generarSimbolos(output,'=');
    output<<setw(6)<<"CODIGO"<<setw(9)<<"MULTA"<<endl;
    output<<fixed<<setprecision(2);
    generarSimbolos(output,'-');
    for (int i=0; i<cant_infra; i++) {
        output<<setw(8)<<left<<codInfracc[i]<<right<<setw(8)<<multa_infrac[i]<<endl;
    }
}

int buscarPlaca(char * placa_infrac, int cant_person, char ** placas) {
    for (int i=0; i<cant_person; i++) {
        if (verificaSiEstaLaPlaca(placas[i],placa_infrac)) return i;
    }
    return -1;
}

int buscarInfraccion(char ** cod_infracc, char * cod_infraccion, int cant_infra) {
    for (int i=0; i<cant_infra; i++) {
        if (strcmp(cod_infracc[i],cod_infraccion)==0) return i;
    }
    return -1;
}

void lecturaInfracCometidas(const char * file_name, int * fechaInfraAntig, int * fecha_pag_rec, int * cant_faltas,
                            double * pag_lev, double * pag_grav, double * pag_muy_grav,
                            int cant_person, char ** cod_infracc, int cant_infra,  double * multa_infrac,char**placas) {
    ifstream input; leerArchivo(file_name, input);
    // 1/12/2020,G760-721,G2022,N
    // 23/7/2023,P474-593,G2060,P,22/8/2023
    int fechaInfrac,i,j;
    char *codInfraccion,*placaInfrac,pago,c;
    while (true) {
        int fechaPago=0;
        fechaInfrac=leerFecha(input);
        if (input.eof()) break;
        input>>c;
        placaInfrac=leerCadenaTexto(input,',');
        codInfraccion=leerCadenaTexto(input,',');
        input.get(pago);
        if (pago=='P') {
            input>>c;
            fechaPago=leerFecha(input);
        }
        i=buscarPlaca(placaInfrac,cant_person,placas);
        j=buscarInfraccion(cod_infracc,codInfraccion,cant_infra);
        if (i==-1 or j==-1) continue;
        if (fechaInfraAntig[i]>fechaInfrac) fechaInfraAntig[i]=fechaInfrac;
        if (fecha_pag_rec[i]<fechaPago) fecha_pag_rec[i]=fechaPago;
        if (pago=='P') {
            if (codInfraccion[0]=='L')  pag_lev[i]+=multa_infrac[j];
            else if (codInfraccion[0]=='G')  pag_grav[i]+=multa_infrac[j];
            else if (codInfraccion[0]=='M')  pag_muy_grav[i]+=multa_infrac[j];
        }
        else cant_faltas[i]++;
    }
}

void swapInt(int &i, int &i1) {
    int temp=i;
    i=i1;
    i1=temp;
}

void swapDouble(double &x, double &x1) {
    double temp=x;
    x=x1;
    x1=temp;
}


void swapStr(char *&a, char * &b) {
    char *temp=a;
    a=b;
    b=temp;
}

void ordenarArreglosFechaInfracc(int * dni, char ** nombres, char ** distrito, char ** placas,
                                 int * fecha_infra_antig, int * fecha_pag_rec, double * pag_lev, double * pag_grav,
                                 double * pag_muy_grav, int * cant_faltas, int cant_person) {
    for (int i=0; i<cant_person-1; i++) {
        for (int j=i+1; j<cant_person; j++) {
            if (fecha_infra_antig[i]>fecha_infra_antig[j] or (fecha_infra_antig[i]==fecha_infra_antig[j] and strcmp(nombres[i],nombres[j])>0)) {
                swapInt(dni[i],dni[j]);
                swapInt(fecha_infra_antig[i],fecha_infra_antig[j]);
                swapInt(fecha_pag_rec[i],fecha_pag_rec[j]);
                swapInt(cant_faltas[i],cant_faltas[j]);
                swapDouble(pag_lev[i],pag_lev[j]);
                swapDouble(pag_grav[i],pag_grav[j]);
                swapDouble(pag_muy_grav[i],pag_muy_grav[j]);
                swapStr(distrito[i],distrito[j]);
                swapStr(nombres[i],nombres[j]);
                swapStr(placas[i],placas[j]);
            }
        }
    }
}

void impresionFecha(int fecha,ofstream& output) {
    int dd,mm,aa;
    char c='/';
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<c<<setw(2)<<mm<<c<<aa<<setfill(' ');
}

void reporteFinal(const char * file_name, int * dni, char ** nombres, char ** distrito, char ** placas,
                  int * fecha_infra_antig, int * fecha_pag_rec, double * pag_lev, double * pag_grav, double * pag_muy_grav,
                  int * cant_faltas, int cant_person) {
    ofstream output; escribirArchivo(file_name, output);
    output<<"MINISTERIO DE TRANSPORTES"<<endl;
    output<<"LISTADO DE INFRACCIONES POR EMPRESA"<<endl;
    generarSimbolos(output,'=');
    output<<setw(50)<<"EMPRESA"<<setw(93)<<"FECHA INF."<<setw(16)<<"FECHA PAGO"<<setw(25)<<"TOTAL PAGADO"<<setw(17)<<"CANTIDAD"<<endl;
    output<<setw(6)<<"No."<<setw(6)<<"DNI"<<setw(11)<<"NOMBRE"<<setw(42)<<"DISTRITO"<<setw(25)<<"PLACAS"<<setw(53)<<"MAS ANTIGUA"<<setw(17)<<"MAS RECIENTE"<<setw(9)<<"LEVES"<<setw(9)<<"GRAVES"<<setw(14)<<"MUY GRAVES"<<setw(10)<<"DE FALTAS"<<endl;
    generarSimbolos(output,'=');
    output<<fixed<<setprecision(2);
    int totalFaltas=0;
    double totalLeves=0,totalGraves=0,totalMuyGraves=0;
    for (int i=0; i<cant_person; i++) {
        int contadorNombre=strlen(nombres[i]),contadorDistrito=strlen(distrito[i]),contadorPlacas=strlen(placas[i]);
        output<<setw(4)<<i+1<<setw(3)<<left<<")"<<setw(10)<<dni[i]<<right<<nombres[i]<<setw(ANCHONOMBRE-contadorNombre)<<" "<<distrito[i]<<setw(ANCHODISTRI-contadorDistrito)<<" "<<placas[i]<<setw(50-contadorPlacas)<<" ";
        impresionFecha(fecha_infra_antig[i],output);
        output<<setw(5)<<" ";
        if (fecha_pag_rec[i]>0) impresionFecha(fecha_pag_rec[i],output);
        else output<<fecha_pag_rec[i];
        output<<setw(10)<<pag_lev[i]<<setw(10)<<pag_grav[i]<<setw(12)<<pag_muy_grav[i]<<setw(7)<<cant_faltas[i]<<endl;
        totalFaltas+=cant_faltas[i];
        totalLeves+=pag_lev[i];
        totalGraves+=pag_grav[i];
        totalMuyGraves+=pag_muy_grav[i];
    }
    generarSimbolos(output,'=');
    output<<setw(158)<<"TOTALES:"<<setw(11)<<totalLeves<<setw(10)<<totalGraves<<setw(12)<<totalMuyGraves<<setw(8)<<totalFaltas<<endl;
    generarSimbolos(output,'=');
}
void leerArchivo(const char*file_name, ifstream&file) {
    file.open(file_name, ios::in);
    if (not file.is_open()) {
        cout<<"Error al abrir el archivo: "<<file_name<<endl;
        exit(1);
    }
}
void escribirArchivo(const char*file_name, ofstream&file) {
    file.open(file_name, ios::out);
    if (not file.is_open()) {
        cout<<"Error al abrir el archivo: "<<file_name<<endl;
        exit(1);
    }
}
void generarSimbolos(ofstream&output,char c) {
    for (int i=0; i<ANCHOREPORT;i++) output.put(c);
    output.put('\n');
}

int leerFecha(ifstream &input) {
    int dd,mm,aa;
    char c;
    input>>dd;
    if (input.eof()) return -1;
    input>>c>>mm>>c>>aa;
    return dd+mm*100+aa*10000;
}