//
// Created by User on 22/06/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Categoria.hpp"

void cargar_categorias(const char * file_name, Categoria *& categoria, int& n_categorias);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
char * leer_cadena( ifstream & input, char del);
void prueba_carga_Reporte_final(const char * file_name, Categoria * categoria, int n_categorias, int fase);
void abrir_archivo_salida(const char * file_name, ofstream & output);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void imprimir_encabezado(const Categoria & categoria, ofstream & output);
void cargar_reproducciones(const char * file_name, Categoria *& categoria, int n_categorias);
int buscar_pos_categoria(char * codigo_ledio, Categoria * categoria, int n_categorias);
double leer_double( ifstream & input);
void leer_duracion(Hora &duracion, ifstream & input);
int leer_int( ifstream & input);
void actualizar_promedios(Categoria *& categoria, int n_categorias);
void imprimir_reproducciones(const Categoria & categoria, ofstream & output, int fase);
void ordenar_nombre_categoria(Categoria *& categoria, int n_categorias);
void swap_struct_cat( Categoria & a, Categoria & b);
void cargar_comentarios(const char * file_name, Categoria *& categoria, int n_categorias);
void buscar_insertar_comentarios(Categoria *& categoria, int n_categorias, char *canal, char *&comentario);
char * asignar_cadena(char * buffer);
void imprimir_comentarios(char ** comentarios, int num_comentarios, ofstream & output);
void ordenar_canales_rating(Categoria *& categoria, int n_categorias);
void swap_struct_repro(Reproduccion & a, Reproduccion & b);



#endif //INC_2025_2_FUNCIONES_HPP
