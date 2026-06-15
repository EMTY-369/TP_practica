//
// Created by User on 26/04/2026.
//

#include "Funciones.hpp"

void calcular_reporte(double tarifa_duracion_etiqueta,
                     const char *file_entrada_canales,
                     const char *file_entrada_etiquetas,
                     const char *file_entrada_reproducciones,
                     const char *file_salida_reporte) {
    ifstream input_canales, input_etiquetas, input_reproducciones;
    apertura_archivo_lectura(file_entrada_canales, input_canales);
    apertura_archivo_lectura(file_entrada_etiquetas, input_etiquetas);
    apertura_archivo_lectura(file_entrada_reproducciones, input_reproducciones);

    ofstream output;
    apertura_archivo_escritura(file_salida_reporte, output);

    imprimir_titulo(tarifa_duracion_etiqueta, output);
    leer_imprimir_canales(tarifa_duracion_etiqueta,input_canales,input_etiquetas,input_reproducciones, output);

    input_canales.close();
    input_etiquetas.close();
    input_reproducciones.close();
    output.close();
}

void apertura_archivo_lectura(const char *file_name,ifstream &input) {
    input.open(file_name, ios::in);
    if(not input.is_open()) {
        cout<<"Error al abrir el archivo de apertura: "<<file_name<<endl;
        exit(1);
    }
}

void apertura_archivo_escritura(const char *file_name,ofstream &output) {
    output.open(file_name, ios::out);
    if(not output.is_open()) {
        cout<<"Error al abrir el archivo de escritura"<<endl;
        exit(1);
    }
}

