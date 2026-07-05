//
// Created by User on 4/07/2026.
//

#ifndef PREGUNTA_2_FUNCIONES_HPP
#define PREGUNTA_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/ListaPalabra.hpp"
void cargar_stopwrods(const char * file_name, ListaPalabra &lista_stopwords);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
char * leer_candena( ifstream & input, char del);
char * asignar_cadena(char * origen);
void insertar_nodo_final(ListaPalabra & lista_palabra, char *prepoc, char *original);
void inicializar_nodo(struct Nodo *& nodo, char * prepoc, char *original);
void inicializar_lista(ListaPalabra & lista_palabra);
void prueba_carga(const char * file_name, const char *file_title, ListaPalabra &lista_palabra, bool extra);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_palabras(const char * file_name, ListaPalabra &palabras);
void insertar_palabras_listas(ListaPalabra & palabras, char * comentario_leido);
void insertar_ordenado_sin_repeticion(ListaPalabra & palabras, char * tokken_original, char *tokken_prepoc);
void eliminar_palabras_stopwords(ListaPalabra &lista_palabra, ListaPalabra &palabras);
struct Nodo * buscar_palabra_prepoce(ListaPalabra &palabras, char * prepoc);
void imprimir_lista_palabras(const char * file_name, ListaPalabra &palabras);
void cargar_frecuencia(const char * file_name, ListaPalabra &lista_frecuencias);
void insertar_ordenado(ListaPalabra &lista_palabra, const struct Palabra & palabra);



#endif //PREGUNTA_2_FUNCIONES_HPP
