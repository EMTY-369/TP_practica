//
// Created by User on 4/07/2026.
//

#include "Funciones.hpp"

void insertar_ordenado(ListaPalabra &lista_palabra, const struct Palabra & palabra) {
    struct Nodo *nuevo_nodo;
    nuevo_nodo = new Nodo;
    inicializar_nodo(nuevo_nodo, nullptr, nullptr);
    nuevo_nodo->dato = palabra;

    struct Nodo *recorrido = lista_palabra.inicio, *anterior = nullptr;

    while (recorrido != nullptr) {
        if (palabra.cantidad > recorrido->dato.cantidad or (palabra.cantidad == recorrido->dato.cantidad
            and strcmp(palabra.preproc, recorrido->dato.preproc)<0)) break;
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }
    nuevo_nodo->siguiente = recorrido;
    if (anterior == nullptr) lista_palabra.inicio = nuevo_nodo;
    else anterior->siguiente = nuevo_nodo;
}

void cargar_frecuencia(const char * file_name, ListaPalabra &lista_frecuencias) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    inicializar_lista(lista_frecuencias);

    char *cadena;
    while (true) {
        cadena = leer_candena(input, ',');
        if (cadena == nullptr or input.eof()) break;
        struct Palabra palabra_leida;
        input>>palabra_leida.cantidad;
        input.ignore();
        palabra_leida.preproc = cadena;
        insertar_ordenado(lista_frecuencias, palabra_leida);
    }
}


void imprimir_lista_palabras(const char * file_name, ListaPalabra &palabras) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    struct Nodo *recorrido = palabras.inicio;
    while (recorrido != nullptr) {
        output<<recorrido->dato.preproc<<","<<recorrido->dato.cantidad<<endl;
        recorrido = recorrido->siguiente;
    }
    output.close();
}


void eliminar_palabras_stopwords(ListaPalabra &lista_palabra, ListaPalabra &palabras) {
    struct Nodo *pos_palabra, *recorrido = palabras.inicio, *anterior = nullptr, *aux=nullptr;

    while (recorrido != nullptr) {
        pos_palabra = buscar_palabra_prepoce(lista_palabra, recorrido->dato.preproc);

        if (pos_palabra != nullptr) {
            aux = recorrido;
            if (recorrido->siguiente == nullptr) palabras.fin = anterior;
            if (anterior == nullptr) palabras.inicio = recorrido->siguiente;
            else anterior->siguiente = recorrido->siguiente;
            recorrido = recorrido->siguiente;
            delete aux;
            continue;
        }
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }
}

struct Nodo * buscar_palabra_prepoce(ListaPalabra &palabras, char * prepoc) {
    struct Nodo *recorrido=palabras.inicio;
    while (recorrido != nullptr) {
        if (strcmp(prepoc, recorrido->dato.preproc) == 0) {
            recorrido->dato.cantidad++;
            return recorrido;
        }
        recorrido = recorrido->siguiente;
    }
    return nullptr;
}

void insertar_ordenado_sin_repeticion(ListaPalabra & palabras, char * tokken_original, char *tokken_prepoc) {
    struct Nodo *pos;
    pos = buscar_palabra_prepoce(palabras, tokken_prepoc);
    if (pos != nullptr) return;
    char *cadena1, *cadena2;
    cadena1 = asignar_cadena(tokken_original);
    cadena2 = asignar_cadena(tokken_prepoc);
    insertar_nodo_final(palabras, cadena2, cadena1);
}

void insertar_palabras_listas(ListaPalabra & palabras, char * comentario_leido) {
    char tokken_original[40]{}, tokken_prepoc[40]{};
    int k=0, j=0;
    bool termino1 = false, termino2 = false, is_word = false;
    for (int i = 0; i < strlen(comentario_leido) + 1; i++) {
        if (comentario_leido[i] != ' ' and comentario_leido[i]!='\0') {
            tokken_original[j] = comentario_leido[i];
            j++;
            termino1 = false;
        } else if (comentario_leido[i]==' ' or comentario_leido[i]=='\0') termino1 = true;

        if ((comentario_leido[i] <= 'Z' and comentario_leido[i] >= 'A') or (comentario_leido[i] <= 'z' and comentario_leido[i] >= 'a')) {
            if (comentario_leido[i] <= 'Z' and comentario_leido[i] >= 'A') tokken_prepoc[k]  = tolower(comentario_leido[i]);
            else tokken_prepoc[k] = comentario_leido[i];
            k++;
            termino2 = false;
            is_word = true;
        }else termino2 = true;

        if (termino1 and termino2) {
            k = 0;
            j = 0;
            if (is_word) {
                insertar_ordenado_sin_repeticion(palabras, tokken_original, tokken_prepoc);
                is_word = false;
            }
        }
        tokken_original[j] = '\0';
        tokken_prepoc[k] = '\0';
    }
}

void cargar_palabras(const char * file_name, ListaPalabra &palabras) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    inicializar_lista(palabras);
    int cod;
    char *comentario_leido;
    while (true) {
        input>>cod;
        if (input.eof()) break;
        input.ignore();
        input.ignore(50, ',');
        comentario_leido = leer_candena(input, '\n');
        insertar_palabras_listas(palabras, comentario_leido);
    }
    input.close();
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

void prueba_carga(const char * file_name, const char *file_title, ListaPalabra &lista_palabra, bool extra) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    centrear(file_title, 70, true,output);
    imprimir_linea(70, '=', true, output);
    struct Nodo *recorrido = lista_palabra.inicio;
    while (recorrido != nullptr) {
        output<<left<<setw(50)<<recorrido->dato.preproc<<right;
        //centrear(recorrido->dato.preproc, 70, true, output);
        if (extra) output<<recorrido->dato.cantidad;
        output<<endl;
        recorrido = recorrido->siguiente;
    }
    output.close();
}


char * leer_candena( ifstream & input, char del) {
    char *cadena, buffer[60]{};
    input.getline(buffer,60, del);
    if (input.eof()) return nullptr;
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

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura: " << file_name << endl;
        exit(1);
    }
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: " << file_name << endl;
        exit(1);
    }
}

void inicializar_nodo(struct Nodo *& nodo, char * prepoc, char *original) {
    nodo->siguiente = nullptr;
    nodo->dato.preproc = prepoc;
    nodo->dato.original = original;
    nodo->dato.cantidad = 1;
}

void insertar_nodo_final(ListaPalabra & lista_palabra, char *prepoc, char *original) {
    struct Nodo *nuevo_nodo;
    nuevo_nodo = new Nodo;
    inicializar_nodo(nuevo_nodo, prepoc, original);

    if (lista_palabra.fin == nullptr and lista_palabra.inicio == nullptr) lista_palabra.inicio = nuevo_nodo;
    else lista_palabra.fin->siguiente = nuevo_nodo;
    lista_palabra.fin = nuevo_nodo;
}

void inicializar_lista(ListaPalabra & lista_palabra) {
    lista_palabra.fin = nullptr;
    lista_palabra.inicio = nullptr;
}

void cargar_stopwrods(const char * file_name, ListaPalabra &lista_stopwords) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    inicializar_lista(lista_stopwords);

    char *cadena;
    while (true) {
        cadena = leer_candena(input, '\n');
        if (cadena == nullptr or input.eof()) break;
        insertar_nodo_final(lista_stopwords, cadena, nullptr);
    }
    input.close();
}