void imprimir_titulo(double tarifa_duracion_etiqueta,ofstream &output) {
    output<<setw((ANCHO_REPORTE+20)/2)<<"PLATAFORMA TP_Twitch"<<endl;
    output<<setw((ANCHO_REPORTE-69)/2)<<""<<"TARIFA POR DURACION DE LAS ETIQUETAS: "<<
        tarifa_duracion_etiqueta<<" POR CADA MINUTO Y FRACCION"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_linea(int n,char c,ofstream &output) {
    for(int i=0;i<n;i++) output.put(c);
    output<<endl;
}

void leer_imprimir_canales(double tarifa_duracion_etiqueta,ifstream &input_canales,ifstream &input_etiquetas,
                           ifstream &input_reproducciones,ofstream &output) {
    int fecha_creacion, cant_canales=1, int_codigo, tiempo_total_repro;
    double rating;
    char c_codigo;

    while (1) {
        fecha_creacion=leer_fecha(input_canales);
        if(input_canales.eof()) break;

        imprimir_leer_encabezado(cant_canales, fecha_creacion, int_codigo, c_codigo, rating, input_canales, output);
        tiempo_total_repro=0;
        leer_imprimir_parte_dinamica(int_codigo, c_codigo,tiempo_total_repro, input_canales, input_etiquetas,
                                  input_reproducciones, output);
        imprimir_resumen_canal(tiempo_total_repro, tarifa_duracion_etiqueta, rating, output);
        cant_canales++;
    }

}

int leer_fecha(ifstream &input) {
    int aa,mm,dd;
    char c;

    input>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void imprimir_leer_encabezado(int cant_canales,int fecha_creacion,int &int_codigo,char &c_codigo,double &rating,
                             ifstream &input_canales, ofstream &output) {

    output<<fixed;
    output<<"CANAL No. "<<cant_canales<<endl;
    output<<setw(ANCHO_REPORTE/20)<<""<<left<<setw(ANCHO_REPORTE/8)<<"NOMBRE "
          <<setw(ANCHO_REPORTE/8)<<"CODIGO "<<setw(ANCHO_REPORTE/8)<<"CREADO EL "
          <<setw(ANCHO_REPORTE/8)<<"RATING DE CALIDAD "<<right<<endl;

    input_canales>>ws>>c_codigo>>int_codigo;

    output<<setw(ANCHO_REPORTE/20)<<"";
    imprimir_nombre(true,input_canales,output);
    input_canales>>ws>>rating;
    output<<c_codigo<<int_codigo<<setw(ANCHO_REPORTE/8 - 5)<<"";
    imprimir_fecha(fecha_creacion, output);
    output<<setw(ANCHO_REPORTE/8 - 10)<<""<<setw(ANCHO_REPORTE/16)<<setprecision(2)<<rating<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void imprimir_nombre(bool mayus,ifstream &input,ofstream &output) {
    int espacios=0;
    char c;

    input>>ws;
    while (1) {
        input.get(c);
        if (c==' ') break;
        if (mayus) {
            if (c>='a' and c<='z') c=a_mayuscula(c);
        }
        output.put(c);
        espacios++;
    }
    if (mayus) {
        output<<setw(ANCHO_REPORTE/8 - espacios)<<" ";
    } else {
        output<<setw(ANCHO_REPORTE/6 - 1 - espacios)<<" ";
    }
}

char a_mayuscula(char c) {
    return c-abs('a' - 'A');
}

void imprimir_fecha(int fecha,ofstream &output) {
    int dd,mm,aa;

    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;

    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void leer_imprimir_parte_dinamica(int int_codigo,char c_codigo,int &tiempo_total_repro,ifstream &input_canales,
                                  ifstream &input_etiquetas, ifstream &input_reproducciones,ofstream &output){
    int etiqueta, cant_etiquetas=1, duracion, cant_reproducciones=0, tiempo_etiqueta_repro;
    char c;

    output<<"ETIQUETAS REPRODUCIDAS: "<<endl;
    output<<setw(5)<<"No."<<setw(2)<<""<<left<<setw(ANCHO_REPORTE/6-1)<<"FECHA"<<setw(ANCHO_REPORTE/6-1)<<"ETIQUETA "
          <<setw(ANCHO_REPORTE/6-1)<<"DESCRIPCION "<<setw(ANCHO_REPORTE/6-1)<<"DURACION "
          <<setw(ANCHO_REPORTE/6-1)<<"CANTIDAD DE REPRODUCCIONES "
          <<setw(ANCHO_REPORTE/6-1)<<"TIEMPO TOTAL REPRODUCIDO"<<right<<endl;
    input_canales>>ws;
    while (1) {
        input_canales>>etiqueta;
        buscar_cant_repro_leer_imprimir_info(int_codigo, c_codigo, etiqueta, cant_reproducciones, input_reproducciones, output, cant_etiquetas);
        // if (cant_reproducciones!=-1) {
        //     output<<setw(2)<<""<<setfill('0')<<setw(2)<<cant_etiquetas<<setfill(' ')<<")"<<setw(2)<<"";
        // }
        if (cant_reproducciones!=-1) {
            buscar_duracion_leer_imprimir_info(etiqueta, duracion, input_etiquetas, output);
            imprimir_tiempo(duracion, false, output);
            output<<setw(ANCHO_REPORTE/6-6)<<" ";
            output<<setw((ANCHO_REPORTE/6 - 8)/2)<<cant_reproducciones<<setw((ANCHO_REPORTE/6-8)/2 +7)<<"";
            tiempo_etiqueta_repro=duracion*cant_reproducciones;
            output<<setw((ANCHO_REPORTE/6-20)/2)<<"";
            imprimir_tiempo(tiempo_etiqueta_repro, true, output);
            output<<endl;

            tiempo_total_repro+=tiempo_etiqueta_repro;
            cant_etiquetas++;
        }
        input_canales.get(c);
        if (c=='\n') break;
    }
}

void buscar_cant_repro_leer_imprimir_info(int int_codigo,char c_codigo,int etiqueta,int &cant_reproducciones,
                                          ifstream &input_reproducciones,ofstream &output,int cant_etiquetas) {
    int fecha_registro, int_codigo_leido, etiqueta_leido;
    char c_codigo_leido;

    input_reproducciones.clear();
    input_reproducciones.seekg(0,ios::beg);

    while (1) {
        fecha_registro=leer_fecha(input_reproducciones);
        if (input_reproducciones.eof()) {
            cant_reproducciones = -1;
            break;
        }

        input_reproducciones>>ws>>c_codigo_leido>>int_codigo_leido>>ws>>etiqueta_leido;
        if (c_codigo==c_codigo_leido and int_codigo_leido==int_codigo and etiqueta==etiqueta_leido) {
            output<<setw(2)<<""<<setfill('0')<<setw(2)<<cant_etiquetas<<setfill(' ')<<")"<<setw(2)<<"";
            imprimir_fecha(fecha_registro,output);
            output<<setw(ANCHO_REPORTE/6 - 11)<<"";
            output<<setw(ANCHO_REPORTE/6-1)<<left<<etiqueta<<right;
            input_reproducciones>>ws>>cant_reproducciones;
            break;
        }
        input_reproducciones.ignore(20, '\n');
    }
}


void buscar_duracion_leer_imprimir_info(int etiqueta,int &duracion,ifstream &input_etiquetas,ofstream &output) {
    int etiqueta_leido;

    input_etiquetas.clear();
    input_etiquetas.seekg(0,ios::beg);

    while (1) {
        input_etiquetas>>etiqueta_leido;
        if (input_etiquetas.eof()) break;

        if (etiqueta==etiqueta_leido) {
            imprimir_nombre(false,input_etiquetas,output);
            duracion=leer_duracion(input_etiquetas); //en segundos
            break;
        }
        input_etiquetas.ignore(40, '\n');
    }
}

int leer_duracion(ifstream &input_etiquetas) {
    int minuto, segundo;
    char c;

    input_etiquetas>>minuto>>c>>segundo;

    return minuto*60+segundo;
}

void imprimir_tiempo(int tiempo,bool hay_hora, ofstream &output) {
    int minuto, segundo, hora;

    if (hay_hora) {
        hora=tiempo/3600;
        tiempo=tiempo%3600;
    }
    minuto=tiempo/60;
    segundo=tiempo%60;
    output<<setfill('0');
    if (hay_hora) output<<setw(2)<<hora<<":";
    output<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

void imprimir_resumen_canal(int tiempo_total_repro,double tarifa_duracion_etiqueta,double rating,ofstream &output) {
    double extra, ingresos;
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<fixed;
    output<<"TIEMPO TOTAL DE REPRODUCCIONES DE ETIQUETAS:    ";
    imprimir_tiempo(tiempo_total_repro,true,output);
    output<<endl<<"PORCENTAJE POR RATING DE CALIDAD:                   ";
    if (rating>4 and rating<=5) {
        extra=1.3;
        output<<"+30%"<<endl;
    }
    if (rating>3 and rating<=4) {
        extra=1.2;
        output<<"+20%"<<endl;
    }
    if (rating>2 and rating<=3) {
        extra=1;
        output<<"  0%"<<endl;
    }
    if (rating>1 and rating<=2) {
        extra=0.75;
        output<<"-25%"<<endl;
    }
    ingresos=(tiempo_total_repro/60)*extra*tarifa_duracion_etiqueta;
    output<<"INGRESOS POR REPRODUCCION DE ETIQUETAS:          "<<setprecision(2)<<setw(7)<<ingresos<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}