//
// Created by User on 8/06/2026.
//

#include "Funciones.hpp"
void imprimir_reproducciones(char * categoria_buscada, int n_streams, int * arr_fechas_streams, int * arr_duraciones_streams, double * arr_tasas_dropoffs,
                            double * arr_ratings_calidad, char ** arr_nombres_canales, char ** arr_categorias_streams, ofstream & output) {
    int j=0, duracion_total=0;
    double prom_rating=0, prom_dropoff=0;
    for (int i = 0; i < n_streams; i++) {
        if (strcmp(categoria_buscada, arr_categorias_streams[i]) == 0) {
            imprimir_fecha_hora(arr_fechas_streams[i], output, true);
            imprimir_linea(ANCHO_REPORTE/5 - 10, ' ', false, output);
            output<<left<<setw(ANCHO_REPORTE/5)<<arr_nombres_canales[i]<<right;
            output<<setw(12)<<arr_ratings_calidad[i]<<setw(20)<<arr_tasas_dropoffs[i];
            imprimir_linea(14, ' ', false, output);
            imprimir_fecha_hora(arr_duraciones_streams[i], output, false);
            output<<endl;
            j++;
            duracion_total+=arr_duraciones_streams[i];
            prom_rating+=arr_ratings_calidad[i];
            prom_dropoff+=arr_tasas_dropoffs[i];
        }
    }
    duracion_total/=(j+1);
    prom_rating/=(j+1);
    prom_dropoff/=(j+1);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<"PROMEDIO DE RATING:      "<<prom_rating<<endl;
    output<<"PROMEDIO DE DROP-OFF:    "<<prom_dropoff<<endl;
    output<<"DURACION TOTAL:        ";
    imprimir_fecha_hora(duracion_total, output, false);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
}

void imprimir_reportes(char ** arr_lista_categorias, char ** arr_nombres_categorias, int n_categorias, int * arr_fechas_streams,
                       int * arr_duraciones_streams, double * arr_tasas_dropoffs, double * arr_ratings_calidad,
                       char ** arr_nombres_canales, char ** arr_categorias_streams, int n_streams) {
    ofstream output;
    output<<fixed;
    output<<setprecision(2);

    for (int i = 0; i < n_categorias; i++) {
        char *nombArch, *enlace;
        generarArchivoEnlace(arr_nombres_categorias[i], nombArch, enlace);
        abrir_archivo_escritura(nombArch, output);
        output<<"Codigo: "<<arr_lista_categorias[i]<<endl;
        output<<"Nombre: "<<arr_nombres_categorias[i]<<endl;
        output<<"Enlace: "<<enlace<<endl;
        output<<"REPRODUCCIONES: "<<endl;
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
        output<<left<<setw(ANCHO_REPORTE/5)<<"FECHA"<<setw(ANCHO_REPORTE/5)<<"CANAL"<<right;
        centrear("RATING", ANCHO_REPORTE/5, output);
        centrear("DROP-OFF", ANCHO_REPORTE/5, output);
        centrear("DURACION", ANCHO_REPORTE/5, output);
        output<<endl;
        imprimir_reproducciones(arr_lista_categorias[i], n_streams, arr_fechas_streams, arr_duraciones_streams, arr_tasas_dropoffs,
                                arr_ratings_calidad, arr_nombres_canales, arr_categorias_streams, output);

        output.close();
    }
}

void imprimir_fecha_hora(int value, ofstream & output, bool es_fecha) {
    int a, b, c;
    if (es_fecha) {
        a = value/10000;
        value=value%10000;
        b=value/100;
        c=value%100;
        output<<setfill('0')<<setw(2)<<c<<"/"<<setw(2)<<b<<"/"<<setw(4)<<a<<setfill(' ');
    } else {
        a = value/3600;
        value=value%3600;
        b=value/60;
        c=value%60;
        output<<setfill('0')<<setw(2)<<a<<":"<<setw(2)<<b<<":"<<setw(2)<<c<<setfill(' ');
    }
}

void prueba_carga_streams(const char * file_name, int * arr_fechas_streams, int * arr_duraciones_streams, double * arr_ratings_calidad, double * arr_tasas_dropoffs, char ** arr_nombres_canales,
                          char ** arr_categorias_streams, int n_streams) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output<<setprecision(2);

    centrear("PRUEBA DE CARGA DE LOS STREAMS REPRODUCIDOS", ANCHO_REPORTE, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    centrear("NOMBRE CANAL", ANCHO_REPORTE/6, output);
    centrear("CATEGORIA", ANCHO_REPORTE/6, output);
    centrear("FECHA STREAM", ANCHO_REPORTE/6, output);
    centrear("DURACION", ANCHO_REPORTE/6, output);
    centrear("RATING", ANCHO_REPORTE/6, output);
    centrear("TASA DROP-OFF", ANCHO_REPORTE/6, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_streams; i++) {
        output<<left<<setw(ANCHO_REPORTE/6)<<arr_nombres_canales[i];
        output<<setw(ANCHO_REPORTE/6)<<arr_categorias_streams[i]<<right;
        imprimir_fecha_hora(arr_fechas_streams[i], output, true);
        imprimir_linea(ANCHO_REPORTE/6 - 10, ' ', false, output);
        imprimir_fecha_hora(arr_duraciones_streams[i], output, false);
        output<<setw(16)<<arr_ratings_calidad[i]<<setw(10)<<arr_tasas_dropoffs[i]<<endl;
    }
}

