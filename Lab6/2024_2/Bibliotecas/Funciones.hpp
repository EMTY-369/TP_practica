//
// Created by User on 1/06/2026.
//

#ifndef INC_2024_2_FUNCIONES_HPP
#define INC_2024_2_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_platos(const char *file_name, int * arrCodigosPlatos, int * arrNumPlatosVendidos, int &n_platos);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
void insertar_ordenado_sin_repeticion(int cant, int cod_plato, int * arr_codigos_platos, int * arr_num_platos_vendidos, int & n_platos);
int busqueda_binaria(int value, int * arr, int n);
void insertar_ordenado(int cant, int cod_plato, int * arr_codigos_platos, int * arr_num_platos_vendidos, int &n_platos);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void cargar_platos_ofrecidos(const char *file_name, double * arrPrecio, double * arrIngresoBruto, double * arrDescuento, double * arrTotal,
                             bool * arrTieneDescuento, int n_platos, int * arrCodigosPlatos, int * arrNumPlatosVendidos);
void prueba_carga_platos_vendidos(const char * file_name, int * arrCodigosPlatos, int * arr_num_platos_vendidos, int n_platos,
                                  double * arr_precio, double * arr_ingreso_bruto, double * arr_descuento, double * arr_total,
                                  bool * arr_tiene_descuento);
void encuadrar_char(const char * cadena, int ancho, ofstream &output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_reporte(const char * file_entrada, const char * file_salida, int * arr_codigos_platos, int * arr_num_platos_vendidos,
                      double * arr_precio, double * arr_ingreso_bruto, double * arr_descuento, double * arr_total,
                      bool * arr_tiene_descuento, int n_platos);
void modificarCadena(char * descripcion, char * catergoria, bool hayDescuento);
void colocar_espacios_minusculas(char * descripcion);
void imprimir_titulo_encabezado( ofstream & output);



#endif //INC_2024_2_FUNCIONES_HPP
