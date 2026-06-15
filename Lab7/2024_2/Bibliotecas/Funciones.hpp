//
// Created by User on 8/06/2026.
//

#ifndef INC_2024_2_FUNCIONES_HPP
#define INC_2024_2_FUNCIONES_HPP
#include "Utils.hpp"
void cargar_repartidores(const char * file_name, int * arr_dnis_repartidores, int * arr_cods_distrito,
                         char ** arr_nombres_repartidores, char ** arr_movilidad, char ** arr_nombres_distritos,
                         int &n_repartidores);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
char * leer_cadena( ifstream & input, char del);
void cargar_platos(const char * file_name, int * arr_cods_platos, double * arr_precio_platos, double * arr_descuentos_platos,
                   char ** arr_nombres_platos, char ** arr_categoria_platos, int &n_platos);
void prueba_carga_repartidores_platos(const char * file_name, int * arr_dnis_repartidores, int * arr_cods_distrito,
                                      char ** arr_nombres_repartidores, char ** arr_movilidad, char ** arr_nombres_distritos,
                                      int n_repartidores, int * arr_cods_platos, double * arr_precio_platos, double * arr_descuentos_platos,
                                      char ** arr_nombres_platos, char ** arr_categoria_platos, int n_platos);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void encuadrar(const char * texto, int espacio, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void imprimir_repartidores(int * arr_dnis_repartidores, char ** arr_nombres_repartidores, char ** arr_movilidad,
                           int * arr_cods_distrito, char ** arr_nombres_distritos, int n_repartidores, ofstream &output);
void imprimir_platos(int * arr_cods_platos, double * arr_precio_platos, char ** arr_nombres_platos, char ** arr_categoria_platos,
                     double * arr_descuentos_platos, int n_platos, ofstream & output);
void ordenar_repartidores(int * arr_dnis_repartidores, int * arr_cods_distrito, char ** arr_nombres_repartidores,
                          char ** arr_movilidad, char ** arr_nombres_distritos, int n_repartidores);
void swap_int(int &a, int &b);


#endif //INC_2024_2_FUNCIONES_HPP
