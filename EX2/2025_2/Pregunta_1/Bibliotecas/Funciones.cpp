//
// Created by User on 3/07/2026.
//

#include "Funciones.hpp"

void imprimir_reporte_final(const char * file_name, Transmision *& transmisiones, int n_transmisiones) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    centrear("REPORTE DE TRANSMISIONES", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_transmisiones; i++) {
        imprimir_titulos_encabezado(output);
        imprimir_datos_transmision(transmisiones[i], output);
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
        output<<"COMENTARIOS DE LA TRANSMISION 5002:"<<endl;
        imprimir_linea(8 + 22, ' ', false, output);
        centrear("ORIGINAL", 60, false, output);
        centrear("PRE-PROCESADO", 50, true, output);
        for (int j = 0; j < transmisiones[i].cantidad_comentarios; j++) {
            imprimir_linea(8, ' ', false, output);
            output<<left<<setw(22)<<transmisiones[i].comentarios[j].comentador;
            output<<setw(60)<<transmisiones[i].comentarios[j].comentario_original<<right;

            output<<transmisiones[i].comentarios[j].comentario_pre_procesado<<endl;
            cout<<transmisiones[i].comentarios[j].comentario_pre_procesado<<endl;
        }
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
    }
    output.close();
}


int buscar_stream(Transmision *& transmision, int n_transmisiones, int cod_transmision) {

    for (int i = 0; i < n_transmisiones; i++) {
        if (transmision[i].id_transmision == cod_transmision) return i;
    }
    return -1;
}

char *pre_procesado_comentario(char *origen) {
    char tokken[60]{};
    int k=0;
    for (int i = 0; origen[i]; i++) {
        if ((origen[i] <= 'Z' and origen[i] >= 'A') or (origen[i] <= 'z' and origen[i] >= 'a')) {
            if (origen[i] <= 'Z' and origen[i] >= 'A') tokken[k]  = tolower(origen[i]);
            else tokken[k] = origen[i];
            k++;
        }
    }
    return asignar_cadena(tokken);
}

void cargar_comentarios(const char * file_name, Transmision *&transmisiones, int n_transmisiones) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int cod_transmision, pos;
    while (true) {
        input>>cod_transmision;
        if (input.eof()) break;
        input.ignore();
        pos = buscar_stream(transmisiones, n_transmisiones, cod_transmision);
        if (pos == -1) {
            input.ignore(100, '\n');
            continue;
        }
        int n = transmisiones[pos].cantidad_comentarios;
        transmisiones[pos].comentarios[n].id_transmision = cod_transmision;
        transmisiones[pos].comentarios[n].comentador  = leer_candena(input,',');
        transmisiones[pos].comentarios[n].comentario_original = leer_candena(input,'\n');
        transmisiones[pos].comentarios[n].comentario_pre_procesado = pre_procesado_comentario(transmisiones[pos].comentarios[n].comentario_original);
        transmisiones[pos].cantidad_comentarios++;
    }
}

void imprimir_titulos_encabezado( ofstream & output) {
    output<<left<<setw(ANCHO_REPORTE/7)<<"ID TRANSMISION"<<setw(ANCHO_REPORTE/7 - 4)<<"FECHA";
    output<<setw(ANCHO_REPORTE/7 - 6)<<"DURACION"<<setw(ANCHO_REPORTE/7)<<"ID STREAMER";
    output<<setw(ANCHO_REPORTE/7 + 4)<<"NOMBRE CANAL"<<setw(ANCHO_REPORTE/7)<<"CATEGORIA";
    output<<setw(ANCHO_REPORTE/7 + 6)<<"CANTIDAD DE SEGUIDORES"<<endl<<right;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
}

void imprimir_datos_transmision(const Transmision & transmision, ofstream & output) {
    output<<left<<setw(ANCHO_REPORTE/7)<<transmision.id_transmision<<right;
    imprimir_fecha(transmision.fecha, output);
    imprimir_linea(ANCHO_REPORTE/7 - 14, ' ', false, output);
    output<<left<<setw(ANCHO_REPORTE/7 - 6)<<transmision.duracion<<setw(ANCHO_REPORTE/7)<<transmision.streamer.id_streamer;
    output<<setw(ANCHO_REPORTE/7 + 4)<<transmision.streamer.nombre_canal<<setw(ANCHO_REPORTE/7)<<transmision.streamer.categoria;
    output<<setw(ANCHO_REPORTE/7 + 6)<<transmision.streamer.cantidad_seguidores<<endl<<right;
}

