//
// Created by User on 18/05/2026.
//

#ifndef PREGUNTA2_3_FUNCIONES_HPP
#define PREGUNTA2_3_FUNCIONES_HPP
#include "Utils.hpp"
void cargar_disponibilidad(const char *file_name, int * dia_semana, int * horas_inicio, int * horas_fin, int &n_dispo);
void abrir_lectura(const char * file_name, ifstream & input);
void cargar_aulas(const char *file_name, int * dia_semana, int * horas_inicio, int * horas_fin, int n_dispo, int * aulas_int,
                  int * cants_sesiones_aulas, int * ses_temprano_horas, int * ses_tardes_horas, int * cant_ses_fueras,
                  char * aulas_char, int *ses_temprano_dia, int *ses_tardes_dia, double * proms_alums, double * ocupacion_aulas,
                  bool * existen_ses_fueras, int &n_aulas);
void ignorar(char c, ifstream & input);
void leer_sesiones_clases(ifstream & input, int * dia_semana, int * horas_inicio, int * horas_fin, int n_dispo, int * aulas_int,
                          int * cants_sesiones_aulas, int * ses_temprano_horas, int * ses_tardes_horas, int * cant_ses_fueras,
                          char * aulas_char, int *ses_temprano_dia, int *ses_tardes_dia, double * proms_alums,
                          double * ocupacion_aulas, bool * existen_ses_fueras, int &n_aulas, int n_alumnos);
void insertar_ordenado_sin_repeticion(char aula_char, int aula_int, int * aulas_int, char * aulas_char, bool * existen_ses_fueras,
                                     int &pos_aula, int &n_aulas);
int buscar_aula(char aula_char, int aula_int, int * aulas_int, char * aulas_char, int n_aulas);
int buscar_dispo(int * dia_semana, int n_dispo, int dia);
void imprimir_reporte(const char *file_name, int *aulas_int, int * cants_sesiones_aulas, int * ses_temprano_horas, int * ses_tardes_horas, int * cant_ses_fueras,
                      char * aulas_char, int * ses_temprano_dia, int * ses_tardes_dia, double * proms_alums, double * ocupacion_aulas, bool * existen_ses_fueras,
                      int n_aulas);
void actualizar_prom_ocupacion(double * proms_alums, double * ocupacion_aulas, int n_aulas, int * cants_sesiones_aulas);
void abrir_escritura(const char * file_name, ofstream & output);
void imprimir_titulo( ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_encabezado( ofstream & output);
void imprimir_dia(int dia, ofstream & output);
void imprimir_hora(int tiempo, ofstream & output);
#endif //PREGUNTA2_3_FUNCIONES_HPP
