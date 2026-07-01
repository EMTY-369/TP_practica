//
// Created by User on 29/06/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Categoria.hpp"
#include "../Estructuras/Nodo.hpp"
#include "../Estructuras/ListaCategoria.hpp"


void cargar_categorias(const char * file_name,struct  ListaCategoria & lista_categorias);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
void inicializar_lista_categorias( struct ListaCategoria & lista_categorias);
char * leer_cadena( ifstream & input, char del);
void insertar_ordenado( struct ListaCategoria & lista_categorias, struct Categoria & c);
void asignar_struct_categoria( struct Categoria & dato, struct Categoria & origen);
char * asignar_cadena(char * buffer);
void probar_carga_categorias(const char * file_name, const ListaCategoria & lista_categorias);
void abrir_archivo_salida(const char * file_name, ofstream & output);
void imprimir_encabezado(const struct Categoria &dato, ofstream & output);
void centrear(const char *texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_streams(const char * file_name, struct  ListaCategoria &lista_categorias);
struct Nodo * buscar_categoria(char * codigo_leido, const struct ListaCategoria &lista_categorias);
double leer_double( ifstream & input);
int leer_int( ifstream & input);
int leer_duracion( ifstream & input);
void calcular_promedios_dropp_off(ListaCategoria &lista_categorias);
void imprimir_reporte(const char * file_name,const ListaCategoria &lista_categorias);
void imprimir_duracion(int tiempo, ofstream & output);
void eliminar_lista_por_dropp_off(ListaCategoria &lista_categoria, double valor);


#endif //INC_2025_2_FUNCIONES_HPP
