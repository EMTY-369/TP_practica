//
// Created by User on 7/06/2026.
//

#include "Funciones.hpp"

void imprimir_titulo_encabezado( ofstream & output) {

    centrear("MINISTERIO DE TRANSPORTES", ANCHO_REPORTE, output);
    output<<endl;
    centrear("LISTADO DE INFRACCIONES POR EMPRESA", ANCHO_REPORTE, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    imprimir_linea(6,' ',false, output);
    centrear("EMPRESA", 10+45+30+50, output);
    centrear("FECHA INF.", 16, output);
    centrear("FECHA PAGO", 16, output);
    centrear("TOTAL PAGADO", 30, output);
    centrear("CANTIDAD", 15, output);
    output<<endl;
    centrear("No.", 6, output);
    output<<left<<setw(10)<<"DNI"<<setw(45)<<"NOMBRE"<<setw(30)<<"DISTRITO"<<setw(50)<<"PLACAS"<<right;
    centrear("MAS ANTIGUA", 16, output);
    centrear("MAS RECIENTE", 16, output);
    centrear("LEVE", 10, output);
    centrear("GRAVE", 10, output);
    centrear("MUY GRAVES", 10, output);
    centrear("DE FALTAS", 15, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
}


void imprimir_fecha(int fecha, ofstream & output) {
    int dd, mm, aa;
    aa = fecha / 10000;
    fecha = fecha % 10000;
    mm = fecha / 100;
    dd = fecha % 100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void imprimir_reporte(const char * file_name, int *dnis_empresas, char ** nombres, char ** distritos, char ** placas,
                      int * infrac_mas_antiguas, int * pagos_mas_recientes, int * cants_faltas, double * pagos_leves,
                      double * pagos_graves, double * pagos_muy_graves, int n_dnis) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output.precision(2);

    imprimir_titulo_encabezado(output);
    double total_leves=0, total_graves=0, total_muy_graves=0;
    int total_faltas=0;
    for (int i = 0; i < n_dnis; i++) {
        output<<setw(3)<<i+1<<")  ";
        output<<left<<setw(10)<<dnis_empresas[i]<<setw(45)<<nombres[i]<<setw(30)<<distritos[i]<<setw(50)<<placas[i]<<right;
        imprimir_linea(3,' ',false, output);
        imprimir_fecha(infrac_mas_antiguas[i], output);
        imprimir_linea(6,' ',false, output);
        imprimir_fecha(pagos_mas_recientes[i], output);
        output<<setw(11)<<pagos_leves[i]<<setw(10)<<pagos_graves[i]<<setw(10)<<pagos_muy_graves[i];
        output<<setw(10)<<cants_faltas[i]<<endl;
        total_faltas+=cants_faltas[i];
        total_leves+=pagos_leves[i];
        total_graves+=pagos_graves[i];
        total_muy_graves+=pagos_muy_graves[i];
    }
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<setw(171)<<"TOTALES: "<<setw(10)<<total_leves<<setw(10)<<total_graves<<setw(10)<<total_muy_graves;
    output<<setw(10)<<total_faltas<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);

    output.close();
}

void swap_double(double &value1, double &value2) {
    double aux=value1;
    value1=value2;
    value2=aux;
}

void swap_int(int &value1, int &value2) {
    int aux=value1;
    value1=value2;
    value2=aux;
}

void swap_str(char *&value1, char *&value2) {
    char *aux=value1;
    value1=value2;
    value2=aux;
}

void ordenar_arreglos(int * dnis_empresas, char ** nombres, char ** distritos, char ** placas, int * infrac_mas_antiguas,
                      int * pagos_mas_recientes, int * cants_faltas, double * pagos_leves, double * pagos_graves,
                      double * pagos_muy_graves, int n_dnis) {
    for (int i = 0; i < n_dnis - 1 ; i++) {
        for (int j = i+1; j < n_dnis; j++) {
            if (infrac_mas_antiguas[i]>infrac_mas_antiguas[j] or (infrac_mas_antiguas[i]==infrac_mas_antiguas[j]
                and strcmp(nombres[i], nombres[j])>0)) {
                swap_int(dnis_empresas[i], dnis_empresas[j]);
                swap_str(nombres[i], nombres[j]);
                swap_str(distritos[i], distritos[j]);
                swap_str(placas[i], placas[j]);
                swap_int(infrac_mas_antiguas[i], infrac_mas_antiguas[j]);
                swap_int(pagos_mas_recientes[i], pagos_mas_recientes[j]);
                swap_int(cants_faltas[i], cants_faltas[j]);
                swap_double(pagos_leves[i], pagos_leves[j]);
                swap_double(pagos_graves[i], pagos_graves[j]);
                swap_double(pagos_muy_graves[i], pagos_muy_graves[j]);
            }
        }
    }
}


int leer_fecha( ifstream & input) {
    int dd, mm, aa;
    char c;
    input>>dd;
    if (input.eof()) return NO_ENCONTRADO;
    input>>c>>mm>>c>>aa;
    return aa*10000 + mm*100 + dd;
}

bool verificaSiEstaLaPlaca(char * placas, char * placa_leido) {
    char placa_extraida[9]{};
    int j=0;
    for (int i = 0; i < strlen(placas) + 1; i++) {
        if (placas[i]=='/' or placas[i]=='\0') {
            j=0;
            if (strcmp(placa_extraida, placa_leido)==0) return true;
            continue;
        }
        placa_extraida[j] = placas[i];
        j++;
    }
    return (false);
    // int i=0;
    // if (placas==nullptr) return false;
    // char placaExtraida[9];
    // while (placas[i]) {
    //     strncpy(placaExtraida,&placas[i],8);
    //     placaExtraida[8]='\0';
    //     if (strcmp(placaExtraida,placa_leido)==0) return true;
    //     i=i+9;
    // }
    // return false;
}

int encontrar_placa(char ** placas, int n_dnis, char * placa_leido) {
    for (int i = 0; i < n_dnis; i++) {
        if (verificaSiEstaLaPlaca(placas[i], placa_leido)) return i;
    }
    return NO_ENCONTRADO;
}

int buscar_cadena(char * cadena, char ** arr, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i], cadena) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void cargar_infracciones_cometidas(const char * file_name, char ** placas, int n_dnis, char ** cods_infrac, double * multas_infrac,
                                   int n_infrac, int * infrac_mas_antiguas, int * pagos_mas_recientes, int * cants_faltas,
                                   double * pagos_leves, double * pagos_graves, double * pagos_muy_graves) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int fecha_infrac, fecha_pago, pos_placa, pos_infrac, i=1;
    char c, *placa_leido, cod_infrac_leido[7]{};
    placa_leido = new char[9]{};
    while (true) {
        fecha_infrac = leer_fecha(input);
        if (input.eof()) break;
        input.get();
        input.getline(placa_leido, 9 , ',');
        input.getline(cod_infrac_leido, 7 , ',');
        input.get(c);
        if (c=='P') {
            input.get();
            fecha_pago = leer_fecha(input);
        } else fecha_pago = 0;
        pos_placa=encontrar_placa(placas, n_dnis, placa_leido);
        if (pos_placa!=NO_ENCONTRADO) {
            pos_infrac=buscar_cadena(cod_infrac_leido, cods_infrac, n_infrac);
            if (pos_infrac!=NO_ENCONTRADO) {
                if (infrac_mas_antiguas[pos_placa]==0 or fecha_infrac<infrac_mas_antiguas[pos_placa]) {infrac_mas_antiguas[pos_placa]=fecha_infrac;}
                if (fecha_pago != 0 and (pagos_mas_recientes[pos_placa]==0 or pagos_mas_recientes[pos_placa]<fecha_pago)) {pagos_mas_recientes[pos_placa]=fecha_pago;}
                if (c=='P') {
                    if (cod_infrac_leido[0]=='L') {pagos_leves[pos_placa]+=multas_infrac[pos_infrac];}
                    if (cod_infrac_leido[0]=='M') {pagos_muy_graves[pos_placa]+=multas_infrac[pos_infrac];}
                    if (cod_infrac_leido[0]=='G') {pagos_graves[pos_placa]+=multas_infrac[pos_infrac];}
                }
                cants_faltas[pos_placa]++;
            } else cout << i<< endl;
        } else cout << i<< endl;
    }
    input.close();
}

