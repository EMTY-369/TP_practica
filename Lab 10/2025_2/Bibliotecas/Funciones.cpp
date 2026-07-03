//
// Created by User on 29/06/2026.
//

#include "Funciones.hpp"

void eliminar_lista_por_dropp_off(ListaCategoria &lista_categoria, double valor) {
    struct Nodo *recorrido = lista_categoria.inicio;
    struct Nodo *anterior = nullptr;

    while (recorrido != nullptr) {
        if (recorrido->dato.promedioDropoff < valor) {
            if (anterior != nullptr) anterior->siguiente = recorrido->siguiente;
            else lista_categoria.inicio = recorrido->siguiente;
            recorrido = recorrido->siguiente;
            continue;
        }
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }
}

void imprimir_duracion(int tiempo, ofstream & output) {
    int horas, minutos, segundos;
    horas = tiempo/3600;
    tiempo = tiempo%3600;
    minutos = tiempo/60;
    segundos = tiempo%60;
    output<<setfill('0')<<setw(2)<<horas<<":"<<setw(2)<<minutos<<":"<<setw(2)<<segundos<<setfill(' ');
}

void imprimir_reporte(const char * file_name,const ListaCategoria &lista_categorias) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    output<<fixed;
    output.precision(2);

    struct Nodo *recorrido = lista_categorias.inicio;
    centrear("REPORTE POR CATEGORIAS", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    while (recorrido != nullptr) {
        imprimir_encabezado(recorrido->dato, output);
        output<<"INFORMACION DE LAS REPRODUCCIONES:"<<endl<<"DURACION MAXIMA:"<<endl;
        output<<left<<setw(20)<<"NOMBRE DE CANAL:"<<recorrido->dato.canalConDuracionMaxima<<endl;
        output<<setw(20)<<"DURACION:"<<right;
        imprimir_duracion(recorrido->dato.duracionMaxima, output);
        output<<endl;
        imprimir_linea(ANCHO_REPORTE,'-',true, output);
        output<<"LISTA DE DROP-OFF:";
        if (recorrido->dato.cantidadDeReproducciones > 0) {
            for (int i = 0; i < recorrido->dato.cantidadDeReproducciones; i++) {
                output<<setw(6)<<recorrido->dato.arrDropOff[i];
            }
            output<<endl;
        }
        output<<"PROMEDIO DE DROP-OFF:"<<setw(14)<<recorrido->dato.promedioDropoff<<endl;
        output<<"TIEMPO DE DURACION TOTAL:   ";
        imprimir_duracion(recorrido->dato.duracionTotal, output);
        output<<endl;
        imprimir_linea(ANCHO_REPORTE,'=',true, output);

        recorrido = recorrido->siguiente;
    }
}

void calcular_promedios_dropp_off(ListaCategoria &lista_categorias) {
    struct Nodo *recorrido = lista_categorias.inicio;

    while (recorrido != nullptr) {
        int n = recorrido->dato.cantidadDeReproducciones;
        double  suma_drop_off=0;
        if (n!=0) {
            for (int i = 0; i < n; i++) {
                suma_drop_off += recorrido->dato.arrDropOff[i];
            }
            recorrido->dato.promedioDropoff = suma_drop_off/n;
        }
        recorrido = recorrido->siguiente;
    }
}

