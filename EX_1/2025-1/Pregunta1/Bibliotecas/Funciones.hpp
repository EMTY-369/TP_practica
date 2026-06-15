//
// Created by User on 17/05/2026.
//

#ifndef INC_2025_1_FUNCIONES_HPP
#define INC_2025_1_FUNCIONES_HPP
#include "Utils.hpp"

void imprimir_reporte(const char *file_empresas, const char *file_placas, const char *file_tabla, const char *file_infrac,
                      const char *file_salilda);
void abrir_archivo_lectura(const char *file_name, ifstream &input);
void abrir_archivo_escritura(const char *file_name, ofstream &output);
void imprimir_titulo( ofstream & output);
void imprimir_encabezado(int dni, int i, ifstream &input, ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_texto( ifstream & input, int espacio, char del,bool mayus, ofstream & output);
void leer_imprimir_placas(ifstream &input_placas, ifstream &input_tabla_infrac, ifstream &input_infrac_cometidas, int dni,
                          double &multas_pagadas, double &multas_pendientes, ofstream & output);
void imprimir_tipo(char placa_char, ofstream & output);
void imprimir_titulo_tablas(bool pagadas, ofstream & output);
void buscar_imprimir_multas( ifstream &input_infrac_cometidas, ifstream &input_tabla_infrac, ofstream &output,
                            char placa_char, int placa_int, bool pagadas, double &multas);
int leer_fecha(ifstream &input);
void imprimir_fecha(int fecha, ofstream & output);
void imprimir_tipo_infrac(char infrac_char, ofstream & output);
void buscar_imprimir_infrac(char infrac_char, int infrac_int, double &multas, ifstream &input, ofstream & output);

#endif //INC_2025_1_FUNCIONES_HPP
