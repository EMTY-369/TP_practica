//
// Created by User on 4/05/2026.
//

#include "Funciones.hpp"

void apertura_archivo_lectura(ifstream & input, const char * file_name) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: " << file_name << endl;
        exit(1);
    }
}

void cargar_pacientes(const char *file_name, int * ID_pacientes, int * edad_pacientes,
                      char * sexo_pacientes, int &n_pacientes) {
    ifstream input;
    apertura_archivo_lectura(input, file_name);
    int parte1, parte2, parte3;
    char c;
    while (1) {
        input>>parte1;
        if (input.eof()) break;
        input>>c>>parte2>>c>>parte3;
        ID_pacientes[n_pacientes] = parte1*1000000 + parte2*10000 + parte3;
        input>>ws;
        input.ignore(50, ' ');
        input>>ws>>sexo_pacientes[n_pacientes]>>edad_pacientes[n_pacientes];
        n_pacientes++;
    }
    input.close();
}

void apertura_archivo_escritura(ofstream & output, const char * file_name) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo de escritura: " << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    output<<endl;
}

void probar_carga_pacientes(const char * file_name, int * ID_pacientes, int * edad_pacientes, char * sexo_pacientes,
                            int n_pacientes) {
    ofstream output;
    apertura_archivo_escritura(output, file_name);

    output<<setw((ANCHO_REPORTE+32)/2)<<"PRUEBA DE CARGA DE LOS PACIENTES"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw(ANCHO_REPORTE/3)<<"ID"<<setw(ANCHO_REPORTE/3)<<"EDAD"<<setw(ANCHO_REPORTE/3)<<"SEXO"<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
    for (int i = 0; i < n_pacientes; i++) {
        output<<setw(ANCHO_REPORTE/3)<<ID_pacientes[i];
        output<<setw(ANCHO_REPORTE/3)<<edad_pacientes[i];
        output<<setw(ANCHO_REPORTE/3)<<sexo_pacientes[i];
        output<<endl;
    }
    output.close();
}

int leer_fecha(ifstream & input) {
    int aa,mm,dd;
    char c;
    input>>dd;
    if (input.eof()) return -1;
    input>>c>>mm>>c>>aa;
    return aa*10000 + mm*100 + dd;
}

void carga_triaje(const char * file_name, int * fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca,
                  int * sistolica, int * diastolica, double *temperatura, int * saturacion_oxigeno, int &n_triaje) {
    ifstream input;
    apertura_archivo_lectura(input, file_name);
    int fecha, parte1, parte2, parte3;
    char c;
    while (1) {
        fecha = leer_fecha(input);
        if (input.eof() or fecha == -1) break;
        input>>parte1>>c>>parte2>>c>>parte3;
        ID_triaje[n_triaje] = parte1*1000000 + parte2*10000 + parte3;
        input>>frecuencia_cardiaca[n_triaje]>>sistolica[n_triaje]>>diastolica[n_triaje];
        input>>temperatura[n_triaje]>>saturacion_oxigeno[n_triaje];
        fechas_atenciones[n_triaje]=fecha;
        n_triaje++;
    }
    input.close();
}

