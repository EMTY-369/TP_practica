//
// Created by User on 03/05/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP

#include "Utils.hpp"

void cargar_canales(const char *file_name, int *fecha_canales, int *codigos_int_canales, char *codigos_char_canales,
                    double *ratings_canales, int &n_canales);
void abrir_archivo_lectura(ifstream &input, const char *file_name);
int leer_fecha(ifstream &input);
void probar_canales(const char *file_name, int *fecha_canales, int *codigos_int_canales, char *codigos_char_canales,
                    double *ratings_canales, int n_canales);
void abrir_archivo_escritura(ofstream &output, const char *file_name);
void imprimir_linea(int n, char c, ofstream &output);
void imprimir_fecha(int fecha, ofstream &output);
void cargar_etiquetas(const char *file_name, int *codigos_etiquetas, int *tiempo_duracion_etiquetas, int &n_etiquetas);
int leer_duracion(ifstream & input);
void probar_etiquetas(const char *file_name, int *codigos_etiquetas, int *tiempo_duracion_etiquetas, int n_etiquetas);
void imprimir_tiempo(int tiempo, ofstream &output);
void procesar_reproducciones(const char *file_name, char *codigos_char_canales, int *codigos_int_canales,
                             int * codigos_etiquetas, double * ratings_canales,int * tiempo_duracion_etiquetas,
                             int * cant_total_reproducciones_canales, int * cant_total_reproducciones_etiquetas,
                             double * ingresos_por_reproducciones, int * tiempo_total_reproducciones_canales,
                             int * tiempo_total_reproducciones_etiquetas, int n_canales, int n_etiquetas, double tarifa);
int buscar_canal(char * codigos_char_canales, int * codigos_int_canales, char codigo_char_canal_leido,
                 int codigo_int_canal_leido, int n_canales);
int buscar_etiqueta(int * codigos_etiquetas, int codigo_etiqueta_leido, int n_etiquetas);
double calcular_ingreso(int tiempo, int reproducciones, double rating, double tarifa);
void generar_reporte(const char *file_name, int * fecha_canales, char * codigos_char_canales, int * codigos_int_canales,
                    double * ratings_canales, int n_canales, int * codigos_etiquetas, int * tiempo_duracion_etiquetas,
                    int n_etiquetas, int * cant_total_reproducciones_canales, int * cant_total_reproducciones_etiquetas,
                    double * ingresos_por_reproducciones, double tarifa,
                    int * tiempo_total_reproducciones_canales, int * tiempo_total_reproducciones_etiquetas);
void imprimir_titulo(ofstream & output, double tarifa);
void imprimir_titulo_tablas1(ofstream & output);
void imprimir_titulo_tablas2(ofstream & output);


#endif //INC_2025_2_FUNCIONES_HPP