void prueba_carga_infracciones(const char * file_name, char ** cods_infrac, double * multas_infrac, int n_infrac) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output<<setprecision(2);

    centrear("PRUEBA DE CARGA DE LAS INFRACCIONES", 100, output);
    output<<endl;
    imprimir_linea(100, '=', true, output);
    centrear("CODIGOS INFRACCIONES", 50, output);
    centrear("COSTO MULTAS", 50, output);
    output<<endl;
    imprimir_linea(100, '-', true, output);
    for (int i = 0; i < n_infrac; i++) {
        output<<cods_infrac[i]<<setw(60)<<multas_infrac[i]<<endl<<right;
    }
    output.close();
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.get();
    input>>ws;
    return dato;
}

void cargar_infracciones(const char * file_name, char **cods_infrac, double * multas_infrac, int &n_infrac) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    char *cod_infra;
    while (true) {
        cod_infra=leer_cadena(input, ',');
        if (input.eof()) {
            delete cod_infra;
            break;
        }
        cods_infrac[n_infrac] = cod_infra;
        multas_infrac[n_infrac] = leer_double(input);
        input.ignore(300, '\n');
        n_infrac++;
    }
    input.close();
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"Error al abrir el archivo escritura: "<<file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output<<endl;
}

void centrear(const char *nombre, int espacio, ofstream & output) {
    int n = strlen(nombre);
    output<<setw((espacio+n)/2)<<nombre;
    imprimir_linea(espacio - (espacio+n)/2, ' ', false, output);
}

