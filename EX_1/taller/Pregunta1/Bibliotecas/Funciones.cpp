//
// Created by User on 17/05/2026.
//

#include "Funciones.hpp"

#include <cmath>


void abrir_archivo_escritura(const char * file_name, ofstream &output) {
    output.open(file_name, ios::out);
    if ( not output.is_open() ) {
        cout<<"El archivo de escritura no se puede abrir: "<<file_name<<endl;
        exit(1);
    }
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if ( not input.is_open() ) {
        cout<<"El archivo de lectura no se puede abrir: "<<file_name<<endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    output<<endl;
}

void imprimir_titulo( ofstream & output) {
    output<<setw((ANCHO_REPORTE+17)/2)<<"DETALLE DE CURSOS"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_texto( ifstream & input, ofstream & output, int espacios, char del) {
    char c;
    int n=0;
    while (true) {
        input.get(c);
        if (c==del) break;
        if (c=='_' or c=='(' or c=='/' or c=='-' or c=='[') c=' ';
        if (c>='a' and c<='z') c-='a'-'A';
        output.put(c);
        n++;
    }
    for (int i = 0; i < espacios-n; i++) output.put(' ');
}

void imprimir_encabezado( ifstream &input, int cod_curso, ofstream & output) {
    double creditos;
    char c;
    input>>creditos>>ws;
    output<<"CURSO:"<<setw(8)<<cod_curso<<" - ";
    imprimir_texto(input,output , 45, ' ');
    output<<"CREDITOS:"<<setw(6)<<creditos<<setw(18)<<"ESPECIALIDAD:";
    input>>ws;
    imprimir_texto(input,output , 15, ')');
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void buscar_imprimir_profesor( ifstream &input, ofstream & output, int cod_profesor,int horario,int n_alumnos_horario) {
    input.clear();
    input.seekg (0, ios::beg);
    int cod_profesor_leido;
    while (true) {
        input>>cod_profesor_leido;
        if (input.eof()) break;
        if (cod_profesor==cod_profesor_leido) {
            output<<"Horario"<<setw(12)<<"Alumnos"<<setw(30)<<"Profesor"<<endl;
            output<<setw(2)<<""<<setfill('0')<<setw(4)<<horario<<setfill(' ')<<setw(10)<<n_alumnos_horario;
            output<<setw(14)<<cod_profesor_leido<<" - ";
            input>>ws;
            imprimir_texto(input,output , 40, ' ');
            input>>ws;
            output<<" - ";
            imprimir_texto(input,output , 15, ')');
            input>>ws;
            output<<" - ";
            imprimir_texto(input,output , 5, ']');
            output<<endl;
            break;
        }
        input.ignore(70,'\n');
    }
}

void imprimir_dia(int dia, ofstream & output) {
    output<<left<<setw(18);
    if (dia==1) output<<"Lunes";
    if (dia==2) output<<"Martes";
    if (dia==3) output<<"Miercoles";
    if (dia==4) output<<"Jueves";
    if (dia==5) output<<"Viernes";
    if (dia==6) output<<"Sabado";
    if (dia==7) output<<"Domingo";
    output<<right;
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora,minuto;
    hora=tiempo/60;
    minuto=tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<setfill(' ');
}

void leer_imprimir_parte_dinamica(ifstream &input, ofstream &output, int &horas_horario) {
    output<<setw(16)<<"Sesiones"<<setw(16)<<"Hora"<<setw(23)<<"Aula"<<endl;
    int i=0,dia,hora,minuto,hora_inicio,hora_fin,aula_int;
    char c,aula_char;
    while (true) {
        input>>dia;
        input>>hora>>c>>minuto;
        hora_inicio=hora*60+minuto; //esta en minutos
        input>>hora>>c>>minuto;
        hora_fin=hora*60+minuto;
        input>>ws>>aula_char>>aula_int;
        output<<setw(2)<<i+1<<")  ";
        imprimir_dia(dia,output);
        imprimir_tiempo(hora_inicio,output);
        output<<" - ";
        imprimir_tiempo(hora_fin,output);
        output<<setw(16)<<aula_char<<aula_int<<endl;
        horas_horario+=hora_fin-hora_inicio;
        i++;

        input.get(c);
        if (c=='\n') break;
    }
}

void buscar_imprimir_horarios(ifstream &input_sesiones, ifstream &input_profesores, ofstream & output, int cod_curso,
                              int &horas_curso,int &n_alumnos_curso) {
    input_sesiones.clear();
    input_sesiones.seekg (0, ios::beg);
    int cod_curso_leido,horario,n_alumnos_horario,cod_profesor;
    while (true) {
        input_sesiones>>cod_curso_leido;
        if (input_sesiones.eof()) break;
        if (cod_curso_leido == cod_curso) {
            input_sesiones>>horario>>n_alumnos_horario>>cod_profesor;
            buscar_imprimir_profesor(input_profesores,output,cod_profesor,horario,n_alumnos_horario);
            int horas_horario=0;
            leer_imprimir_parte_dinamica(input_sesiones,output,horas_horario);
            output<<"Horas de dictado del horario:  ";
            imprimir_tiempo(horas_horario,output);
            output<<endl;
            imprimir_linea(ANCHO_REPORTE,'-',output);
            horas_curso+=horas_horario;
            n_alumnos_curso+=n_alumnos_horario;
        }
        input_sesiones.ignore(145,'\n');
    }
}

void imprimir_cursos( ifstream &input_cursos, ifstream &input_profesores, ifstream &input_sesiones, ofstream &output) {

    int cod_curso, n_cursos=0, horas_totales=0;
    while (true) {
        input_cursos>>cod_curso;
        if (input_cursos.eof()) break;
        imprimir_encabezado(input_cursos, cod_curso, output);
        int horas_curso=0, n_alumnos_curso=0;
        buscar_imprimir_horarios(input_sesiones, input_profesores, output, cod_curso, horas_curso, n_alumnos_curso);
        output<<"TOTAL DE HORAS DE DICTADO DEL CURSO:  ";
        imprimir_tiempo(horas_curso,output);
        output<<endl<<"TOTAL DE ALUMNOS MATTRICULADOS:   "<<n_alumnos_curso<<endl;
        imprimir_linea(ANCHO_REPORTE,'=',output);
        n_cursos++;
        horas_totales+=horas_curso;
    }
    output<<"RESUMEN"<<endl;
    output<<"TOTAL DE CURSOS DICTADOS:  "<<n_cursos<<endl;
    output<<"HORAS TOTALES DICTADAS:  ";
    imprimir_tiempo(horas_totales,output);
}

void imprimir_reporte(const char *file_cursos, const char *file_profesores, const char *file_sesiones, const char *file_salida) {
    ifstream input_cursos,input_profesores, input_sesiones;
    abrir_archivo_lectura(file_cursos,input_cursos);
    abrir_archivo_lectura(file_profesores,input_profesores);
    abrir_archivo_lectura(file_sesiones,input_sesiones);
    ofstream output;
    abrir_archivo_escritura(file_salida,output);
    output<<fixed;
    output.precision(2);

    imprimir_titulo(output);
    imprimir_cursos(input_cursos,input_profesores,input_sesiones,output);
    input_cursos.close();
    input_profesores.close();
    input_sesiones.close();
    output.close();
}
