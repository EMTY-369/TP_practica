//
// Created by User on 22/06/2026.
//

#ifndef INC_2026_ADAPTADO_FUNCIONES_HPP
#define INC_2026_ADAPTADO_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Atencion.hpp"
#include "../Estructuras/Medico.hpp"


void cargar_medicos(const char * file_name, Medico *& arr_medicos, int &n_med);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
char * leer_cadena( ifstream & input, char del);
int leer_int( ifstream & input);
double leer_double( ifstream & input);
char * asignar_cadena(char * origen);
void prueba_carga_medicos(const char * file_name , Medico * arr_medicos, int n_med);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_atenciones(const char * file_name, Atencion *& arr_atenciones, int& n_atenciones);
int leer_tiempo( ifstream & input);
void prueba_atenciones(const char * file_name, Atencion * arr_atencion, int n_atenciones);
void ordenar_atenciones(Atencion *& atencion, int n_atenciones);
void swap_struct( Atencion & a,  Atencion & b);
void imprimir_reporte(const char * file_name, Medico * medico, int n_med, Atencion * atencion, int n_atenciones);
void modificar_cadena(char * nombre);



#endif //INC_2026_ADAPTADO_FUNCIONES_HPP
