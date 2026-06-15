//
// Created by User on 10/05/2026.
//

#ifndef INC_2025_1_FUNCIONES_HPP
#define INC_2025_1_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_empresas(const char *file_name, int *DNIs_empresas, int  &n_empresas);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
void insertar_ordenar_dni(int DNI, int * DNIs_empresas, int n_empresas);
void probar_carga_empresas(const char *file_name, int *DNIs_empresas, int n_empresas);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void cargar_infracciones(const char *file_name, char *codigos_char_infrac, int *codigos_int_infrac, double *costos_infrac, int &n_infrac);
void insertar_ordenar_infrac(int codigo_int_leido, char codigo_char_leido, double costo_leido, int n_infrac, int * codigos_int_infrac,
                            char * codigos_char_infrac, double * costos_infrac);
void probar_carga_infracciones(const char *file_name, char *codigos_char_infrac, int *codigos_int_infrac,
                               double *costos_infrac, int n_infrac);
void cargar_placas(const char *file_name, char *placas_char, int *placas_int, int *DNIs_placas, int &n_placas);
void cargar_multas(const char *file_name, int *cants_leves, int *cants_graves, int *cants_muy_graves, int *cants_totales,
                  double *costos_leves, double *costos_graves, double *costos_muy_graves, double *costos_totales,
                  int n_empresas, int * cants_infrac, double * monto_totales, int n_infrac,int * DNIs_empresas,
                  char *codigos_char_infrac, int *codigos_int_infrac, double * costos_infrac, char *placas_char,
                  int *placas_int, int *DNIs_placas, int n_placas);
int buscar_representante(char placa_char_leido, int placa_int_leido, char * placas_char, int * placas_int, int * DNIs_placas, int n_placas);
int buscar_empresa(int DNI, int *DNIs_empresas, int n_empresas);
int buscar_infraccion(char infrac_char_leido, int infrac_int_leido, char * codigos_char_infrac, int * codigos_int_infrac, int n_infrac);
void generar_reporte(const char *file_name, int *cants_leves, int *cants_graves, int *cants_muy_graves, int *cants_totales,
                    double * costos_leves, double * costos_graves, double * costos_muy_graves, double * costos_totales,
                    int n_empresas, int * cants_infrac, double * monto_totales, int n_infrac, int * DNIs_empresas,
                    char *codigos_char_infrac, int * codigos_int_infrac, double * costos_infrac);
void imprimir_titulo_1(ofstream & output);
void imprimir_encabezados(ofstream & output);

#endif //INC_2025_1_FUNCIONES_HPP
