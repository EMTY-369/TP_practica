//
// Created by User on 20/04/2026.
//

#include "Funciones.hpp"

void imprimir_resumen_final(int cant_canales_total,int duracion_total,double ingreso_total_duración,double ingreso_total_publicidad,ofstream &output) {

    output<<"RESUMEN FINAL: "<<endl;
    output<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES:    "<<setw(9)<<cant_canales_total<<endl;
    output<<"DURACION TOTAL DE LOS STREAMS PUBLICADOS:               ";
    imprimir_hora(duracion_total,output);
    output<<endl;
    output<<"INGRESOS TOTALES POR DURACION:                         $"<<setw(9)<<ingreso_total_duración<<endl;
    output<<"INGRESOS TOTALES POR PUBLICIDAD:                       $"<<setw(9)<<ingreso_total_publicidad<<endl;
}

void imprimir_resumen_canal(int duracion_canal_total,double ingreso_duracion_canal,int reproducciones_canal,double ingreso_publicidad_canal,double index,
                            ifstream &input,ofstream &output) {
    output<<fixed;
    output<<setw(6)<<"RESUMEN DEL CANAL: "<<endl;
    output<<setw(6)<<"DURARCION TOTAL DE LAS REPRODUCCIONES: ";
    imprimir_hora(duracion_canal_total, output);
    output<<endl;
    output<<setw(6)<<"INGRESOS POR DURACION:                 $"<<setprecision(2)<<setw(7)<<ingreso_duracion_canal<<endl;
    output<<setw(6)<<"TOTAL DE REPRODUCCIONES:               "<<setw(8)<<reproducciones_canal<<endl;
    output<<setw(6)<<"INGRESOS POR PUBLICIDAD:               $"<<setprecision(2)<<setw(7)<<ingreso_publicidad_canal<<endl;
    output<<setw(6)<<"ENGAGEMENT INDEX:                      "<<setw(8)<<index<<endl<<endl;
    imprimir_linea('=',ANCHO_REPORTE,output);
}

