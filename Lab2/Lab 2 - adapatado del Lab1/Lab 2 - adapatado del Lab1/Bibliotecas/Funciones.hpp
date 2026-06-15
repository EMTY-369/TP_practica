//
// Created by alois on 18/4/26.
//

#ifndef LAB_2___ADAPATADO_DEL_LAB1_FUNCIONES_HPP
#define LAB_2___ADAPATADO_DEL_LAB1_FUNCIONES_HPP

#include "Utils.hpp"

void calcular_el_reporte(int fecha_inicio,int fecha_final, const char *file_name_entrada, const char *file_name_salida);
void apertura_archivo_lectura(ifstream &input, const char *file_name);
void apertura_archivo_escritura(ofstream &output,const char *file_name);
void imprimir_titulo(int fecha_inicio,int fecha_final,ofstream &output);
void imprimir_fecha(int fecha, ofstream &output);
void imprimir_linea(char c,int n,ofstream &output);
void leer_imprimir_atenciones(int fecha_inicio, int fecha_final, int &atenciones_total, int &tiempo_total, double &costo_total, ifstream &input, ofstream &output);
int leer_fecha(ifstream &input);
bool valid(int fecha_inicio,int fecha_final,int fecha);
void imprimir_canal(int fecha,int &atenciones_dia,int &tiempo_dia,double &costo_dia,ifstream &input,ofstream &output);
void imprimir_encabezado(int fecha, ofstream &output);
void imprimir_titulo_de_columnas(ofstream &output);
void leer_imprimir_ID(int &ID, ifstream &input, ofstream &output);
void leer_imprimir_nombre(ifstream &input,ofstream &output);
char mayuscula(char c);
int leer_hora(ifstream &input);
void imprimir_hora(int time, ofstream &output);
void imprimir_nivel_PA(int sistolica, int diastolica, int &normal, int &h_nivel_2, ofstream &output);
void imprimir_resumen_canal(int atenciones_dia, int normal, int h_nivel_2, int ID_PA_mayor, double PA_mayor, int tiempo_dia, double costo_dia, ofstream &output);
void imprir_resumen_final(int atenciones_total,int tiempo_total,double costo_total,ofstream &output);

#endif //LAB_2___ADAPATADO_DEL_LAB1_FUNCIONES_HPP
