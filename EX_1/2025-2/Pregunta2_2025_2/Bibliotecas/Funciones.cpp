//
// Created by User on 15/05/2026.
//

#include "Funciones.hpp"

void cargar_streams(const char *file_name, int *arr_codigos_streams, int *arr_duraciones_streams, int *arr_codigos_idiomas,
                    int * arr_categorias_int, char *arr_categorias_char, int &n_streams) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int cod_stream, duracion,cod_idioma,cat_int;
    char cat_char;
    while (true) {
        input>>cod_stream;
        if (input.eof()) break;
        duracion = leer_tiempo(input);
        input>>cod_idioma>>ws>>cat_char>>cat_int;
        insertar_ordenar(cod_stream,duracion,cod_idioma,cat_char,cat_int,n_streams,arr_codigos_streams,arr_duraciones_streams,
                         arr_codigos_idiomas,arr_categorias_int, arr_categorias_char);
        n_streams++;
    }
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if(not input.is_open()) {
        cout<<"El archivo de lectura no se pudo abrir: "<<file_name<<endl;
        exit(1);
    }
}

int leer_tiempo(ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void insertar_ordenar(int cod_stream, int duracion, int cod_idioma, char cat_char, int cat_int, int n_streams,
                     int * arr_codigos_streams, int * arr_duraciones_streams, int * arr_codigos_idiomas, int * arr_categorias_int, char * arr_categorias_char) {
    int i=n_streams-1;

    while (i>=0 and arr_codigos_streams[i]>cod_stream) {
        arr_codigos_streams[i+1]=arr_codigos_streams[i];
        arr_duraciones_streams[i+1]=arr_duraciones_streams[i];
        arr_codigos_idiomas[i+1]=arr_codigos_idiomas[i];
        arr_categorias_int[i+1]=arr_categorias_int[i];
        arr_categorias_char[i+1]=arr_categorias_char[i];
        i--;
    }
    arr_codigos_streams[i+1]=cod_stream;
    arr_duraciones_streams[i+1]=duracion;
    arr_codigos_idiomas[i+1]=cod_idioma;
    arr_categorias_int[i+1]=cat_int;
    arr_categorias_char[i+1]=cat_char;
}

void probar_carga_streams(const char *file_name, int *arr_codigos_streams, int *arr_duraciones_streams, int *arr_codigos_idiomas,
                          int *arr_categorias_int, char *arr_categorias_char, int n_streams) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    output<<setw((ANCHO_REPORTE+30)/2)<<"PRUEBA DE CARGA DE LOS STREAMS"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw(ANCHO_REPORTE/4)<<left<<"CODIGOS STREAMS";
    output<<setw(ANCHO_REPORTE/4)<<"DURACIÓN";
    output<<setw(ANCHO_REPORTE/4)<<"CODIGOS IDIOMA";
    output<<setw(ANCHO_REPORTE/4)<<"CATEGORIAS"<<endl;
    for(int i=0; i<n_streams; i++) {
        output<<left<<setw(ANCHO_REPORTE/4)<<arr_codigos_streams[i]<<right;
        imprimir_tiempo(arr_duraciones_streams[i], output);
        output<<left<<setw(ANCHO_REPORTE/4 - 8)<<"";
        output<<setw(ANCHO_REPORTE/4)<<arr_codigos_idiomas[i];
        output<<right<<arr_categorias_char[i]<<arr_categorias_int[i]<<endl;
    }
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if(not output.is_open()) {
        cout<<"El archivo de escritura no se pudo arbri: "<<file_name<<endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for(int i=0; i<n; i++) output.put(c);
    output<<endl;
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora, minuto, segundo;
    hora=tiempo/3600;
    tiempo=tiempo%3600;
    minuto=tiempo/60;
    segundo=tiempo%60;

    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

void leer_parte_dinamica(int * arr_codigos_streams, int n_streams, int * arr_rep_antiguas, int * arr_rep_recientes, int * arr_n_rep, double * arr_prom_rating,
                        double * arr_prom_drop, ifstream & input) {
    int cod_stream_leido,fecha, pos_stream;
    double rating_leido,drop_leido;
    char c;
    while(true) {
        input>>cod_stream_leido;
        fecha=leer_fecha(input);
        ignorar(input, ' ');
        input>>rating_leido>>drop_leido;
        pos_stream=buscar_stream(cod_stream_leido,arr_codigos_streams,n_streams);
        if (pos_stream!=-1) {
            if (arr_rep_antiguas[pos_stream]==0 or arr_rep_antiguas[pos_stream]>fecha) arr_rep_antiguas[pos_stream]=fecha;
            if (arr_rep_recientes[pos_stream]==0 or arr_rep_recientes[pos_stream]<fecha) arr_rep_recientes[pos_stream]=fecha;
            arr_n_rep[pos_stream]++;
            arr_prom_rating[pos_stream]+=rating_leido;
            arr_prom_drop[pos_stream]+=drop_leido;
        }
        input.get(c);
        if (c=='\n') break;
    }
}

void cargar_canales(const char *file_name, int *arr_codigos_streams, int n_streams, int * arr_rep_antiguas,
                    int * arr_rep_recientes, int * arr_n_rep, double * arr_prom_rating, double * arr_prom_drop) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dd;
    while (true) {
        input>>dd;
        if (input.eof()) break;
        ignorar(input, ' ');
        ignorar(input, ' ');
        ignorar(input, ' ');
        leer_parte_dinamica(arr_codigos_streams, n_streams, arr_rep_antiguas, arr_rep_recientes,arr_n_rep, arr_prom_rating,
                            arr_prom_drop, input);
    }
}

void ignorar(ifstream & input, char del) {
    input>>ws;
    char c;
    while (true) {
        input.get(c);
        if (c==del) break;
    }
}

int leer_fecha( ifstream & input) {
    int dd,mm,aa;
    char c;

    input>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

int buscar_stream(int cod_stream_leido, int * arr_codigos_streams, int n_streams) {
    int limite_inferior=0, limite_superior=n_streams-1;
    int punto_medio;
    while (true) {
        if (limite_inferior>limite_superior) return NO_ENCONTRADO;
        punto_medio=(limite_inferior+limite_superior)/2;
        if (cod_stream_leido==arr_codigos_streams[punto_medio]) return punto_medio;
        if (cod_stream_leido>arr_codigos_streams[punto_medio]) limite_inferior=punto_medio+1;
        else limite_superior=punto_medio-1;
    }
}

void imprimir_reporte(const char *file_name, bool report1, int *arr_codigos_streams, int *arr_duraciones_streams,
                      int *arr_codigos_idiomas, int * arr_categorias_int, char *arr_categoria_char, int n_streams,
                      int * arr_rep_antiguas, int * arr_rep_recientes, int * arr_n_rep, double * arr_prom_rating,
                      double * arr_prom_drop) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    imprimir_titulo(output, report1);
    imprimir_encabezado(output);
    output<<fixed;
    int mayor_dur=0, menor_dur=0, cod_menor,cod_mayor;
    for (int i=0;i<n_streams;i++) {
        output<<left<<setw(ANCHO_REPORTE/10)<<arr_codigos_streams[i];
        output<<setw(ANCHO_REPORTE/10)<<arr_codigos_idiomas[i];
        output<<arr_categoria_char[i]<<arr_categorias_int[i]<<setw(ANCHO_REPORTE/10 - 5)<<""<<right;
        if (arr_n_rep[i]!=0) {
            imprimir_fecha(arr_rep_antiguas[i], output);
            output<<setw(ANCHO_REPORTE/10 - 10)<<"";
            imprimir_fecha(arr_rep_recientes[i], output);
            output<<setw(ANCHO_REPORTE/10 - 10)<<"";
            output<<left<<setw(ANCHO_REPORTE/10)<<setprecision(2)<<arr_prom_rating[i]/arr_n_rep[i];
            output<<setw(ANCHO_REPORTE/10)<<setprecision(2)<<arr_prom_drop[i]/arr_n_rep[i]*100<<right;
        } else {
            output<<left<<setw(ANCHO_REPORTE/10)<<"  -"<<setw(ANCHO_REPORTE/10)<<"  -"<<setw(ANCHO_REPORTE/10)<<"  -"<<setw(ANCHO_REPORTE/10)<<"-"<<right;
        }
        imprimir_tiempo(arr_duraciones_streams[i], output);
        output<<left<<setw(ANCHO_REPORTE/10 - 8)<<""<<setw(ANCHO_REPORTE/10)<<arr_n_rep[i]<<right;
        imprimir_tiempo(arr_duraciones_streams[i]*arr_n_rep[i], output);
        output<<endl;
        if (mayor_dur==0 or mayor_dur<arr_duraciones_streams[i]) {
            mayor_dur=arr_duraciones_streams[i];
            cod_mayor=arr_codigos_streams[i];
        }
        if (menor_dur==0 or menor_dur>arr_duraciones_streams[i]) {
            menor_dur=arr_duraciones_streams[i];
            cod_menor=arr_codigos_streams[i];
        }
    }
    imprimir_linea(ANCHO_REPORTE,'-',output);
    if (report1) {
        imprimir_resumen(cod_mayor, cod_menor, menor_dur, mayor_dur, output);
        imprimir_linea(ANCHO_REPORTE,'=',output);
    }
}

void imprimir_titulo( ofstream & output, bool report1) {
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw((ANCHO_REPORTE+26)/2)<<"PLATAFORMA DE STREAMING TP"<<endl;
    if (report1) output<<setw((ANCHO_REPORTE+43)/2)<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS"<<endl;
    else output<<setw((ANCHO_REPORTE+79)/2)<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS ORDENADO POR IDIOMA Y TASA DROP-OFF"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_encabezado( ofstream & output) {
    output<<left<<setw(ANCHO_REPORTE/10)<<"STREAM";
    output<<setw(ANCHO_REPORTE/10)<<"IDIOMA";
    output<<setw(ANCHO_REPORTE/10)<<"CATEGORIA";
    output<<setw(ANCHO_REPORTE/10)<<"REP. ANTIGUA";
    output<<setw(ANCHO_REPORTE/10)<<"REP. RECIENTE";
    output<<setw(ANCHO_REPORTE/10)<<"PROM. RAT. CAL";
    output<<setw(ANCHO_REPORTE/10)<<"PROM. TASA. DROP-OFF";
    output<<setw(ANCHO_REPORTE/10)<<"DURAC.";
    output<<setw(ANCHO_REPORTE/10)<<"#REPR.";
    output<<setw(ANCHO_REPORTE/10)<<"TOT.REPR."<<endl<<right;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void imprimir_fecha(int fecha, ofstream & output) {
    int aa,dd,mm;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;

    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void imprimir_resumen(int cod_mayor, int cod_menor, int menor_dur, int mayor_dur, ofstream & output) {
    output<<"RESUMEN: "<<endl;
    output<<"STREAM CON MAYOR DURACION:      "<<cod_mayor<<" - ";
    imprimir_tiempo(mayor_dur, output);
    output<<endl;
    output<<"STREAM CON MENOR DURACION:      "<<cod_menor<<" - ";
    imprimir_tiempo(menor_dur, output);
    output<<endl;
}

void ordenar_idioma_drop(int *arr_codigos_streams, int * arr_duraciones_streams, int * arr_codigos_idiomas, int * arr_categorias_int,
                         char *arr_categorias_char, int n_streams, int * arr_rep_antiguas, int * arr_rep_recientes, int * arr_n_rep,
                         double * arr_prom_rating, double * arr_prom_drop) {
    for (int i = 0; i < n_streams-1; i++) {
        for (int j = i+1; j < n_streams; j++) {
            if (arr_codigos_idiomas[i] > arr_codigos_idiomas[j] or
                arr_codigos_idiomas[i] == arr_codigos_idiomas[j] and arr_prom_drop) {

            }
        }
    }

}