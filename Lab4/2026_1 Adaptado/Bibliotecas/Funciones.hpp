//
// Created by User on 4/05/2026.
//

#ifndef INC_2026_1_ADAPTADO_FUNCIONES_HPP
#define INC_2026_1_ADAPTADO_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_pacientes(const char *file_name, int * ID_pacientes, int * edad_pacientes,
                      char * sexo_pacientes, int &n_pacientes);
void apertura_archivo_lectura(ifstream & input, const char * file_name);
void carga_triaje(const char * file_name, int * fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca,
                  int * sistolica, int * diastolica, double *temperatura, int * saturacion_oxigeno, int &n_triaje);
void apertura_archivo_escritura(ofstream & output, const char * file_name);
void probar_carga_pacientes(const char * file_name, int * ID_pacientes, int * edad_pacientes, char * sexo_pacientes,
                            int n_pacientes);
void carga_triaje(const char * file_name, int * fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca,
                  int * sistolica, int * diastolica, double *temperatura, int * saturacion_oxigeno, int &n_triaje);
void imprimir_linea(int n, char c, ofstream & output);
int leer_fecha(ifstream & input);
void probar_carga_triaje(const char *file_name, int *fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca,
                        int * sistolica, int * diastolica, double * temperatura, int * saturacion_oxigeno, int n_triaje);
void imprimir_fecha(int fecha, ofstream & output);
void generar_reporte(const char * file_name_entrada, const char *file_name_salida, int * ID_pacientes, int * edad_pacientes,
                     char * sexo_pacientes, int n_pacientes, int * fechas_atenciones, int * ID_triaje,
                     int * frecuencia_cardiaca, int * sistolica, int * diastolica, double * temperatura, int * saturacion_oxigeno, int n_triaje);
void imprimir_titulo(ofstream & output);
int leer_hora(ifstream & input);
void imprimir_pacientes(ifstream & input, ofstream & output, int fecha_leido, int * ID_pacientes, int * edad_pacientes, char * sexo_pacientes,
                        int n_pacientes, int * fechas_atenciones, int * ID_triaje, int * frecuencia_cardiaca, int * sistolica, int * diastolica,
                        double * temperatura, int * saturacion_oxigeno, int n_triaje);
int buscar_paciente(int id_leido, int * id_pacientes,int n_pacientes);
int buscar_triaje(int fecha_leido, int id_leido, int * fechas_atenciones, int * id_triaje, int n_triaje);
int calcular_duracion(int hora_ingreso, int hora_salida);
void imprimir_hora(int tiempo,ofstream & output);

#endif //INC_2026_1_ADAPTADO_FUNCIONES_HPP
