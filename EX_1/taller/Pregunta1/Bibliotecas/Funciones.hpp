//
// Created by User on 17/05/2026.
//

#ifndef PREGUNTA1_FUNCIONES_HPP
#define PREGUNTA1_FUNCIONES_HPP
#include "Utils.hpp"
void imprimir_reporte(const char *file_cursos, const char *file_profesores, const char *file_sesiones, const char *file_salida);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
void abrir_archivo_escritura(const char * file_name, ofstream &output);
void imprimir_titulo( ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_cursos( ifstream &input_cursos, ifstream &input_profesores, ifstream &input_sesiones, ofstream &output);
void imprimir_encabezado( ifstream &input, int cod_curso, ofstream & output);
void imprimir_texto( ifstream & input, ofstream & output, int espacios, char del);
void buscar_imprimir_horarios(ifstream &input_sesiones, ifstream &input_profesores, ofstream & output, int cod_curso,
                       int &horas_curso,int &n_alumnos_curso);
void buscar_imprimir_profesor( ifstream &input, ofstream & output, int cod_profesor,int horario,int n_alumnos_horario);
void leer_imprimir_parte_dinamica(ifstream &input, ofstream &output, int &horas_horario);
void imprimir_dia(int dia, ofstream & output);
void imprimir_tiempo(int tiempo, ofstream & output);

#endif //PREGUNTA1_FUNCIONES_HPP
