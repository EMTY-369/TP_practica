//
// Created by User on 10/05/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_streams(const char *file_name, int *codigos_stream, int *duraciones_stream, int *codigos_idioma,
                    int *catergorias_int, char *categorias_char,int &n_streams);
void abrir_archivo_lectura(const char * file_name, ifstream &input);
int leer_tiempo(ifstream & input);
void insertar_ordenar(int n_streams, int codigo_stream, int duracion, int codigo_idioma, int categoria_int, char categoria_char,
                     int * codigos_stream, int * duraciones_stream, int * codigos_idioma, int * categorias_int, char * categorias_char);
void probar_carga_streams(const char *file_name, int *codigos_stream, int *duraciones_stream, int *codigos_idioma,
                         int * categorias_int, char *categorias_char,int n_streams);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_tiempo(int tiempo, ofstream & output);
void cargar_canales(const char *file_name, int *reps_antiguas, int *reps_recientes, int *cant_reproducciones, int *tiempos_totales_repro,
                   double * prom_ratings_canales, double * prom_drops_off, int n_streams, int * codigos_stream, int * duraciones_stream,
                   int * codigos_idioma, int * categorias_int, char * categorias_char);
int leer_fecha(ifstream & input);
void leer_parte_dinamica(int * reps_antiguas, int * reps_recientes, int * cant_reproducciones,
                         int * tiempos_totales_repro, double * prom_ratings_canales, double * prom_drops_off, int n_streams, int * codigos_stream,
                         int * duraciones_stream, ifstream &input);
int busqueda_pos(int value, int *arr, int n);
void imprimir_reporte(const char *file_name, int *codigos_stream, int *duraciones_stream, int *codigos_idioma, int *categorias_int,
                      char *cateforias_char, int *reps_antiguas, int *reps_recientes, int *cant_reproducciones, int *tiempos_totales_repro,
                      double *prom_ratings_canales, double *prom_drops_off, int n_streams, bool report1);
void imprimir_titulo(ofstream & output, bool report1);
void imprimir_cabecera_tablas(ofstream & output);
void imprimir_fecha(int fecha, ofstream & output);
void imprimir_resumen(int mayor_dur, int cod_mayor, int menor_dur, int cod_menor, ofstream & output);
void ordenar_categoria_drops_off(int *codigos_stream, int *duraciones_stream, int *codigos_idioma, int *categorias_int,
                                 char *categorias_char, int * reps_antiguas, int * reps_recientes, int * cant_reproducciones,
                                 int * tiempos_totales_repro, double * prom_ratings_canales, double * prom_drops_off, int n_streams);
void swap_int(int &value_i, int &value_j);
void swap_double(double &value_i, double &value_j);
void swap_char(char &value_i, char &value_j);

#endif //INC_2025_2_FUNCIONES_HPP