struct Nodo * buscar_categoria(char * codigo_leido, const struct ListaCategoria &lista_categorias) {
    struct Nodo *recorrido = lista_categorias.inicio;
    while (recorrido != nullptr) {
        if (strcmp(recorrido->dato.codigo, codigo_leido) == 0) return recorrido;
        recorrido = recorrido->siguiente;
    }
    return nullptr;
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

int leer_duracion( ifstream & input) {
    int horas, minutos, segundos;
    horas = leer_int(input);
    minutos = leer_int(input);
    segundos = leer_int(input);
    return horas*3600 + minutos*60 + segundos;
}

void cargar_streams(const char * file_name, struct  ListaCategoria &lista_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    char *codigo_leido, *canal;
    double drop_off;
    int duracion;
    struct Nodo *pos_categoria;
    while (true) {
        codigo_leido = leer_cadena(input, ',');
        if (codigo_leido == nullptr or input.eof()) break;
        canal = leer_cadena(input, ',');
        drop_off = leer_double(input);
        duracion = leer_duracion(input);
        pos_categoria = buscar_categoria(codigo_leido, lista_categorias);
        if (pos_categoria == nullptr) {
            input.ignore(50, '\n');
            continue;
        }
        int n = pos_categoria->dato.cantidadDeReproducciones;
        if (n==0 or pos_categoria->dato.duracionMaxima < duracion) {
            pos_categoria->dato.canalConDuracionMaxima = canal;
            pos_categoria->dato.duracionMaxima = duracion;
        }
        pos_categoria->dato.duracionTotal += duracion;
        pos_categoria->dato.arrDropOff[n] = drop_off;
        pos_categoria->dato.cantidadDeReproducciones ++;
    }
    input.close();
}

void abrir_archivo_salida(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Se resiste: " << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void centrear(const char *texto, int espacio, bool slash_n, ofstream & output) {
    int n=strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', slash_n, output);
}

void imprimir_encabezado(const struct Categoria &dato, ofstream & output) {
    output<<left<<setw(15)<<"Codigo: "<<dato.codigo<<endl;
    output<<setw(15)<<"Nombre: "<<dato.nombre<<endl;
    output<<setw(15)<<"Descripcion: "<<dato.descripcion<<endl<<right;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
}

void probar_carga_categorias(const char * file_name, const ListaCategoria & lista_categorias) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    centrear("REPORTE POR CATEGORIAS", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    struct Nodo *recorrido = lista_categorias.inicio;
    while (recorrido != nullptr) {
        imprimir_encabezado(recorrido->dato, output);
        recorrido = recorrido->siguiente;
    }
}

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada: " << file_name << endl;
        exit(1);
    }
}

void inicializar_lista_categorias( struct ListaCategoria & lista_categorias) {
    lista_categorias.inicio = nullptr;
    lista_categorias.cant_categorias=0;
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[100]{}, *candena;
    input.getline(buffer, 100, del);
    if ( input.eof() ) return nullptr;
    candena = new char[strlen(buffer)+1];
    strcpy(candena, buffer);
    return candena;
}

char * asignar_cadena(char * buffer) {
    char *candena;
    candena = new char[strlen(buffer)+1];
    strcpy(candena, buffer);
    return candena;
}

void asignar_struct_categoria( struct Categoria & dato, struct Categoria & origen) {
    dato.codigo = asignar_cadena(origen.codigo);
    dato.nombre = asignar_cadena(origen.nombre);
    dato.descripcion = asignar_cadena(origen.descripcion);
}

void insertar_ordenado( struct ListaCategoria & lista_categorias, struct Categoria & c) {
    struct Nodo *nuevo_nodo;
    nuevo_nodo = new Nodo{};
    asignar_struct_categoria(nuevo_nodo->dato, c);
    nuevo_nodo->siguiente = nullptr;

    struct Nodo *recorrido;
    recorrido = lista_categorias.inicio;
    struct Nodo *anterior;
    anterior = nullptr;

    while (recorrido != nullptr) {
        if (strcmp(recorrido->dato.codigo, c.codigo) > 0) break;
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }

    nuevo_nodo->siguiente = recorrido;
    if (anterior != nullptr) anterior->siguiente = nuevo_nodo;
    else lista_categorias.inicio = nuevo_nodo;
    lista_categorias.cant_categorias++;
}

void cargar_categorias(const char * file_name,struct ListaCategoria & lista_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    inicializar_lista_categorias(lista_categorias);

    char *codigo;
    while (true) {
        codigo = leer_cadena(input, ',');
        if (codigo == nullptr or input.eof()) break;
        struct Categoria c{};
        c.nombre = leer_cadena(input, ',');
        c.descripcion = leer_cadena(input, '\n');
        c.codigo = codigo;
        insertar_ordenado(lista_categorias, c);
    }

    input.close();
}
