//
// Created by alois on 18/4/26.
//

#include "Funciones.hpp"

void imprir_resumen_final(int atenciones_total,int tiempo_total,double costo_total,ofstream &output) {
    output<<"RESUMEN FINAL:"<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"CANTIDAD DE ATENCIONES:  "<<atenciones_total<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"TIEMPO TOTAL DESTINADO A LAS ATENCIONES:  ";
    imprimir_hora(tiempo_total, output);
    output<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"COSTO TOTAL POR LAS ATENCIONES:           "<<costo_total<<endl;

}

void imprimir_resumen_canal(int atenciones_dia, int normal, int h_nivel_2, int ID_PA_mayor, double PA_mayor, int tiempo_dia, double costo_dia, ofstream &output) {
    int part1, part2, part3;
    imprimir_linea('-',ANCHO_REPORTE,output);

    output<<fixed;

    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"RESUMEN DEL CANAL"<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"CANTIDAD DE ATENCIONES:  "<<atenciones_dia<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"CANTIDAD DE PACIENTES CON NIVEL DE LA PRESION ARTERIAL EN NORMAL:  "<<normal<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"CANTIDAD DE PACIENTES CON NIVEL DE LA PRESION ARTERIAL EN HIPERTENSION NIVEL 2:  "<<h_nivel_2<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"PACIENTE CON MAYOR PRESION ARTERIAL MEDIA: ";
    part1=ID_PA_mayor/1000000;
    ID_PA_mayor=ID_PA_mayor%1000000;
    part2=ID_PA_mayor/10000;
    part3=ID_PA_mayor%10000;
    output<<part1<<"-"<<part2<<"-"<<part3;
    output<<" con "<<setprecision(2)<<PA_mayor<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"TIEMPO TOTAL DESTINADO A LAS ATENCIONES: ";
    imprimir_hora(tiempo_dia, output);
    output<<endl;
    output<<setw((ANCHO_REPORTE/N_COLUMNAS)/2)<<""<<"COSTO TOTAL DE LAS ATENCIONES:           "<<setprecision(2)<<costo_dia<<endl;

    imprimir_linea('=',ANCHO_REPORTE,output);
}

void imprimir_nivel_PA(int sistolica, int diastolica, int &normal, int &h_nivel_2, ofstream &output) {
    output<<sistolica<<"/"<<diastolica;
    if (sistolica<120 and diastolica<80){
        output<<" (Normal)";
        normal++;
    }
    if ((sistolica<120 and diastolica>80) or (sistolica>=120 and sistolica<=129 and diastolica<80)) {
        output<<" (Elevada)";
    }
    else {
        if ((sistolica>=130 and sistolica<=139) or (diastolica>=80 and diastolica<=89)) {
            output<<" (H. Nivel 1)";
        }
        else {
            if (sistolica>=140 or diastolica>=90) {
                output<<" (H. Nivel 2)";
                h_nivel_2++;
            }
        }
    }
    output<<endl;
}

