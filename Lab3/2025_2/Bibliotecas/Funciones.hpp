//
// Created by User on 26/04/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP

#include "Utils.hpp"

void calcular_reporte(double tarifa_duracion_etiqueta, const char *file_entrada_canales, const char *file_entrada_etiquetas,
                     const char *file_entrada_reproducciones, const char *file_salida_reporte);
void apertura_archivo_lectura(const char *file_name,ifstream &input);
void apertura_archivo_escritura(const char *file_name,ofstream &output);
void imprimir_titulo(double tarifa_duracion_etiqueta,ofstream &output);
void imprimir_linea(int n,char c,ofstream &output);
void leer_imprimir_canales(double tarifa_duracion_etiqueta,ifstream &input_canales,ifstream &input_etiquetas,
                           ifstream &input_reproducciones,ofstream &output);
int leer_fecha(ifstream &input);
void imprimir_leer_encabezado(int cant_canales,int fecha_creacion,int &int_codigo,char &c_codigo,double &rating,
                             ifstream &input_canales, ofstream &output);
void imprimir_nombre(bool mayus,ifstream &input,ofstream &output);
char a_mayuscula(char c);
void imprimir_fecha(int fecha,ofstream &output);
void leer_imprimir_parte_dinamica(int int_codigo,char c_codigo,int &tiempo_total_repro,ifstream &input_canales,
                                  ifstream &input_etiquetas, ifstream &input_reproducciones,ofstream &output);
void buscar_cant_repro_leer_imprimir_info(int int_codigo,char c_codigo,int etiqueta,int &cant_reproducciones,
                                          ifstream &input_reproducciones,ofstream &output,int cant_etiquetas);
void buscar_duracion_leer_imprimir_info(int etiqueta,int &duracion,ifstream &input_etiquetas,ofstream &output);
int leer_duracion(ifstream &input_etiquetas);
void imprimir_tiempo(int tiempo,bool hay_hora, ofstream &output);
void imprimir_resumen_canal(int tiempo_total_repro,double tarifa_duracion_etiqueta,double rating,ofstream &output);

#endif //INC_2025_2_FUNCIONES_HPP
