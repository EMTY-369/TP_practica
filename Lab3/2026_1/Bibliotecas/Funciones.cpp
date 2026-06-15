//
// Created by User on 18/05/2026.
//

#include "Funciones.hpp"

void abrir_lectura(const char *file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de lectura" << file_name << endl;
        exit(1);
    }
}

void abrir_escritura(const char *file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"Error al abrir el archivo de escritura" << file_name << endl;
        exit(1);
    }
}

void imprimir_titulo( ofstream & output) {
    output<<setw((ANCHO_REPORTE+29)/2)<<"CLINICA DE URGENCIAS TP_SALUD"<<endl;
    output<<setw((ANCHO_REPORTE+22)/2)<<"REGISTRO DE ATENCIONES"<<endl;
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i=0; i<n; i++) output.put(c);
    output<<endl;
}

void espacios(int n, ofstream & output) {
    for (int i=0; i<n; i++) output.put(' ');
}

void imprimir_nombre( ifstream & input, int espacio,char del, ofstream & output) {
    char c;
    int n=0;
    input>>ws;
    while (true) {
        input.get(c);
        if (c == del) break;
        if (c=='/' or c=='-') c=' ';
        if (c>='a' and c<='z') c-='a'-'A';
        output.put(c);
        n++;
    }
    espacios(espacio-n,output);
}

