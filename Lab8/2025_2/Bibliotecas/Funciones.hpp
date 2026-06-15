//
// Created by User on 14/06/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Categoria.hpp"

void cargar_categorias(const char * file_name, Categoria *&arr_categorias, int &cant_categorias);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
char * leer_candena( ifstream & input, char del);
void prueba_categorias(const char * file_name, const char *titulo, Categoria * arr_categorias, int cant_categorias, bool report1);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_streams_reproducidos(const char * file_name, Categoria *&arr_categorias, int cant_categorias);
int leer_duracion( ifstream & input);
int buscar_categoria(char * codigo, Categoria * arr_categorias, int cant_categorias);
double leer_double( ifstream & input);
void calculo_rating_prom_y_duraciones(Categoria * arr_categorias, int cant_categorias);
void imprimir_reporte(const char * file_name, Categoria * arr_categorias, int cant_categorias);
void abrir_archivo_salida(const char * file_name, ofstream & output);
void imprimir_reporte(const char * file_name, Categoria * arr_categorias, int cant_categorias);
void imprimir_duracion(int tiempo, ofstream & output);



#endif //INC_2025_2_FUNCIONES_HPP