void imprimir_fecha(int fecha, ofstream & output) {
    int aa,mm,dd;
    aa=fecha/10000;
    fecha%=10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void probar_carga_triaje(const char *file_name, int *fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca,
                         int * sistolica, int * diastolica, double * temperatura, int * saturacion_oxigeno, int n_triaje) {
    ofstream output;
    apertura_archivo_escritura(output, file_name);

    output<<setw((ANCHO_REPORTE+30)/2)<<"PRUEBA DE CARGA DE LOS TRIAJES"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<left<<setw(ANCHO_REPORTE/7)<<"FECHAS DE LAS ATENCIONES"<<setw(ANCHO_REPORTE/7)<<"ID";
    output<<setw(ANCHO_REPORTE/7)<<"FRECUENCIA CARDIACA"<<setw(ANCHO_REPORTE/7)<<"PRESION SISTOLICA";
    output<<setw(ANCHO_REPORTE/7)<<"PRESION DIASTOLICA"<<setw(ANCHO_REPORTE/7)<<"TEMPERATURA";
    output<<setw(ANCHO_REPORTE/7)<<"SATURACION DE OXIGENO"<<right<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<fixed;
    for (int i = 0; i < n_triaje; i++) {
        imprimir_fecha(fechas_atenciones[i], output);
        output<<left<<setw(ANCHO_REPORTE/7 - 10)<<"";
        output<<setw(ANCHO_REPORTE/7)<<ID_triaje[i];
        output<<setw(ANCHO_REPORTE/7)<<frecuencia_cardiaca[i];
        output<<setw(ANCHO_REPORTE/7)<<sistolica[i];
        output<<setw(ANCHO_REPORTE/7)<<diastolica[i];
        output<<setw(ANCHO_REPORTE/7)<<setprecision(1)<<temperatura[i];
        output<<setw(ANCHO_REPORTE/7)<<saturacion_oxigeno[i];
        output<<endl<<right;
    }
    output.close();
}

void imprimir_titulo(ofstream & output) {
    output<<setw((ANCHO_REPORTE+29)/2)<<"CLINICA DE URGENCIAS TP_SALUD"<<endl;
    output<<setw((ANCHO_REPORTE+22)/2)<<"REGISTRO DE ATENCIONES"<<endl;
}

int leer_hora(ifstream & input) {
    int hora,minuto,segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void generar_reporte(const char * file_name_entrada, const char *file_name_salida, int * ID_pacientes, int * edad_pacientes,
                     char * sexo_pacientes, int n_pacientes, int * fechas_atenciones, int * ID_triaje,
                     int * frecuencia_cardiaca, int * sistolica, int * diastolica, double * temperatura, int * saturacion_oxigeno, int n_triaje) {
    ifstream input;
    apertura_archivo_lectura(input, file_name_entrada);
    ofstream output;
    apertura_archivo_escritura(output, file_name_salida);

    imprimir_titulo(output);
    int fecha_registro_leido;
    while (1) {
        fecha_registro_leido = leer_fecha(input);
        if (fecha_registro_leido == -1 or input.eof()) break;
        imprimir_linea(ANCHO_REPORTE,'=',output);
        output<<"FECHA:       ";
        imprimir_fecha(fecha_registro_leido, output);
        output<<endl<<"PACIENTES ATENDIDOS: "<<endl;
        imprimir_pacientes(input, output, fecha_registro_leido, ID_pacientes,edad_pacientes, sexo_pacientes, n_pacientes,
                           fechas_atenciones, ID_triaje, frecuencia_cardiaca, sistolica, diastolica, temperatura, saturacion_oxigeno, n_triaje);
    }
    input.close();
}

void imprimir_pacientes(ifstream & input, ofstream & output, int fecha_leido, int * ID_pacientes, int * edad_pacientes, char * sexo_pacientes,
                        int n_pacientes, int * fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca, int * sistolica, int * diastolica,
                        double * temperatura, int * saturacion_oxigeno, int n_triaje) {
    int hora_ingreso, hora_salida, parte1, parte2, parte3, ID_leido, i=0;
    int pos_paciente, pos_triaje, duracion;
    double costo_atencion, costo_total;
    char c;
    output<<fixed;
    while (1) {
        hora_ingreso = leer_hora(input);
        input>>parte1>>c>>parte2>>c>>parte3;
        ID_leido = parte1*1000000 + parte2*10000 + parte3;
        hora_salida = leer_hora(input);
        input>>costo_atencion;
        pos_paciente=buscar_paciente(ID_leido, ID_pacientes, n_pacientes);
        pos_triaje=buscar_triaje(fecha_leido, ID_leido, fechas_atenciones, ID_triaje, n_triaje);
        if (pos_paciente != -1 and pos_triaje != -1) {
            imprimir_linea(ANCHO_REPORTE,'-',output);
            output<<setfill('0')<<setw(2)<<i+1<<setfill(' ')<<")   "<<"DATOS DEL PACIENTE:"<<endl;
            output<<setw(6)<<""<<"ID:"<<setw(13)<<ID_pacientes[pos_paciente];
            output<<setw(14)<<""<<"EDAD:"<<setw(4)<<edad_pacientes[pos_paciente];
            output<<setw(14)<<""<<"SEXO:  ";
            if (sexo_pacientes[pos_paciente] == 'M') output<<"MASCULINO";
            if (sexo_pacientes[pos_paciente] == 'F') output<<"FEMENINO";
            output<<endl;
            output<<setw(6)<<""<<"SIGNOS VITALES: "<<endl;
            output<<setw(6)<<""<<"TEMPERATURA:"<<setw(8)<<setprecision(1)<<temperatura[pos_triaje];
            output<<setw(10)<<""<<"PRESION SISTOLICA:"<<setw(6)<<sistolica[pos_triaje];
            output<<setw(10)<<""<<"PRESION DIASTOLICA:"<<setw(5)<<diastolica[pos_triaje]<<endl;
            output<<setw(6)<<""<<"ATENCION:"<<endl;
            output<<setw(6)<<""<<"COSTO POR HORA SEGUN LA ESPECIALIDAD:"<<setw(12)<<setprecision(2)<<costo_atencion;
            output<<setw(10)<<""<<"DURACION:"<<setw(4)<<"";
            duracion=calcular_duracion(hora_ingreso,hora_salida);
            imprimir_hora(duracion,output);
            output<<setw(6)<<""<<"COSTO TOTAL:";
            if (edad_pacientes[pos_paciente] < 18) costo_total=costo_atencion*duracion/3600.0*0.95;
            if (edad_pacientes[pos_paciente] >= 18 and edad_pacientes[pos_paciente] <=64) costo_total=costo_atencion*duracion/3600.0;
            if (edad_pacientes[pos_paciente] > 64) costo_total=costo_atencion*duracion/3600.0*0.82;
            output<<setw(12)<<costo_total<<endl;
            i++;
        } else {
            cout<<"No se encontró al paciente o el registro de la cita realizada"<<endl;
        }
        input.get(c);
        if (c=='\n') break;
    }
}

int buscar_paciente(int id_leido, int * id_pacientes,int n_pacientes) {
    for (int i=0; i<n_pacientes; i++) {
        if (id_pacientes[i] == id_leido) return i;
    }
    return -1;
}

int buscar_triaje(int fecha_leido, int id_leido, int * fechas_atenciones, int * id_triaje, int n_triaje) {
    for (int i=0; i<n_triaje; i++) {
        if (fechas_atenciones[i] == fecha_leido and
            id_triaje[i] == id_leido) return i;
    }
    return -1;
}

int calcular_duracion(int hora_ingreso, int hora_salida) {
    if (hora_salida-hora_ingreso >= 0) return hora_salida-hora_ingreso;
    return (HORAS_COMPLETAS)-hora_ingreso+hora_salida;
}

void imprimir_hora(int tiempo,ofstream & output) {
    int hora,minuto,segundo;

    hora=tiempo/3600;
    tiempo=tiempo%3600;
    minuto=tiempo/60;
    segundo=tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}