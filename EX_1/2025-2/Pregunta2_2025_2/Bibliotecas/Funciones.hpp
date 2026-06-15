//
// Created by User on 15/05/2026.
//

#ifndef PREGUNTA2_2025_2_FUNCIONES_HPP
#define PREGUNTA2_2025_2_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_streams(const char *file_name, int *arr_codigos_streams, int *arr_duraciones_streams, int *arr_codigos_idiomas,
                    int * arr_categorias_int, char *arr_categorias_char, int &n_streams);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
int leer_tiempo(ifstream & input);
void insertar_ordenar(int cod_stream, int duracion, int cod_idioma, char cat_char, int cat_int, int n_streams,
                     int * arr_codigos_streams, int * arr_duraciones_streams, int * arr_codigos_idiomas, int * arr_categorias_int, char * arr_categorias_char);
void probar_carga_streams(const char *file_name, int *arr_codigos_streams, int *arr_duraciones_streams, int *arr_codigos_idiomas,
                          int *arr_categorias_int, char *arr_categorias_char, int n_streams);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_tiempo(int tiempo, ofstream & output);
void cargar_canales(const char *file_name, int *arr_codigos_streams, int n_streams, int * arr_rep_antiguas,
                    int * arr_rep_recientes, int * arr_n_rep, double * arr_prom_rating, double * arr_prom_drop);
void ignorar(ifstream & input, char del);
int leer_fecha( ifstream & input);
int buscar_stream(int cod_stream_leido, int * arr_codigos_streams, int n_streams);
void imprimir_reporte(const char *file_name, bool report1, int *arr_codigos_streams, int *arr_duraciones_streams,
                      int *arr_codigos_idiomas, int * arr_categorias_int, char *arr_categoria_char, int n_streams,
                      int * arr_rep_antiguas, int * arr_rep_recientes, int * arr_n_rep, double * arr_prom_rating,
                      double * arr_prom_drop);
void imprimir_titulo( ofstream & output, bool report1);
void imprimir_encabezado( ofstream & output);
void imprimir_fecha(int fecha, ofstream & output);
void imprimir_resumen(int cod_mayor, int cod_menor, int menor_dur, int mayor_dur, ofstream & output);
void ordenar_idioma_drop(int *arr_codigos_streams, int * arr_duraciones_streams, int * arr_codigos_idiomas, int * arr_categorias_int,
                         char *arr_categorias_char, int n_streams, int * arr_rep_antiguas, int * arr_rep_recientes, int * arr_n_rep,
                         double * arr_prom_rating, double * arr_prom_drop);


#endif //PREGUNTA2_2025_2_FUNCIONES_HPP