void imprimir_hora(int tiempo,ofstream &output) {
    int hora, minuto, segundo;

    hora=tiempo/3600;
    tiempo=tiempo%3600;
    minuto=tiempo/60;
    segundo=tiempo%60;

    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

int leer_tiempo(ifstream &input) {
    int hora, minuto, segundo;
    char c;
    input>>ws>>hora>>c>>minuto>>c>>segundo;
    return hora*3600 + minuto*60 + segundo;
}

bool valid(int fecha_inicio,int fecha_final,int fecha) {
    return (fecha_inicio<=fecha and fecha_final>=fecha);
}

void leer_imprimir_reproducciones(int fecha_inicio, int fecha_final, double tarifa_duracion, int &duracion_canal_total,
                                  double &ingreso_duracion_canal, int &reproducciones_canal, ifstream &input, ofstream &output) {
    int fecha_publicacion,duracion_publicacion,numero_reproducciones_publicacion;
    double ingreso_duracion_publicacion;
    char c;

    output<<fixed;

    output<<left<<setw(6)<<""<<"ULTIMAS REPRODUCCIONES"<<endl;
    output<<setw(ANCHO_REPORTE/(N_COLUMNAS*2))<<""<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"FECHA DE PUBLICACION";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"TIEMPO DE DURACION"<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"INGRESOS POR DURACION";
    output<<setw(ANCHO_REPORTE/N_COLUMNAS)<<"NUMERO DE REPRODUCCIONES"<<right<<endl;

    while (1) {
        fecha_publicacion=leer_fecha_archivo(input);
        duracion_publicacion=leer_tiempo(input); //en segundos
        input>>numero_reproducciones_publicacion;
        ingreso_duracion_publicacion = tarifa_duracion*duracion_publicacion/60;

        output<<setw(ANCHO_REPORTE/(N_COLUMNAS*2))<<"";
        imprimir_fecha_archivo(fecha_publicacion, output);
        output<<setw(ANCHO_REPORTE/N_COLUMNAS - 10 + 6)<<"";
        imprimir_hora(duracion_publicacion, output);
        output<<setw(ANCHO_REPORTE/N_COLUMNAS - 14)<<""<<setw(13)<<setprecision(2)<<ingreso_duracion_publicacion;
        output<<setw(ANCHO_REPORTE/N_COLUMNAS - 13)<<""<<setw(13)<<numero_reproducciones_publicacion<<endl;

        duracion_canal_total+=duracion_publicacion;
        ingreso_duracion_canal+=ingreso_duracion_publicacion;
        reproducciones_canal+=numero_reproducciones_publicacion;

        input.get(c);
        if (c=='\n') break;
    }
    imprimir_linea('-',ANCHO_REPORTE,output);
}

char mayuscula(char c) {
    return (c-abs('A'-'a'));
}

void leer_imprimir_nombre(ifstream &input,ofstream &output) {
    int espacios=0;
    char c;
    input>>ws;
    while (1) {
        input.get(c);
        if (c==' ') break;
        if (c<='z' and c>='a') c=mayuscula(c);
        output.put(c);
        espacios++;
    }
    output<<setw(20-espacios)<<"";
}

void leer_imprimir_encabezado(int fecha, int cant_canales_total, int &seguidores_nuevos_mes, int &vistas_nuevas_mes, int &max_espectadores, ifstream &input, ofstream &output) {
    int codigo;
    char car_codigo;

    output<<"CANAL No. "<<cant_canales_total<<endl;
    output<<setw(6)<<""<<left<<setw(20)<<"NOMBRE"<<setw(8)<<"CODIGO "<<setw(11)<<"CREADO EL "<<setw(28)<<"SEGUIDORES NUEVOS POR MES";
    output<<setw(24)<<"VISITAS NUEVAS POR MES"<<setw(23)<<"MAXIMO DE ESPECTARORES"<<right<<endl;

    input>>ws>>car_codigo>>codigo;
    output<<setw(6)<<"";
    leer_imprimir_nombre(input, output);
    output<<left<<car_codigo<<codigo<<setw(3)<<"";
    imprimir_fecha_archivo(fecha, output);
    input>>ws>>seguidores_nuevos_mes>>ws>>vistas_nuevas_mes>>ws>>max_espectadores;
    output<<right<<setw(16)<<seguidores_nuevos_mes<<setw(12)<<""<<setw(16)<<vistas_nuevas_mes<<setw(8)<<"";
    output<<setw(14)<<max_espectadores<<endl;
    imprimir_linea('-',ANCHO_REPORTE, output);

}

void leer_imprimir_info_canal(int fecha, int cant_canales_total, double tarifa_duracion, double tarifa_reproduccion, int fecha_inicio, int fecha_final,
                              int &duracion_canal_total, double &ingreso_duracion_canal, double &ingreso_publicidad_canal, ifstream &input, ofstream &output) {

    int reproducciones_canal=0,seguidores_nuevos_mes,vistas_nuevas_mes,max_espectadores;
    double index;
    ingreso_duracion_canal = 0;
    ingreso_publicidad_canal = 0;
    duracion_canal_total = 0;
    leer_imprimir_encabezado(fecha,cant_canales_total,seguidores_nuevos_mes,vistas_nuevas_mes,max_espectadores, input, output);
    leer_imprimir_reproducciones(fecha_inicio,fecha_final,tarifa_duracion,duracion_canal_total,ingreso_duracion_canal,reproducciones_canal,input,output);
    ingreso_publicidad_canal = reproducciones_canal*tarifa_reproduccion/1000;
    index = ((double)seguidores_nuevos_mes + (double)vistas_nuevas_mes/1000)/max_espectadores;
    imprimir_resumen_canal(duracion_canal_total,ingreso_duracion_canal,reproducciones_canal,ingreso_publicidad_canal,index,input,output);

}

int leer_fecha_archivo(ifstream &input) {
    int aa,mm,dd;
    char c;
    input>>ws;
    input>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void leer_imprimir_info_canales(int fecha_inicio, int fecha_final, double tarifa_reproduccion, double tarifa_duracion, int &cant_canales_total, int &duracion_total,
                                double &ingreso_total_duración, double &ingreso_total_publicidad, ifstream &input, ofstream &output) {
    int fecha, duracion_canal_total;
    double ingreso_duracion_canal, ingreso_publicidad_canal;

    while (1) {
        fecha=leer_fecha_archivo(input);
        if (input.eof()) break;
        if (not valid(fecha_inicio, fecha_final, fecha)) {
            input.ignore(380,'\n');
            continue;
        }
        cant_canales_total++;

        leer_imprimir_info_canal(fecha, cant_canales_total, tarifa_duracion,tarifa_reproduccion,fecha_inicio,fecha_final,
                    duracion_canal_total,ingreso_duracion_canal, ingreso_publicidad_canal, input, output);

        duracion_total+=duracion_canal_total;
        ingreso_total_duración+=ingreso_duracion_canal;
        ingreso_total_publicidad+=ingreso_publicidad_canal;
    }
}

void imprimir_linea(char c,int n,ofstream &output) {
    for (int i=0;i<n;i++) output.put(c);
    output<<endl;
}

void imprimir_fecha_archivo(int fecha, ofstream &output) {
    int dd,mm,aa;
    aa = fecha/10000;
    fecha = fecha%10000;
    mm = fecha/100;
    dd = fecha%100;

    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void imprimir_titulo(int fecha_inicio,int fecha_final,double tarifa_reproduccion,double tarifa_duracion,ofstream &output) {

    output<<setw((ANCHO_REPORTE+20)/2)<<"PLATAFORMA TP_Twitch"<<endl;
    output<<setw((ANCHO_REPORTE+33)/2)<<"REGISTRO DE LOS CANALES AFILIADOS"<<endl;
    output<<setw(ANCHO_REPORTE/3)<<""<<"FECHAS DE CREACION ENTRE EL ";
    imprimir_fecha_archivo(fecha_inicio, output);
    output<<" Y EL ";
    imprimir_fecha_archivo(fecha_final, output);
    output<<endl;
    output<<setw(ANCHO_REPORTE/5)<<""<<"TARIFA POR NUMERO DE REPRODUCCIONES: "<<tarifa_reproduccion<<" POR CADA 1,000 REPRODUCCIONES Y FRACCION"<<endl;
    output<<setw(ANCHO_REPORTE/4)<<""<<"TARIFA POR DURACION DEL STREAM: "<<tarifa_duracion<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimir_linea('=', ANCHO_REPORTE, output);
}

void calcular_reporte(int fecha_inicio, int fecha_final, double tarifa_reproduccion, double tarifa_duracion, const char *file_name_entrada, const char *file_name_salida) {


    ifstream input;
    apertura_archivo_lectura(input, file_name_entrada);
    ofstream output;
    apertura_archivo_escritura(output, file_name_salida);

    int cant_canales_total = 0, duracion_total = 0;
    double  ingreso_total_duración=0, ingreso_total_publicidad=0;

    imprimir_titulo(fecha_inicio, fecha_final, tarifa_reproduccion, tarifa_duracion, output);
    leer_imprimir_info_canales(fecha_inicio,fecha_final,tarifa_reproduccion,tarifa_duracion, cant_canales_total,
            duracion_total, ingreso_total_duración, ingreso_total_publicidad, input, output);
    imprimir_resumen_final(cant_canales_total,duracion_total,ingreso_total_duración,ingreso_total_publicidad,output);

    input.close();
    output.close();
}

void apertura_archivo_escritura(ofstream &output,const char *file_name) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<< "Error al abrir el archivo de escritura" << endl;
        exit(1);
    }
}

void apertura_archivo_lectura(ifstream &input,const char *file_name) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de lectura" << endl;
        exit(1);
    }
}

int leer_fecha_consola() {
    int dd,mm,aa;
    char c;
    cin>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}