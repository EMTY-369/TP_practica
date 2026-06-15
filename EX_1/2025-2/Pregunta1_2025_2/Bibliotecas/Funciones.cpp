//
// Created by User on 13/05/2026.
//

#include "Funciones.hpp"

void escribir_reporte(const char *file_entrada_canales, const char *file_entrada_streams, const char *file_entrada_categorias,
                      const char *file_entrada_idiomas, const char *file_salida) {
    ifstream input_canales, input_streams, input_categorias, input_idiomas;
    abrir_archivo_lectura(file_entrada_canales, input_canales);
    abrir_archivo_lectura(file_entrada_streams, input_streams);
    abrir_archivo_lectura(file_entrada_categorias, input_categorias);
    abrir_archivo_lectura(file_entrada_idiomas, input_idiomas);

    ofstream output;
    abrir_archivo_escritura(file_salida, output);

    imprimir_titulo(output);
    int n_streams=0, total_duraciones=0;
    imprimir_streams(output, input_canales, input_streams, input_categorias, input_idiomas, n_streams, total_duraciones);
    output<<"RESUMEN TOTAL:"<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<"# STREAMS:    "<<n_streams<<endl;
    output<<"DURACION TOTAL REPRODUCCION:   ";
    imprimir_tiempo(total_duraciones, output);


    input_canales.close();
    input_streams.close();
    input_categorias.close();
    input_idiomas.close();
    output.close();
}

void abrir_archivo_lectura(const char *file_name, ifstream & input) {
    input.open(file_name);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: " <<file_name<< endl;
        exit(1);
    }
}

void abrir_archivo_escritura(const char * file_salida, ofstream & output) {
    output.open(file_salida);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura: " <<file_salida<< endl;
        exit(1);
    }
}

void imprimir_titulo( ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw((ANCHO_REPORTE+26)/2)<<"PLATAFORMA DE STREAMING TP"<<endl;
    output<<setw((ANCHO_REPORTE+23)/2)<<"REPRODUCCION DE STREAMS"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    output<<endl;
}

void imprimir_streams(ofstream & output, ifstream & input_canales,ifstream &input_streams, ifstream &input_categorias,
                      ifstream & input_idiomas, int &n_streams, int &total_duraciones) {

    int cod_stream, duracion, cod_idioma, categoria_int;
    char categoria_char;
    output<<fixed;
    while (true) {
        input_streams>>cod_stream;
        if (input_streams.eof()) break;
        duracion=leer_tiempo(input_streams);
        input_streams>>cod_idioma>>ws>>categoria_char>>categoria_int;
        imprimir_encabezado(output, input_categorias,input_idiomas, cod_stream, categoria_char, categoria_int,
                            cod_idioma, duracion);
        double drop_menor=0, drop_mayor=0;
        int cant_repro=0, tiempo_stream=0, canal_menor_int, canal_mayor_int;
        char canal_mayor_char, canal_menor_char;
        imprimir_canales(input_canales,output,cod_stream, duracion,cant_repro,tiempo_stream,drop_menor,drop_mayor,canal_mayor_int,canal_menor_int,
                         canal_mayor_char,canal_menor_char);
        output<<"RESUMEN DEL STREAM:"<<endl;
        output<<"#VECES REPRODUCIDAS:               "<<cant_repro<<endl;
        output<<"TIEMPO TOTAL REPRODUCION:         ";
        imprimir_tiempo(tiempo_stream,output);
        output<<endl;
        output<<"TASA DROP-OFF MENOR: "<<setprecision(2)<<drop_menor<<"  CANAL:  "<<canal_menor_char<<canal_menor_int<<endl;
        output<<"TASA DROP-OFF MAYOR: "<<setprecision(2)<<drop_mayor<<"  CANAL:  "<<canal_mayor_char<<canal_mayor_int<<endl;
        imprimir_linea(ANCHO_REPORTE,'=',output);
        n_streams+=cant_repro;
        total_duraciones+=tiempo_stream;
    }
}

