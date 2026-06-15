//
// Created by User on 14/06/2026.
//

#ifndef INC_2025_1_FUNCIONES_HPP
#define INC_2025_1_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/EmpresasRegistradas.hpp"
#include "../Estructuras/TablaDeInfracciones.hpp"

void cargar_tabla_infracciones(const char * file_name, TablaDeInfracciones * tabla_de_infracciones, int &n_infrac);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
char * leer_candena( ifstream & input, char del);
double leer_double( ifstream & input);
void cargar_empresas_registradas(const char * file_name, EmpresasRegistradas * empresas_registradas, int &n_empresas);
void cargar_placas_registradas(const char * file_name, EmpresasRegistradas * empresas_registradas, int n_empresas);
int buscar_empresa(EmpresasRegistradas * empresas_registradas, int dni, int n_empresas);
void cargar_infracciones_cometidas(const char * file_name, EmpresasRegistradas *empresas_registradas, int n_empresas, TablaDeInfracciones *
                                   tabla_de_infracciones, int n_infrac);
int buscar_empresa_placa(char * placa_leida, EmpresasRegistradas * empresas_registradas, int n_empresas);
int buscar_infraccion(char * codigo_infrac, TablaDeInfracciones * tabla_de_infracciones, int n_infrac);
void actualizar_datos(EmpresasRegistradas & empresa, TablaDeInfracciones &infraccion, int aa, int mm, int dd, ifstream &input);
void ordenar_empresas(EmpresasRegistradas * empresas_registradas, int n_empresas);
void swap_struct( EmpresasRegistradas & a, EmpresasRegistradas & b);
void ordenar_infracciones(TablaDeInfracciones * tabla_de_infracciones, int n_infrac);
void swap_struct_infrac( TablaDeInfracciones & a, TablaDeInfracciones & b);
void abrir_archivo_salida(const char * file_name, ofstream & output);
void imprimir_reporte(const char * file_name, EmpresasRegistradas * empresas_registradas, int n_empresas,
                      TablaDeInfracciones * tabla_de_infracciones, int n_infrac);
void encuadrar(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void imprimir_fecha(int aa, int mm, int dd, ofstream & output);
void imprimir_titulo_encabezado1( ofstream & output);
void modificar_cadena(char * cadena);

#endif //INC_2025_1_FUNCIONES_HPP
