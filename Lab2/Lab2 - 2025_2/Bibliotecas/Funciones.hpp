//
// Created by User on 20/04/2026.
//

#ifndef LAB2___2025_2_FUNCIONES_HPP
#define LAB2___2025_2_FUNCIONES_HPP

#include "Utils.hpp"

int leer_fecha_consola();
void calcular_reporte(int fecha_inicio, int fecha_final, double tarifa_reproduccion, double tarifa_duracion, const char *file_name_entrada, const char *file_name_salida);
void apertura_archivo_lectura(ifstream &input,const char *file_name);
void apertura_archivo_escritura(ofstream &output,const char *file_name);
void imprimir_titulo(int fecha_inicio,int fecha_final,double tarifa_reproduccion,double tarifa_duracion,ofstream &output);
void imprimir_fecha_archivo(int fecha, ofstream &output);
void imprimir_linea(char c,int n,ofstream &output);
void leer_imprimir_info_canales(int fecha_inicio, int fecha_final, double tarifa_reproduccion, double tarifa_duracion, int &cant_canales_total, int &duracion_total,
                                double &ingreso_total_duración, double &ingreso_total_publicidad, ifstream &input, ofstream &output);
int leer_fecha_archivo(ifstream &input);
void leer_imprimir_info_canal(int fecha, int cant_canales_total, double tarifa_duracion, double tarifa_reproduccion, int fecha_inicio, int fecha_final,
                              int &duracion_canal_total, double &ingreso_duracion_canal, double &ingreso_publicidad_canal, ifstream &input, ofstream &output);
void leer_imprimir_encabezado(int fecha, int cant_canales_total, int &seguidores_nuevos_mes, int &vistas_nuevas_mes, int &max_espectadores, ifstream &input, ofstream &output);
void leer_imprimir_nombre(ifstream &input,ofstream &output);
char mayuscula(char c);
void leer_imprimir_reproducciones(int fecha_inicio, int fecha_final, double tarifa_duracion, int &duracion_canal_total,
                                  double &ingreso_duracion_canal, int &reproducciones_canal, ifstream &input, ofstream &output);
bool valid(int fecha_inicio,int fecha_final,int fecha);
int leer_tiempo(ifstream &input);
void imprimir_hora(int tiempo,ofstream &output);
void imprimir_resumen_canal(int duracion_canal_total,double ingreso_duracion_canal,int reproducciones_canal,double ingreso_publicidad_canal,double index,
                            ifstream &input,ofstream &output);
void imprimir_resumen_final(int cant_canales_total,int duracion_total,double ingreso_total_duración,double ingreso_total_publicidad,ofstream &output);

#endif //LAB2___2025_2_FUNCIONES_HPP