void prueba_carga_streamers(const char * file_name, Transmision *&transmisiones, int n_transmisiones) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    centrear("PRUEBA DE CARGA DE LOS STREAMERS", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    imprimir_titulos_encabezado(output);
    for (int i = 0; i < n_transmisiones; i++) {
        imprimir_datos_transmision(transmisiones[i], output);
    }
    output.close();
}

char * leer_candena( ifstream & input, char del) {
    char *cadena, buffer[60]{};
    input.getline(buffer,60, del);
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

char * asignar_cadena(char * origen) {
    char *cadena;
    cadena = new char[strlen(origen)+1];
    strcpy(cadena, origen);
    return cadena;
}

void buscar_insertar_streamers(Transmision *&transmisiones, int n_transmisiones, int id_streamer_leido, char * canal, char * categoria,
                               int cant_seguidores) {
    for (int i = 0; i < n_transmisiones; i++) {
        if (transmisiones[i].streamer.id_streamer == id_streamer_leido) {
            transmisiones[i].streamer.nombre_canal = asignar_cadena(canal);
            transmisiones[i].streamer.categoria = asignar_cadena(categoria);
            transmisiones[i].streamer.cantidad_seguidores = cant_seguidores;
        }
    }
}

void cargar_streamers(const char * file_name, Transmision *&transmisiones, int n_transmisiones) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int id_streamer_leido, cant_seguidores;
    char *canal, *categoria;
    while (true) {
        input>>id_streamer_leido;
        if (input.eof()) break;
        input.ignore();
        canal = leer_candena(input, ',');
        categoria = leer_candena(input, ',');
        cant_seguidores = leer_int(input);
        buscar_insertar_streamers(transmisiones, n_transmisiones, id_streamer_leido, canal, categoria, cant_seguidores);
    }
    input.close();
}


void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura: " << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slas_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slas_n) output.put('\n');
}

void centrear(const char * texto, int espacio, bool slas_n, ofstream & output) {
    int n = strlen(texto);
    output << setw((espacio + n)/2) << texto;
    imprimir_linea(espacio - (espacio + n)/2, ' ', slas_n, output);
}

void imprimir_fecha(int fecha, ofstream & output) {
    int dd, mm, aa;
    aa = fecha/10000;
    fecha %= 10000;
    mm = fecha/100;
    dd = fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"-"<<setw(2)<<mm<<"-"<<setw(2)<<aa<<setfill(' ');
}

void prueba_carga_transmisiones(const char * file_name, Transmision *&transmisiones, int n_transmisiones) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    centrear("PRUEBA DE CARGA DE LAS TRANSMISIONES", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/4)<<"CODIGO TRANSMISION"<<setw(ANCHO_REPORTE/4)<<"CODIGO STREAMER";
    output<<setw(ANCHO_REPORTE/4)<<"DURACION"<<setw(ANCHO_REPORTE/4)<<"FECHA"<<endl<<right;
    for (int i = 0; i < n_transmisiones; i++) {
        output<<left<<setw(ANCHO_REPORTE/4)<<transmisiones[i].id_transmision<<setw(ANCHO_REPORTE/4)<<transmisiones[i].streamer.id_streamer;
        output<<setw(ANCHO_REPORTE/4)<<transmisiones[i].duracion;
        imprimir_fecha(transmisiones[i].fecha, output);
        output<<endl;
    }
    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: " << file_name << endl;
        exit(1);
    }
}

int leer_int( ifstream & input) {
    int dato;
    input>>dato;
    input.ignore();
    return dato;
}

int leer_fecha( ifstream & input) {
    int dd, mm, aa;
    dd = leer_int(input);
    mm = leer_int(input);
    aa = leer_int(input);
    return dd + mm*100 + aa*10000;
}

void cargar_transmisiones(const char * file_name, Transmision *& transmisiones, int &n_transmisiones) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    transmisiones = new Transmision[MAX_TRANSMISIONES]{};

    int cod_transmision;
    while (true) {
        input>>cod_transmision;
        if (input.eof()) break;
        input.ignore();
        transmisiones[n_transmisiones].streamer.id_streamer = leer_int(input);
        transmisiones[n_transmisiones].fecha = leer_fecha(input);
        transmisiones[n_transmisiones].duracion = leer_int(input); //esta en minutos
        transmisiones[n_transmisiones].id_transmision = cod_transmision;
        transmisiones[n_transmisiones].comentarios = new Comentario[MAX_COMENTARIOS]{};
        n_transmisiones++;
    }
    input.close();
}


