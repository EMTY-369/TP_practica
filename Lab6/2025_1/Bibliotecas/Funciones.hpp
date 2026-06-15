//
// Created by User on 31/05/2026.
//

#ifndef INC_2025_1_FUNCIONES_HPP
#define INC_2025_1_FUNCIONES_HPP
#include "Utils.hpp"
void cargar_infracciones(const char *file_name, int *arr_codigo_infraccion, double *arr_multas_infraccion, int &n_infrac);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
void insertar_ordenado_infracciones(int codigo, double multa, int * arr_codigo_infraccion, double * arr_multas_infraccion, int &n_infrac);
void probar_carga_infracciones(const char * file_name, int * arr_codigo_infraccion, double * arr_multas_infraccion, int n_infrac);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void cargar_infracciones_cometidas(const char *file_entrada, const char *file_new, int * arr_codigo_infraccion,
                                   double * arr_multas_infraccion, int n_infrac, int * arr_dni, int * arr_mas_multa_antigua,
                                   int * arr_ultima_pendiente, double * arr_total_multas, double * arr_total_pagadas,
                                   double * arr_total_pendientes, int & n_cometidas);
int leer_fecha( ifstream & input);
int busqueda_binaria(int value, int * arr, int n);
void insertar_ordenado_sin_repeticion(int dni, int fecha, double costo, int fecha_pago, int * arr_dni, int * arr_mas_multa_antigua,
                                      int * arr_ultima_pendiente, double * arr_total_multas, double * arr_total_pagadas,
                                      double * arr_total_pendientes, int & n_cometidas);
void insetar_ordenado_dni(int dni, int fecha, int fecha_pago, double costo, int * arr_dni, int * arr_mas_multa_antigua,
                         double * arr_total_multas, int * arr_ultima_pendiente, double * arr_total_pagadas,
                         double * arr_total_pendientes, int &n_cometidas);
void imprimir_reporte(const char * file_salida, const char * file_placas, int * arr_dni, int * arr_mas_multa_antigua,
                      int * arr_ultima_pendiente, double * arr_total_multas, double * arr_total_pagadas,
                      double * arr_total_pendientes, int n_cometidas);
void imprimir_titulo_y_encabezado( ofstream & output);
void imprimir_placas(int dni, ofstream & output, ifstream & input);
void agregar_placa(char *listaDePlacas, const char *placa);
int contar_placas(const char * listaDePlacas);
void obtener_placa(const char * listaDePlacas, int n, char *placa);
void imprimir_fecha(int fecha, ofstream & output);

#endif //INC_2025_1_FUNCIONES_HPP
