//
// Created by User on 17/05/2026.
//

#ifndef PREGUNTA2_FUNCIONES_HPP
#define PREGUNTA2_FUNCIONES_HPP
#include "Utils.hpp"
void cargar_disponibilidad(const char *file_name, int *arr_dia_semana, int *arr_hora_inicio, int *arr_hora_final, int &n_dispo);
void abrir_archivo_lectura(const char * file_name, ifstream  &input);
void cargar_sesiones(const char *file_name, int *arr_dia_semana, int * arr_hora_inicio, int * arr_hora_final, int n_dispo,
                     int * arr_aulas_int, int * arr_cant_sesiones, int * arr_dia_temprano, int * arr_dia_tarde,
                     int * arr_hora_temprano, int * arr_hora_tarde, int * arr_cant_ses_fuera, bool * arr_ses_fuera,
                     double * arr_prom_alumnos, double * arr_ocupacion, char *arr_aulas_char, int &n_aulas);
void ignorar( ifstream & input, char del);
void agregar_sin_repeticion(char aula_char, int aula_int,int n_alumnos, int hora_inicio, int hora_fin, int dia, int * arr_dia_semana,
                           int * arr_hora_inicio, int * arr_hora_final, int n_dispo, int * arr_aulas_int, int * arr_cant_sesiones,
                           int * arr_dia_temprano, int * arr_dia_tarde, int * arr_hora_temprano, int * arr_hora_tarde,
                           int * arr_cant_ses_fuera, bool * arr_ses_fuera, double * arr_prom_alumnos, double * arr_ocupacion,
                           char * arr_aulas_char, int &n_aulas);
int buscar_aula(char aula_char, int aula_int, char * arr_aulas_char, int * arr_aulas_int, int n_aulas);
int buscar_dia(int dia, int * arr_dia_semana, int n_dispo);
void actualizar_prom_ocupaciones(double * arr_prom_alumnos, double * arr_ocupacion, int * arr_cant_sesiones, int n_aulas);
void imprimir_reporte(const char *file_name, int * arr_aulas_int, int * arr_cant_sesiones, int * arr_dia_temprano,
                      int * arr_dia_tarde, int * arr_hora_temprano, int * arr_hora_tarde, int * arr_cant_ses_fuera,
                      bool * arr_ses_fuera, double * arr_prom_alumnos, double * arr_ocupacion, char * arr_aulas_char, int n_aulas);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void imprimir_titulo( ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_encabezado( ofstream & output);
void imprimir_nombre_dia(int i, ofstream & output);
void imprimir_tiempo(int tiempo, ofstream & output);
void imprimir_resumen(int total_sesiones, int total_ses_fuera, ofstream & output);
void eliminar_aulas(int * arr_aulas_int, int * arr_cant_sesiones, int * arr_dia_temprano, int * arr_dia_tarde,
                    int * arr_hora_temprano, int * arr_hora_tarde, int * arr_cant_ses_fuera, bool * arr_ses_fuera,
                    double * arr_prom_alumnos, double * arr_ocupacion, char *arr_aulas_char, int &n_aulas);

#endif //PREGUNTA2_FUNCIONES_HPP