void prueba_carga_empresas_placas(const char * file_name, int * dnis_empresas, char ** nombres, char ** distritos, char ** placas,
                                  int n_dnis) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<setw((ANCHO_REPORTE+40)/2)<<"PRUEBA DE CARGA DE LAS EMPRESAS Y PLACAS"<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    centrear("DNI", 20, output);
    centrear("NOMBRE", 50, output);
    centrear("DISTRITO", 30, output);
    centrear("PLACAS", 60, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_dnis; i++) {
        output<<left<<setw(20)<<dnis_empresas[i]<<setw(50)<<nombres[i];
        output<<setw(30)<<distritos[i]<<setw(60)<<placas[i]<<endl<<right;
    }
    output.close();
}

int buscar_valor(int valor, int * arr, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) return i;
    }
    return NO_ENCONTRADO;
}

void cargar_placas(const char * file_name, char ** placas, int * dnis_empresas, int n_dnis) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dni_leido, pos_dni;

    while (true) {
        dni_leido = leer_entero(input);
        if (input.eof()) break;
        char placa[9]{};
        input>>placa;
        pos_dni=buscar_valor(dni_leido, dnis_empresas, n_dnis);
        if (pos_dni != NO_ENCONTRADO) {
            if (strlen(placas[pos_dni]) == 0){
                strcpy(placas[pos_dni], placa);
                // cout << placas[pos_dni] << endl;
            } else {
                strcat(placas[pos_dni], "/");
                strcat(placas[pos_dni], placa);
                // cout << placas[pos_dni] << endl;
            }
        }
    }
    input.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: "<<file_name << endl;
        exit(1);
    }
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[MAX_TAM_CADENA]{}, *cadena;
    input.getline(buffer, MAX_TAM_CADENA, del);
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

int leer_entero( ifstream & input) {
    int dato;
    input>>dato;
    input.get();
    input>>ws;
    return dato;
}

void modificar_cadena(char * cadena) {
    for (int i = 0; cadena[i]; i++) {
        if (cadena[i]<='z' and cadena[i]>='a') cadena[i]-='a'-'A';
    }
}

void cargar_empresas_registradas(const char * file_name, int * dnis_empresas, char ** nombres, char ** distritos, int &n_dnis) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dni;
    while (true) {
        dni=leer_entero(input);
        if (input.eof()) break;
        nombres[n_dnis] = leer_cadena(input, ',');
        modificar_cadena(nombres[n_dnis]);
        distritos[n_dnis] = leer_cadena(input, '\n');
        modificar_cadena(distritos[n_dnis]);
        // cout<<left<<setw(50)<<nombres[n_dnis]<<distritos[n_dnis]<<endl<<right;
        dnis_empresas[n_dnis] = dni;
        n_dnis++;
    }
    input.close();
}