void imprimir_encabezado(int id, int i, ifstream &input, ofstream & output, int &edad) {
    char genero;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<"PACIENTE No. "<<setfill('0')<<setw(2)<<i<<setfill(' ')<<endl;
    output<<"ID: "<<id<<setw(14)<<"NOMBRE: ";
    imprimir_nombre(input,30,' ',output);
    input>>ws>>genero>>edad;
    output<<"SEXO: "<<left;
    if (genero == 'M') output<<setw(14)<<"MASCULINO";
    if (genero == 'F') output<<setw(14)<<"FEMENINO";
    output<<right<<"EDAD: "<<setw(4)<<edad<<endl;
    output<<"ATENCIONES REGISTRADAS: "<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

int leer_fecha( ifstream &input) {
    int aa,mm,dd;
    char c;
    input>>dd;
    if (input.eof()) return NO_ENCONTRADO;
    input>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void imprimir_titulos_tablas( ofstream & output) {
    output<<left<<setw(6)<<"No."<<setw(15)<<"FECHA"<<setw(20)<<"FREC. CARDIACA"<<setw(17)<<"P.SISTOLICA";
    output<<setw(18)<<"P.DIASTOLICA"<<setw(14)<<"TEMPERATURA"<<setw(20)<<"SAT. DE OXIGENO";
    output<<setw(16)<<"DURACION"<<setw(18)<<"COSTO ATENCION"<<endl<<right;
}

void imprimir_fecha(int fecha, ofstream & output) {
    int mm,dd,aa;
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

int leer_tiempo( ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora, minuto, segundo;
    hora = tiempo/3600;
    tiempo %= 3600;
    minuto = tiempo/60;
    segundo = tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

void imprimir_calcular_costo_atencion(int edad, double &costo_atencion, int duracion, double costo_hora, ofstream &output) {
    if (edad<18) costo_atencion=duracion/3600.0*costo_hora*0.95;
    if (edad>=18 and edad<=64) costo_atencion=duracion/3600.0*costo_hora;
    if (edad>64) costo_atencion=duracion/3600.0*costo_hora*0.82;
    output<<setw(16)<<costo_atencion<<endl;
}

void buscar_imprimir_duracion_costo(ifstream &input, int fecha_aten, double &costo_atencion, int id, ofstream & output, int edad) {
    input.clear();
    input.seekg (0, ios::beg);
    int fecha_leido, hora_inicio, hora_fin, part1, part2, part3, id_leido;
    char c;
    double costo_hora;
    bool encontrado=false;
    while (true) {
        fecha_leido=leer_fecha(input);
        if (fecha_leido==NO_ENCONTRADO or input.eof()) break;
        if (fecha_leido==fecha_aten) {
            while (true) {
                hora_inicio=leer_tiempo(input);
                input>>part1>>c>>part2>>c>>part3;
                hora_fin=leer_tiempo(input);
                input>>costo_hora;
                id_leido=part1*1000000+part2*10000+part3;
                if (id==id_leido) {
                    encontrado=true;
                    espacios(11,output);
                    imprimir_tiempo(hora_fin-hora_inicio,output);
                    imprimir_calcular_costo_atencion(edad,costo_atencion,hora_fin-hora_inicio, costo_hora, output);
                    break;
                }
                input.get(c);
                if (c=='\n') break;
            }
            break;
        } else {
            input.ignore(800,'\n');
        }
    }
    if (not encontrado) {
        espacios(6,output);
        output<<"Error, no se guardo la atencion"<<endl;
    }
}

void determinar_amyor_menor(int id, double temp, int &id_temp_mayor, int &id_temp_menor, double &temperatura_mayor,
                           double &temperatura_menor) {
    if (temperatura_mayor==0 or temperatura_mayor<temp) {
        id_temp_mayor=id;
        temperatura_mayor=temp;
    }
    if (temperatura_menor==0 or temperatura_menor>temp) {
        id_temp_menor=id;
        temperatura_menor=temp;
    }
}

void buscar_imprimir_triajes(ifstream &input_triaje, ifstream &input_atenciones, int id, int &id_temp_mayor, int &id_temp_menor,
                             double &temperatura_mayor, double &temperatura_menor, double &costo_total, ofstream & output, int edad) {
    input_triaje.clear();
    input_triaje.seekg (0, ios::beg);

    int fecha_aten, part1,part2,part3, id_leido,frecuencia,sistolica,diastolica,saturacion,i=0;
    double temp, costo_atencion, costo_paciente=0;
    bool encontrado=false;
    char c;
    while (true) {
        fecha_aten=leer_fecha(input_triaje);
        if (fecha_aten==NO_ENCONTRADO or input_triaje.eof()) break;
        input_triaje>>part1>>c>>part2>>c>>part3>>frecuencia>>sistolica>>diastolica>>temp>>saturacion;
        id_leido=part1*1000000+part2*10000+part3;
        if (id==id_leido) {
            i++;
            encontrado=true;
            if (i==1) imprimir_titulos_tablas(output);
            output<<setfill('0')<<setw(2)<<i<<setfill(' ')<<left<<setw(4)<<")"<<right;
            imprimir_fecha(fecha_aten,output);
            output<<setw(13)<<frecuencia<<setw(19)<<sistolica<<setw(17)<<diastolica<<setw(18)<<setprecision(1)<<temp<<setprecision(2);
            output<<setw(16)<<saturacion;
            buscar_imprimir_duracion_costo(input_atenciones,fecha_aten,costo_atencion,id,output, edad);
            costo_paciente+=costo_atencion;
            determinar_amyor_menor(id, temp, id_temp_mayor, id_temp_menor, temperatura_mayor, temperatura_menor);
        }
    }
    if (not encontrado) {
        output<<"EL PACIENTE NO VISITO LA CLINCIA TODAVÍA"<<endl;
    } else {
        costo_total+=costo_paciente;
        imprimir_linea(ANCHO_REPORTE, '-',output);
        output<<"GASTO TOTAL DEL PACIENTE:"<<setw(10)<<costo_paciente<<endl;
    }
}

void imprimir_resumen_final(double costo_total, int id_temp_mayor, int id_temp_menor, double temperatura_mayor, double temperatura_menor,
                            ofstream & output) {
    imprimir_linea(ANCHO_REPORTE, '=',output);
    output<<"RESUMEN:"<<endl;
    output<<"MAYOR TEMPERATURA REGISTRADA: "<<id_temp_mayor<<" - "<<temperatura_mayor<<endl;
    output<<"MENOR TEMPERATURA REGISTRADA: "<<id_temp_menor<<" - "<<temperatura_menor<<endl;
}

void imprimir_reporte(const char *file_pacientes, const char *file_triaje, const char *file_atenciones, const char *file_salida) {
    ifstream input_pacientes, input_triaje, input_atenciones;
    abrir_lectura(file_atenciones, input_atenciones);
    abrir_lectura(file_pacientes, input_pacientes);
    abrir_lectura(file_triaje, input_triaje);
    ofstream output;
    abrir_escritura(file_salida, output);

    output<<fixed;
    output.precision(2);
    int part1,part2,part3, i=0, edad, id_temp_mayor, id_temp_menor;;
    double temperatura_mayor=0, temperatura_menor=0,costo_total=0;
    char c;
    imprimir_titulo(output);
    while (true) {
        input_pacientes>>part1;
        if (input_pacientes.eof()) break;
        i++;
        input_pacientes>>c>>part2>>c>>part3;
        int id=part1*1000000+part2*10000+part3;
        imprimir_encabezado(id,i,input_pacientes,output, edad);
        buscar_imprimir_triajes(input_triaje,input_atenciones,id,id_temp_mayor,id_temp_menor,temperatura_mayor,temperatura_menor,
                                costo_total,output, edad);
    }
    imprimir_resumen_final(costo_total,id_temp_mayor,id_temp_menor,temperatura_mayor,temperatura_menor,output);
}
