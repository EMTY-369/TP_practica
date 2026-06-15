//
// Created by User on 15/06/2026.
//

#ifndef INC_2024_2_FUNCIONES_HPP
#define INC_2024_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Plato.hpp"
#include "../Estructuras/Cliente.hpp"

void cargar_platos_ofrecidos(const char * file_name, Plato * arr_platos, int &n_platos);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
char * leer_cadena( ifstream & input, char del);
double leer_double( ifstream & input);




#endif //INC_2024_2_FUNCIONES_HPP
