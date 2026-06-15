//
// Created by User on 15/06/2026.
//

#include "Funciones.hpp"

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada: "<<file_name << endl;
        exit(1);
    }
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[MAX_CADENA]{}, *cadena;
    input>>ws;
    input.getline(buffer, MAX_CADENA, del);
    if (input.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.ignore();
    return dato;
}

void cargar_platos_ofrecidos(const char * file_name, Plato * arr_platos, int &n_platos) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    arr_platos = new Plato[MAX_PLATOS]{};

    char *codigo;
    while (true) {
        codigo = leer_cadena(input, ',');
        if (codigo == nullptr or input.eof()) {
            delete [] codigo;
            break;
        }
        arr_platos[n_platos].descripcion = leer_cadena(input, ',');
        arr_platos[n_platos].precio = leer_double(input);
        arr_platos[n_platos].categoria = leer_cadena(input, '\n');
        arr_platos[n_platos].codigo = codigo;
        n_platos++;
    }
    input.close();
}
