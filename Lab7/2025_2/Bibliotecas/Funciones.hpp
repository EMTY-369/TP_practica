//
// Created by User on 8/06/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP
#include "Utils.hpp"
void generarArchivoEnlace(char * categoria, char *&nomb_arch, char *&enlace);
char * asignar_cadena(char * categoria);
void modificar_cadena(char * cadena);
void cargar_categorias(const char * file_name, char ** arr_lista_categorias, char ** arr_nombres_categorias, int &n_categorias);
void abrir_archivo_lectura(const char * file_name, ifstream & input);

char *leer_cadena(char del, ifstream &input);
void prueba_carga_catergorias(const char * file_name, char ** arr_lista_categorias, char ** arr_nombres_categorias, int n_categorias);
void abrir_archivo_escritura(const char * file_name,  ofstream & output);
void centrear(const char * texto, int espacio, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_streams(const char * file_name, int * arr_fechas_streams, int * arr_duraciones_streams, double * arr_ratings_calidad,
                    double * arr_tasas_dropoffs, char ** arr_nombres_canales, char ** arr_categorias_streams, int &n_streams);
void prueba_carga_streams(const char * file_name, int * arr_fechas_streams, int * arr_duraciones_streams, double * arr_ratings_calidad, double * arr_tasas_dropoffs, char ** arr_nombres_canales,
                          char ** arr_categorias_streams, int n_streams);
int leer_fecha_tiempo(ifstream & input, bool es_fecha);
void imprimir_fecha_hora(int value, ofstream & output, bool es_fecha);
void imprimir_reportes(char ** arr_lista_categorias, char ** arr_nombres_categorias, int n_categorias, int * arr_fechas_streams,
                       int * arr_duraciones_streams, double * arr_tasas_dropoffs, double * arr_ratings_calidad,
                       char ** arr_nombres_canales, char ** arr_categorias_streams, int n_streams);
void imprimir_reproducciones(char * categoria_buscada, int n_streams, int * arr_fechas_streams, int * arr_duraciones_streams, double * arr_tasas_dropoffs,
                            double * arr_ratings_calidad, char ** arr_nombres_canales, char ** arr_categorias_streams, ofstream & output);



#endif //INC_2025_2_FUNCIONES_HPP
