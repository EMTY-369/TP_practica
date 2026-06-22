//
// Created by User on 22/06/2026.
//

#include "Funciones.hpp"

void swap_struct_repro(Reproduccion & a, Reproduccion & b) {
    Reproduccion aux = a;
    a = b;
    b = aux;
}

void ordenar_canales_rating(Categoria *& categoria, int n_categorias) {
    for (int i = 0; i < n_categorias; i++) {
        int n=categoria[i].numReproducciones;
        for (int j = 0; j < n-1; j++) {
            for (int k = j+1; k < n; k++) {
                if (categoria[i].reproducciones[j].rating > categoria[i].reproducciones[k].rating) {
                    swap_struct_repro(categoria[i].reproducciones[j], categoria[i].reproducciones[k]);
                }
            }
        }
    }
}

char * asignar_cadena(char * buffer) {
    char *cadena;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void buscar_insertar_comentarios(Categoria *& categoria, int n_categorias, char *canal, char *&comentario) {
    for (int i = 0; i < n_categorias; i++) {
        for (int j = 0; j < categoria[i].numReproducciones; j++) {
            if (strcmp(categoria[i].reproducciones[j].canal, canal) == 0) {
                int n=categoria[i].reproducciones[j].numComentarios;
                categoria[i].reproducciones[j].comentarios[n] = asignar_cadena(comentario);
                categoria[i].reproducciones[j].numComentarios++;
            }
        }
    }
}

void cargar_comentarios(const char * file_name, Categoria *& categoria, int n_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    char *canal, *comentario;
    while (true) {
        canal = leer_cadena(input, ',');
        if (canal == nullptr or input.eof()) {
            delete []canal;
            break;
        }
        comentario = leer_cadena(input, '\n');
        buscar_insertar_comentarios(categoria, n_categorias, canal, comentario);
    }
}

void swap_struct_cat( Categoria & a, Categoria & b) {
    Categoria aux = a;
    a = b;
    b = aux;
}

void ordenar_nombre_categoria(Categoria *& categoria, int n_categorias) {
    for (int i = 0; i < n_categorias-1; i++) {
        for (int j = i+1; j < n_categorias; j++) {
            if (strcmp(categoria[i].nombre, categoria[j].nombre) > 0) {
                swap_struct_cat(categoria[i], categoria[j]);
            }
        }
    }
}

int buscar_pos_categoria(char * codigo_ledio, Categoria * categoria, int n_categorias) {
    for (int i = 0; i < n_categorias; i++) {
        if (strcmp(codigo_ledio, categoria[i].codigo) == 0) return i;
    }
    return NO_ENCONTRADO;
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.ignore();
    return dato;
}

int leer_int( ifstream & input) {
    int dato;
    input>>dato;
    input.ignore();
    return dato;
}

void leer_duracion(Hora &duracion, ifstream & input) {
    duracion.hora = leer_int(input);
    duracion.minuto = leer_int(input);
    duracion.segundo = leer_int(input);
    duracion.hora_segundos = duracion.hora*3600 + duracion.minuto*60 + duracion.segundo;
}

void actualizar_promedios(Categoria *& categoria, int n_categorias) {
    for (int i = 0; i < n_categorias; i++) {
        if (categoria[i].numReproducciones > 0) categoria[i].promedioRating /= categoria[i].numReproducciones;
    }
}

void cargar_reproducciones(const char * file_name, Categoria *& categoria, int n_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    char *canal, *codigo_ledio;
    int pos_categoria;

    while (true) {
        canal = leer_cadena(input, ',');
        if (canal == nullptr or input.eof()) {
            delete [] canal;
            break;
        }
        codigo_ledio = leer_cadena(input, ',');
        pos_categoria = buscar_pos_categoria(codigo_ledio, categoria, n_categorias);
        if (pos_categoria == NO_ENCONTRADO) {
            input.ignore(100, '\n');
            continue;
        }
        int n=categoria[pos_categoria].numReproducciones;
        categoria[pos_categoria].reproducciones[n].comentarios = new char*[MAX_COMENTARIOS]{};
        categoria[pos_categoria].reproducciones[n].canal=canal;
        categoria[pos_categoria].reproducciones[n].rating=leer_double(input);
        leer_duracion(categoria[pos_categoria].reproducciones[n].duracion,input);
        categoria[pos_categoria].promedioRating += categoria[pos_categoria].reproducciones[n].rating;
        categoria[pos_categoria].duracionTotal.hora_segundos += categoria[pos_categoria].reproducciones[n].duracion.hora_segundos;
        categoria[pos_categoria].numReproducciones++;
    }
    actualizar_promedios(categoria, n_categorias);
}

void abrir_archivo_salida(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo de salida." << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void centrear(const char * texto, int espacio, bool slash_n, ofstream & output) {
    int n=strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', slash_n, output);
}

void imprimir_encabezado(const Categoria & categoria, ofstream & output) {
    output<<setw(14)<<left<<"Codigo:"<<categoria.codigo<<endl;
    output<<setw(14)<<"Nombre:"<<categoria.nombre<<endl;
    output<<setw(14)<<"Descripcion:"<<categoria.descripcion<<endl<<right;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
}

void imprimir_comentarios(char ** comentarios, int num_comentarios, ofstream & output) {
    output<<"    COMENTARIOS:"<<endl;
    for (int i = 0; i < num_comentarios; i++) {
        output<<"     - "<<comentarios[i]<<endl;
    }
}

void imprimir_reproducciones(const Categoria & categoria, ofstream & output, int fase) {
    output<<"REPRODUCCIONES: "<<endl;
    for (int i = 0; i < categoria.numReproducciones; i++) {
        output<<"CANAL:   "<<left<<setw(25)<<categoria.reproducciones[i].canal;
        output<<"RATING:   "<<setw(10)<<categoria.reproducciones[i].rating<<right;
        output<<"DURACION:   ";
        output<<setfill('0')<<setw(2)<<categoria.reproducciones[i].duracion.hora<<":"<<setw(2)<<categoria.reproducciones[i].duracion.minuto;
        output<<":"<<setw(2)<<categoria.reproducciones[i].duracion.segundo<<setfill(' ')<<endl;
        if (fase == 3) imprimir_comentarios(categoria.reproducciones[i].comentarios, categoria.reproducciones[i].numComentarios, output);
    }
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
}

void prueba_carga_Reporte_final(const char * file_name, Categoria * categoria, int n_categorias, int fase) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    output<<fixed;
    output.precision(2);

    centrear("REPORTE POR CATEGORIAS", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    for (int i = 0; i < n_categorias; i++) {
        imprimir_encabezado(categoria[i], output);
        if (fase == 2 or fase==3) {
            imprimir_reproducciones(categoria[i], output, fase);
        }
    }
    output.close();
}

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada" << endl;
        exit(1);
    }
}

char * leer_cadena( ifstream & input, char del) {
    char  buffer[200]{}, *cadena;
    input.getline(buffer, 200, del);
    if (input.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void cargar_categorias(const char * file_name, Categoria *& categoria, int& n_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    categoria = new Categoria[MAX_CATEGORIAS]{};
    char *codigo;
    while (true) {
        codigo = leer_cadena(input, ',');
        if (codigo == nullptr or input.eof()) {
            delete [] codigo;
            break;
        }
        categoria[n_categorias].codigo = codigo;
        categoria[n_categorias].nombre = leer_cadena(input, ',');
        categoria[n_categorias].descripcion = leer_cadena(input, '\n');
        categoria[n_categorias].reproducciones = new Reproduccion[MAX_REPRODUCCIONES]{};
        n_categorias++;
    }
    input.close();
}