void imprimir_hora(int time, ofstream &output) {
    int hora,minuto,segundo;
    hora=time/3600;
    time=time%3600;
    minuto=time/60;
    segundo=time%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

int leer_hora(ifstream &input) {
    int hora, minuto, segundo;
    char c;
    input>>ws;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

char mayuscula(char c) {
    c = c - abs('A'-'a');
    return c;
}

void leer_imprimir_nombre(ifstream &input,ofstream &output) {
    int espacios=0;
    char c;
    input>>ws;
    while (1) {
        input.get(c);
        if (c==' ') {
            break;
        }else {
            if (c=='_') c=' ';
            if (c>='a' and c <='z') mayuscula(c);
        }
        output.put(c);
        espacios++;
    }
    output<<setw(ANCHO_REPORTE/N_COLUMNAS - espacios)<<"";
}

void leer_imprimir_ID(int &ID, ifstream &input, ofstream &output) {
    int part1, part2, part3;
    char c;
    input>>ws;
    input>>part1>>c>>part2>>c>>part3;
    ID=part1*1000000+part2*10000+part3;
    output<<left<<setw(ANCHO_REPORTE/N_COLUMNAS)<<ID<<right;
}

void imprimir_titulo_de_columnas(ofstream &output) {
    output<<left<<setw(4*ANCHO_REPORTE/N_COLUMNAS)<<" "<<setw(ANCHO_REPORTE/ANCHO_REPORTE)<<"DURACION DE LA";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"  COSTO DE LA"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<" ";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"PRESION ARTERIAL"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"  NIVEL DE LA"<<endl;
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"ID "<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"NOMBRE ";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"INGRESO"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"  ALTA"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"   ATENCION";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<" ATENCION"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"TEMPERATURA"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"  MEDIA";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"PRESION ARTERIAL"<<right<<endl;
}


void imprimir_encabezado(int fecha, ofstream &output) {
    output<<"FECHA:  ";
    imprimir_fecha(fecha, output);
    output<<endl;
    output<<"REGISTRO DE ATENCIONES"<<endl;
    imprimir_linea('-',ANCHO_REPORTE,output);
}

void imprimir_canal(int fecha,int &atenciones_dia,int &tiempo_dia,double &costo_dia,ifstream &input,ofstream &output) {
    int ID,hora_ingreso,hora_alta,duracion,sistolica, diastolica;
    int normal=0, h_nivel_2=0, ID_PA_mayor=0;
    double temperatura,costo_persona,presion_arterial_media,PA_mayor=0;
    char c;


    output<<fixed;
    imprimir_encabezado(fecha, output);
    imprimir_titulo_de_columnas(output);
    while (1) {
        leer_imprimir_ID(ID, input, output);
        leer_imprimir_nombre(input, output);
        hora_ingreso=leer_hora(input); //este en segundos
        input>>ws>>temperatura>>ws>>sistolica>>ws>>diastolica;
        hora_alta=leer_hora(input);

        imprimir_hora(hora_ingreso, output);
        output<<setw(ANCHO_REPORTE/N_COLUMNAS-8)<<"";
        imprimir_hora(hora_alta, output);
        output<<setw(ANCHO_REPORTE/N_COLUMNAS-8)<<"";
        duracion=hora_alta-hora_ingreso;
        imprimir_hora(duracion,output);
        output<<setw(ANCHO_REPORTE/N_COLUMNAS-8)<<"";
        costo_persona=(1.0*duracion/3600)*575;
        output<<setw(ANCHO_REPORTE/N_COLUMNAS - 7)<<setprecision(2)<<costo_persona<<setw(7)<<"";
        output<<setw(ANCHO_REPORTE/N_COLUMNAS - 9)<<setprecision(1)<<temperatura<<setw(9)<<"";
        presion_arterial_media=(double)(sistolica+2*diastolica)/3;
        if (PA_mayor<presion_arterial_media) {
            PA_mayor=presion_arterial_media;
            ID_PA_mayor=ID;
        }
        output<<setw(ANCHO_REPORTE/N_COLUMNAS - 9)<<setprecision(2)<<presion_arterial_media<<setw(9)<<"";
        imprimir_nivel_PA(sistolica, diastolica, normal, h_nivel_2, output);
        atenciones_dia++;
        costo_dia+=costo_persona;
        tiempo_dia+=duracion;

        input.get(c);
        if (c=='\n' or c=='\r') break;
    }

    imprimir_resumen_canal(atenciones_dia,normal,h_nivel_2,ID_PA_mayor,PA_mayor,tiempo_dia,costo_dia, output);
}

bool valid(int fecha_inicio,int fecha_final,int fecha) {
    return (fecha_inicio<=fecha and fecha_final>=fecha);
}

void leer_imprimir_atenciones(int fecha_inicio, int fecha_final, int &atenciones_total, int &tiempo_total, double &costo_total, ifstream &input, ofstream &output) {
    int fecha, atenciones_dia, tiempo_dia;
    double costo_dia;
    while (1) {
        fecha=leer_fecha(input);
        if (input.eof()) break;
        if (not  valid(fecha_inicio, fecha_final, fecha)){
            input.ignore(1114,'\n');
            continue;
        }
        atenciones_dia=0;
        costo_dia=0;
        tiempo_dia=0;
        imprimir_canal(fecha, atenciones_dia, tiempo_dia, costo_dia, input, output);

        atenciones_total += atenciones_dia;
        costo_total += costo_dia;
        tiempo_total += tiempo_dia;
    }
}

void imprimir_titulo(int fecha_inicio,int fecha_final,ofstream &output) {
    output << setw((ANCHO_REPORTE+29)/2) << "CLINICA DE URGENCIAS TP_SALUD"<<endl;
    output<<setw((ANCHO_REPORTE+26)/2)<<"REGISTRO DE LAS ATENCIONES"<<endl;
    output<<setw(2*ANCHO_REPORTE/7)<<""<<"ATENCIONES REALIZADAS ENTRE EL ";
    imprimir_fecha(fecha_inicio, output);
    output<<" Y EL ";
    imprimir_fecha(fecha_final, output);
    output<<endl;
    imprimir_linea('=',ANCHO_REPORTE,output);
}

void calcular_el_reporte(int fecha_inicio,int fecha_final, const char *file_name_entrada, const char *file_name_salida) {
    ifstream input;
    apertura_archivo_lectura(input, file_name_entrada);
    ofstream output;
    apertura_archivo_escritura(output, file_name_salida);

    int atenciones_total=0, tiempo_total=0;
    double costo_total=0;

    imprimir_titulo(fecha_inicio, fecha_final, output);
    leer_imprimir_atenciones(fecha_inicio, fecha_final, atenciones_total, tiempo_total, costo_total, input, output);
    imprir_resumen_final(atenciones_total, tiempo_total, costo_total, output);
    input.close();
    output.close();
    cout<<"EL REPORTE FUE REALIZADO CON EXITO";
}

void apertura_archivo_lectura(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout<<"El archivo "<<file_name<<" no se puede abrir"<<endl;
        exit(1);
    }
}
void apertura_archivo_escritura(ofstream &output,const char *file_name) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"El archivo "<<file_name<<" no se puede abrir"<<endl;
        exit(1);
    }
}

void imprimir_fecha(int fecha, ofstream &output) {
    int aa, mm, dd;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;

    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

int leer_fecha(ifstream &input) {
    int aa, mm, dd;
    char c;
    input>>dd>>c>>mm>>c>>aa;

    return aa*10000+mm*100+dd;
}

void imprimir_linea(char c,int n,ofstream &output) {
    for (int i=0;i<n;i++) output.put(c);
    output<<endl;
}