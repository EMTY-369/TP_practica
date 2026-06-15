//
// Created by User on 10/05/2026.
//

#include "Funciones.hpp"

void swap_char(char &value_i, char &value_j) {
    char temp = value_i;
    value_i = value_j;
    value_j = temp;
}

void swap_double(double &value_i, double &value_j) {
    double temp = value_i;
    value_i = value_j;
    value_j = temp;
}

void swap_int(int &value_i, int &value_j) {
    int temp = value_i;
    value_i = value_j;
    value_j = temp;
}

void ordenar_categoria_drops_off(int *codigos_stream, int *duraciones_stream, int *codigos_idioma, int *categorias_int,
                                 char *categorias_char, int * reps_antiguas, int * reps_recientes, int * cant_reproducciones,
                                 int * tiempos_totales_repro, double * prom_ratings_canales, double * prom_drops_off, int n_streams) {
    for (int i = 0; i < n_streams-1; i++) {
        for (int j = i+1; j < n_streams; j++) {
            if (categorias_char[i] > categorias_char[j] or
                categorias_char[i] == categorias_char[j] and categorias_int[i] > categorias_int[j] or
                categorias_int[i] == categorias_int[j] and prom_drops_off[i] < prom_drops_off[j]) {
                swap_int(codigos_stream[i], codigos_stream[j]);
                swap_int(duraciones_stream[i], duraciones_stream[j]);
                swap_int(codigos_idioma[i], codigos_idioma[j]);
                swap_int(categorias_int[i], categorias_int[j]);
                swap_char(categorias_char[i], categorias_char[j]);
                swap_int(reps_antiguas[i], reps_antiguas[j]);
                swap_int(reps_recientes[i], reps_recientes[j]);
                swap_int(cant_reproducciones[i], cant_reproducciones[j]);
                swap_int(tiempos_totales_repro[i], tiempos_totales_repro[j]);
                swap_double(prom_ratings_canales[i], prom_ratings_canales[i]);
                swap_double(prom_drops_off[i], prom_drops_off[j]);
            }
        }
    }
}