int leer_fecha_tiempo(ifstream & input, bool es_fecha) {
    int dd, mm, aa;
    char c;
    input>>dd;
    if (input.eof()) return NO_ENCONTRADO;
    input>>c>>mm>>c>>aa;
    if (es_fecha) return aa*10000 + mm*100 + dd;
    return dd*3600 + mm*60 + aa;
}

void cargar_streams(const char * file_name, int * arr_fechas_streams, int * arr_duraciones_streams, double * arr_ratings_calidad,
                    double * arr_tasas_dropoffs, char ** arr_nombres_canales, char ** arr_categorias_streams, int &n_streams) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int fecha;
    while (true) {
        fecha=leer_fecha_tiempo(input, true);
        if (fecha == NO_ENCONTRADO or input.eof()) break;
        arr_nombres_canales[n_streams] = leer_cadena(' ', input);
        arr_categorias_streams[n_streams] = leer_cadena(' ', input);
        input>>arr_ratings_calidad[n_streams]>>arr_tasas_dropoffs[n_streams];
        arr_duraciones_streams[n_streams]=leer_fecha_tiempo(input, false);
        arr_fechas_streams[n_streams]=fecha;
        // cout<<left<<setw(70)<<arr_nombres_canales[n_streams]<< arr_categorias_streams[n_streams]<<right<<endl;
        n_streams++;
    }
}

void abrir_archivo_escritura(const char * file_name,  ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura:" << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void centrear(const char * texto, int espacio, ofstream & output) {
    int n=strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2,' ', false, output );
}

void prueba_carga_catergorias(const char * file_name, char ** arr_lista_categorias, char ** arr_nombres_categorias, int n_categorias) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    centrear("PRUEBA DE CARGA DE LAS CATEGORIAS DE STREAMS", ANCHO_REPORTE, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    centrear("CODIGOS DE LAS CATEGORIAS", ANCHO_REPORTE/2, output);
    centrear("NOMBRE DE LA CATEGORIA", ANCHO_REPORTE/2, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_categorias; i++) {
        output<<left<<setw(ANCHO_REPORTE/2)<<arr_lista_categorias[i];
        output<<setw(ANCHO_REPORTE/2)<<arr_nombres_categorias[i]<<right<<endl;
    }

    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de lectura: "<<file_name << endl;
        exit(1);
    }
}

char *leer_cadena(char del, ifstream &input) {
    char buffer[MAX_TAM_CADENA]{}, *cadena;
    input>>ws;
    input.getline(buffer,MAX_TAM_CADENA,del);
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

void cargar_categorias(const char * file_name, char ** arr_lista_categorias, char ** arr_nombres_categorias, int &n_categorias) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    char *cod_cat;
    while (true) {
        cod_cat=leer_cadena(' ', input);
        if (input.eof()) {
            delete [] cod_cat;
            break;
        }
        arr_nombres_categorias[n_categorias]=leer_cadena('\n', input);
        // cout<<arr_nombres_categorias[n_categorias]<<endl;
        arr_lista_categorias[n_categorias]=cod_cat;
        n_categorias++;
    }
    input.close();
}

char * asignar_cadena(char * categoria) {
    char *cadena;
    cadena = new char[strlen(categoria) + 1];
    strcpy(cadena, categoria);
    return cadena;
}

void modificar_cadena(char * cadena) {
    bool mayus=true;
    for (int i = 0; cadena[i]; i++) {
        if (cadena[i] >= 'a' and cadena[i] <= 'z' and mayus) {
            cadena[i] -= 'a' - 'A';
            mayus=false;
        }
        if (cadena[i] == '_') mayus=true;
    }
}

void generarArchivoEnlace(char * categoria, char *&nomb_arch, char *&enlace) {
    char *copia_categoria, base_arch[MAX_TAM_CADENA]="ArchivosDeReporte/", base_enlace[MAX_TAM_CADENA]="https://Laboratorio06_2025_2/ArchivosDeReporte/";
    copia_categoria = asignar_cadena(categoria);
    modificar_cadena(copia_categoria);
    strcat(base_arch, copia_categoria);
    strcat(base_arch, ".txt");
    strcat(base_enlace, copia_categoria);
    nomb_arch = asignar_cadena(base_arch);
    enlace = asignar_cadena(base_enlace);
}