int leer_tiempo(ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void imprimir_encabezado(ofstream & output,ifstream & input_categorias, ifstream & input_idiomas, int cod_stream,
                         char categoria_char, int categoria_int, int cod_idioma, int duracion) {
    output<<"STREAM:  "<<cod_stream<<setw(6)<<"";
    output<<"CATEGORIA:  "<<categoria_char<<categoria_int<<" - ";
    buscar_imprimir_categoria(input_categorias,output,categoria_char,categoria_int);
    output<<"IDIOMA:  "<<cod_idioma<<" - ";
    buscar_imprimir_idioma(input_idiomas,output,cod_idioma);
    output<<"DURACION:  ";
    imprimir_tiempo(duracion, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void buscar_imprimir_categoria(ifstream &input_categorias,ofstream & output, char categoria_char, int categoria_int) {
    input_categorias.clear();
    input_categorias.seekg(0,ios::beg);

    int cat_int_leido;
    char cat_char_leido;
    bool encontrado = false;
    while (true) {
        input_categorias>>ws>>cat_char_leido;
        if (input_categorias.eof()) break;
        input_categorias>>cat_int_leido;
        if (categoria_char==cat_char_leido and categoria_int==cat_int_leido) {
            leer_imprimir_nombre(input_categorias,output,60,true);
            encontrado = true;
            break;
        }else {
            input_categorias.ignore(100,'\n');
        }
    }
    if (not encontrado) {
        output<<left<<setw(60)<<"NO ENCONTRADO"<<right;
    }
}

void leer_imprimir_nombre(ifstream &input,ofstream &output, int espacio, bool all_mayus) {
    char c;
    int n=0;
    input>>ws;
    while (true) {
        input.get(c);
        if (c=='\n') break;
        if (all_mayus) {
            if (c>='a' and c<='z') c=to_mayus(c);
        }
        if (c=='_') c=' ';
        output.put(c);
        n++;
    }
    output<<setw(espacio-n)<<"";
}

char to_mayus(char c) {
    return c-abs('A'-'a');
}

void buscar_imprimir_idioma(ifstream &input_idiomas, ofstream & output, int cod_idioma) {
    input_idiomas.clear();
    input_idiomas.seekg(0,ios::beg);
    int cod_idi_leido;
    bool encontrado = false;
    while (true) {
        input_idiomas>>cod_idi_leido;
        if (input_idiomas.eof()) break;
        if (cod_idi_leido==cod_idioma) {
            leer_imprimir_nombre(input_idiomas,output,15,false);
            encontrado = true;
            break;
        }else {
            input_idiomas.ignore(30,'\n');
        }
    }
    if (not encontrado) {
        output<<left<<setw(15)<<"NO ENCONTRADO"<<right;
    }
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora,minuto,segundo;
    hora = tiempo/3600;
    tiempo = tiempo%3600;
    minuto = tiempo/60;
    segundo = tiempo%60;

    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

void imprimir_canales(ifstream &input_canales, ofstream &output, int cod_stream,int duracion, int &cant_repro, int &tiempo_stream, double &drop_menor,
                     double &drop_mayor, int &canal_mayor_int, int &canal_menor_int, char &canal_mayor_char, char &canal_menor_char) {
    input_canales.clear();
    input_canales.seekg(0,ios::beg);
    int dd, cod_canal_int,n_canales=0,
    n_repro;
    char cod_canal_char;
    output<<fixed;
    while (true) {
        input_canales>>dd;
        if (input_canales.eof()) break;
        input_canales.ignore(9,' ');
        input_canales>>ws>>cod_canal_char>>cod_canal_int>>ws;
        input_canales.ignore(40,' ');
        double prom_rating=0, prom_drop=0;
        leer_imprimir_repro(input_canales, output, cod_stream, duracion, cod_canal_int, cod_canal_char, prom_rating,
                            prom_drop, drop_mayor,drop_menor,canal_mayor_int, canal_menor_int,
                            canal_menor_char,canal_mayor_char,n_repro,n_canales);
        cant_repro+=n_repro;
        tiempo_stream+=duracion*n_repro;
        if (n_repro!=0) {
            prom_rating/=n_repro;
            prom_drop/=n_repro;
            output<<setw(8)<<""<<"TOTAL TIEMPO REPRODUCCIONES:  ";
            imprimir_tiempo(duracion*n_repro,output);
            output<<endl;
            output<<setw(8)<<""<<"PROMEDIO RATING CALIDAD:  "<<setprecision(2)<<prom_rating<<endl;
            output<<setw(8)<<""<<"PROMEDIO RATING CALIDAD:  "<<setprecision(2)<<prom_drop*100<<"%"<<endl;
            imprimir_linea(ANCHO_REPORTE,'-',output);
        }
    }

}

int leer_fecha( ifstream &input) {
    int aa,mm,dd;
    char c;
    input>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void leer_imprimir_repro(ifstream &input_canales, ofstream & output, int cod_stream, int duracion, int cod_canal_int, char cod_canal_char,
                         double &prom_rating, double &prom_drop, double &drop_mayor, double &drop_menor, int &canal_mayor_int,
                         int &canal_menor_int, char &canal_menor_char, char &canal_mayor_char, int &n_repro, int &n_canales) {
    int cod_stream_leido, fecha_leido, hora_inicio, hora_final;
    double rating_leido, drop_leido;
    char c;
    output<<fixed;
    n_repro=0;
    while (true) {
        input_canales>>cod_stream_leido;
        fecha_leido=leer_fecha(input_canales);
        hora_inicio=leer_tiempo(input_canales);
        input_canales>>rating_leido>>drop_leido;
        if (cod_stream==cod_stream_leido) {
            n_repro++;
            if (n_repro==1) {
                n_canales++;
                imprimir_encabezado_2(output, n_canales, cod_canal_char, cod_canal_int);
            }
            output<<setw(8)<<""<<setfill('0')<<setw(2)<<n_repro<<setfill(' ')<<")   ";
            imprimir_fecha(output,fecha_leido);
            output<<setw((ANCHO_REPORTE-14)/5 -10)<<"";
            imprimir_tiempo(hora_inicio,output);
            output<<setw((ANCHO_REPORTE-14)/5 -8)<<"";
            hora_final=hora_inicio+duracion;
            imprimir_tiempo(hora_final,output);
            output<<setw((ANCHO_REPORTE-14)/5 -8)<<"";
            output<<setw(((ANCHO_REPORTE-14)/5 +4)/2)<<setprecision(2)<<rating_leido<<setw(((ANCHO_REPORTE-14)/5 -4)/2)<<"";
            output<<setw(((ANCHO_REPORTE-14)/5 +4)/2)<<setprecision(2)<<drop_leido*100<<"%"<<setw(((ANCHO_REPORTE-14)/5 -3)/2)<<""<<endl;
            if (drop_mayor==0 or drop_mayor<drop_leido) {
                drop_mayor=drop_leido;
                canal_mayor_int=cod_canal_int;
                canal_mayor_char=cod_canal_char;
            }
            if (drop_menor==0 or drop_menor>drop_leido) {
                drop_menor=drop_leido;
                canal_menor_int=cod_canal_int;
                canal_menor_char=cod_canal_char;
            }
            prom_rating+=rating_leido;
            prom_drop+=drop_leido;
        }
        input_canales.get(c);
        if (c=='\n') break;
    }
}

void imprimir_encabezado_2(ofstream &output, int n_canales, char cod_canal_char, int cod_canal_int) {
    output<<setw(2)<<""<<setfill('0')<<setw(2)<<n_canales<<setfill(' ')<<")   ";
    output<<"CANAL:  "<<cod_canal_char<<cod_canal_int<<endl;
    output<<setw(8)<<""<<"REPRODUCCIONES"<<endl;
    output<<setw(8)<<""<<"No.   ";
    output<<setw((((ANCHO_REPORTE-14)/5)+6)/2)<<"FECHA "<<setw((((ANCHO_REPORTE-14)/5)-6)/2)<<"";
    output<<setw((((ANCHO_REPORTE-14)/5)+6)/2)<<"INICIO"<<setw((((ANCHO_REPORTE-14)/5)-6)/2)<<"";
    output<<setw((((ANCHO_REPORTE-14)/5)+4)/2)<<"FIN "<<setw((((ANCHO_REPORTE-14)/5)-4)/2)<<"";
    output<<setw((((ANCHO_REPORTE-14)/5)+14)/2)<<"RATING CALIDAD"<<setw((((ANCHO_REPORTE-14)/5)-14)/2)<<"";
    output<<setw((((ANCHO_REPORTE-14)/5)+6)/2)<<"TASA DROP-OFF"<<setw((((ANCHO_REPORTE-14)/5)-6)/2)<<"";
    output<<endl;
}

void imprimir_fecha( ofstream & output, int fecha) {
    int aa,mm,dd;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}