void imprimir_titulo(ofstream & output, bool report1) {
    imprimir_linea(ANCHO_REPORTE,'=',output);
    if (report1) {
        output<<setw((ANCHO_REPORTE+26)/2)<<"PLATAFORMA DE STREAMING TP"<<endl;
        output<<setw((ANCHO_REPORTE+43)/2)<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS"<<endl;
    }
    else {
        output<<setw((ANCHO_REPORTE+26)/2)<<"PLATAFORMA DE STREAMING TP"<<endl;
        output<<setw((ANCHO_REPORTE+82)/2)<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS ORDENADO POR CATEGORIA Y TASA DROP-OFF"<<endl;
    }
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_cabecera_tablas(ofstream & output) {
    output<<left<<setw(ANCHO_REPORTE/10)<<"STREAM";
    output<<setw(ANCHO_REPORTE/10)<<"IDIOMA";
    output<<setw(ANCHO_REPORTE/10)<<"CATEGORIA";
    output<<setw(ANCHO_REPORTE/10)<<"DURACION";
    output<<setw(ANCHO_REPORTE/10)<<"REP. ANTIGUA";
    output<<setw(ANCHO_REPORTE/10)<<"REP. RECIENTE";
    output<<setw(ANCHO_REPORTE/10)<<"PROM. RAT. CAL";
    output<<setw(ANCHO_REPORTE/10)<<"PROM. TASA DROP-OFF";
    output<<setw(ANCHO_REPORTE/10)<<"#REPRO.";
    output<<setw(ANCHO_REPORTE/10)<<"TOT. REPR."<<endl<<right;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void imprimir_fecha(int fecha, ofstream & output) {
    int aa,mm,dd;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void imprimir_resumen(int mayor_dur, int cod_mayor, int menor_dur, int cod_menor, ofstream & output) {
    output<<"RESUMEN:"<<endl;
    output<<"STREAM CON MAYOR DURACION:     "<<cod_mayor<<" - ";
    imprimir_tiempo(mayor_dur,output);
    output<<" hrs"<<endl;
    output<<"STREAM CON MENOR DURACION:     "<<cod_menor<<" - ";
    imprimir_tiempo(menor_dur,output);
    output<<" hrs"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_reporte(const char *file_name, int *codigos_stream, int *duraciones_stream, int *codigos_idioma, int *categorias_int,
                      char *cateforias_char, int *reps_antiguas, int *reps_recientes, int *cant_reproducciones, int *tiempos_totales_repro,
                      double *prom_ratings_canales, double *prom_drops_off, int n_streams, bool report1) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    imprimir_titulo(output, report1);
    imprimir_cabecera_tablas(output);
    int mayor_dur=0,menor_dur=0,cod_mayor,cod_menor;
    output<<fixed;
    for (int i=0;i<n_streams;i++) {
        output<<left<<setw(ANCHO_REPORTE/10)<<codigos_stream[i];
        output<<setw(ANCHO_REPORTE/10)<<codigos_idioma[i];
        output<<cateforias_char[i]<<categorias_int[i]<<setw(ANCHO_REPORTE/10 - 5)<<""<<right;
        imprimir_tiempo(duraciones_stream[i], output);
        output<<setw(ANCHO_REPORTE/10 - 8)<<"";
        imprimir_fecha(reps_antiguas[i], output);
        output<<setw(ANCHO_REPORTE/10 - 10)<<"";
        imprimir_fecha(reps_recientes[i], output);
        output<<setw(ANCHO_REPORTE/10 - 10)<<"";
        output<<setw(10)<<setprecision(2)<<prom_ratings_canales[i]<<setw(ANCHO_REPORTE/10 - 10)<<"";
        output<<setw(10)<<setprecision(2)<<prom_drops_off[i]<<"%"<<setw(ANCHO_REPORTE/10 - 11)<<"";
        output<<setw(6)<<cant_reproducciones[i]<<setw(ANCHO_REPORTE/10 - 6)<<"";
        imprimir_tiempo(tiempos_totales_repro[i], output);
        output<<endl;
        if (mayor_dur==0 or duraciones_stream[i]>mayor_dur) {
            mayor_dur=duraciones_stream[i];
            cod_mayor=codigos_stream[i];
        }
        if (menor_dur==0 or duraciones_stream[i]<menor_dur) {
            menor_dur=duraciones_stream[i];
            cod_menor=codigos_stream[i];
        }
    }
    imprimir_linea(ANCHO_REPORTE,'-',output);
    if (report1) imprimir_resumen(mayor_dur, cod_mayor, menor_dur, cod_menor, output);
}


int leer_fecha(ifstream & input) {
    int aa,mm,dd;
    char c;
    input>>dd;
    if (input.eof()) return NO_ENCONTRADO;
    input>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

int busqueda_pos(int value, int *arr, int n) {
    for (int i=0;i<n;i++) {
        if (arr[i]==value) return i;
    }
    return NO_ENCONTRADO;
}

void leer_parte_dinamica(int * reps_antiguas, int * reps_recientes, int * cant_reproducciones, int * tiempos_totales_repro,
                         double * prom_ratings_canales, double * prom_drops_off, int n_streams, int * codigos_stream,
                         int *duraciones_stream, ifstream &input) {

    int codigo_stream_leido, fecha_leido, pos_stream;
    double  rating_leido, drop_off_leido;
    char c;

    while (true) {
        input>>codigo_stream_leido;
        fecha_leido=leer_fecha(input);
        input>>ws;
        input.ignore(8,' ');
        input>>rating_leido>>drop_off_leido;
        pos_stream=busqueda_pos(codigo_stream_leido, codigos_stream,n_streams);
        if (pos_stream!=NO_ENCONTRADO) {
            if (reps_antiguas[pos_stream] == 0 or reps_antiguas[pos_stream] > fecha_leido) {
                reps_antiguas[pos_stream] = fecha_leido;
            }
            if (reps_recientes[pos_stream] == 0 or reps_recientes[pos_stream] < fecha_leido) {
                reps_recientes[pos_stream] = fecha_leido;
            }
            cant_reproducciones[pos_stream] ++;
            tiempos_totales_repro[pos_stream] += duraciones_stream[pos_stream];
            prom_ratings_canales[pos_stream] = (prom_ratings_canales[pos_stream]*((cant_reproducciones[pos_stream]==1) + (cant_reproducciones[pos_stream]!=1)*(cant_reproducciones[pos_stream] - 1))
                                                + rating_leido)/cant_reproducciones[pos_stream];
            prom_drops_off[pos_stream] = (prom_drops_off[pos_stream]*((cant_reproducciones[pos_stream]==1) + (cant_reproducciones[pos_stream]!=1)*(cant_reproducciones[pos_stream] - 1))
                                          + drop_off_leido)/cant_reproducciones[pos_stream];
        }
        input.get(c);
        if (c=='\n') break;
    }
}

void cargar_canales(const char *file_name, int *reps_antiguas, int *reps_recientes, int *cant_reproducciones, int *tiempos_totales_repro,
                    double * prom_ratings_canales, double * prom_drops_off, int n_streams, int * codigos_stream, int * duraciones_stream,
                    int * codigos_idioma, int * categorias_int, char * categorias_char) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int fecha,categoria_int_leido;
    char categoria_char_leido;
    while (true) {
        fecha=leer_fecha(input);
        if (fecha==-1 or input.eof()) break;
        input >> ws >> categoria_char_leido >> categoria_int_leido >> ws;
        input.ignore(50, ' ');
        leer_parte_dinamica(reps_antiguas,reps_recientes,cant_reproducciones,tiempos_totales_repro,prom_ratings_canales,
                            prom_drops_off,n_streams,codigos_stream,duraciones_stream,input);
    }
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"Error al abrir el archivo escritura: "<<file_name<<endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i=0;i<n;i++) output.put(c);
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

void probar_carga_streams(const char *file_name, int *codigos_stream, int *duraciones_stream, int *codigos_idioma,
                          int * categorias_int, char *categorias_char,int n_streams) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    output<<setw((ANCHO_REPORTE+26)/2)<<"PRUEBA DE CARGA DE STREAMS"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<left<<setw(ANCHO_REPORTE/4)<<"CODIGO DEL STREAM";
    output<<setw(ANCHO_REPORTE/4)<<"DURACION";
    output<<setw(ANCHO_REPORTE/4)<<"CODIGO DEL IDIOMA";
    output<<setw(ANCHO_REPORTE/4)<<"CATEGORIA"<<endl;

    for (int i=0;i<n_streams;i++) {
        output<<setw(ANCHO_REPORTE/4)<<codigos_stream[i]<<right;
        imprimir_tiempo(duraciones_stream[i], output);
        output<<setw(ANCHO_REPORTE/4 - 8)<<""<<left;
        output<<setw(ANCHO_REPORTE/4)<<codigos_idioma[i];
        output<<categorias_char[i]<<categorias_int[i]<<endl;
    }
    output<<right;
    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream &input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: " << file_name << endl;
        exit(1);
    }
}

int leer_tiempo(ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void insertar_ordenar(int n_streams, int codigo_stream, int duracion, int codigo_idioma, int categoria_int, char categoria_char,
                     int * codigos_stream, int * duraciones_stream, int * codigos_idioma, int * categorias_int, char * categorias_char) {
    int i=n_streams-1;

    while (i>=0 and codigos_stream[i]>codigo_stream) {
        codigos_stream[i+1]=codigos_stream[i];
        duraciones_stream[i+1]=duraciones_stream[i];
        codigos_idioma[i+1]=codigos_idioma[i];
        categorias_int[i+1]=categorias_int[i];
        categorias_char[i+1]=categorias_char[i];
        i--;
    }
    codigos_stream[i+1]=codigo_stream;
    duraciones_stream[i+1]=duracion;
    codigos_idioma[i+1]=codigo_idioma;
    categorias_int[i+1]=categoria_int;
    categorias_char[i+1]=categoria_char;
}

void cargar_streams(const char *file_name, int *codigos_stream, int *duraciones_stream, int *codigos_idioma,
                    int *categorias_int, char *categorias_char,int &n_streams) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int codigo_stream, duracion, codigo_idioma, categoria_int;
    char categoria_char;

    while (true) {
        input>>codigo_stream;
        if (input.eof()) break;
        duracion = leer_tiempo(input);
        input>>codigo_idioma>>ws>>categoria_char>>categoria_int;
        insertar_ordenar(n_streams,codigo_stream,duracion,codigo_idioma,categoria_int,categoria_char,
                         codigos_stream,duraciones_stream,codigos_idioma,categorias_int, categorias_char);
        n_streams++;
    }
}
