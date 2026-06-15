//
// Created by User on 7/06/2026.
//

#ifndef INC_2025_1_FUNCIONES_HPP
#define INC_2025_1_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_empresas_registradas(const char * file_name, int * dnis_empresas, char ** nombres, char ** distritos, int &n_dnis);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
char * leer_cadena( ifstream & input, char del);
void modificar_cadena(char * cadena);
int leer_entero( ifstream & input);
void cargar_placas(const char * file_name, char ** placas, int * dnis_empresas, int n_dnis);
int buscar_valor(int valor, int * arr, int n);
void prueba_carga_empresas_placas(const char * file_name, int * dnis_empresas, char ** nombres, char ** distritos, char ** placas,
                                 int n_dnis);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void centrear(const char *nombre, int espacio, ofstream & output);
void cargar_infracciones(const char * file_name, char **cods_infrac, double * multas_infrac, int &n_infrac);
double leer_double( ifstream & input);
void prueba_carga_infracciones(const char * file_name, char ** cods_infrac, double * multas_infrac, int n_infrac);
void cargar_infracciones_cometidas(const char * file_name, char ** placas, int n_dnis, char ** cods_infrac, double * multas_infrac,
                                  int n_infrac, int * infrac_mas_antiguas, int * pagos_mas_recientes, int * cants_faltas,
                                  double * pagos_leves, double * pagos_graves, double * pagos_muy_graves);
int leer_fecha( ifstream & input);
int encontrar_placa(char ** placas, int n_dnis, char * placa_leido);
bool verificaSiEstaLaPlaca(char * placas, char * placa_leido);
int buscar_cadena(char * cadena, char ** arr, int n);
void ordenar_arreglos(int * dnis_empresas, char ** nombres, char ** distritos, char ** placas, int * infrac_mas_antiguas,
                      int * pagos_mas_recientes, int * cants_faltas, double * pagos_leves, double * pagos_graves,
                      double * pagos_muy_graves, int n_dnis);
void swap_int(int &value1, int &value2);
void swap_double(double &value1, double &value2);
void swap_str(char *&value1, char *&value2);
void imprimir_reporte(const char * file_name, int *dnis_empresas, char ** nombres, char ** distritos, char ** placas,
                      int * infrac_mas_antiguas, int * pagos_mas_recientes, int * cants_faltas, double * pagos_leves,
                      double * pagos_graves, double * pagos_muy_graves, int n_dnis);
void imprimir_titulo_encabezado( ofstream & output);
void imprimir_fecha(int fecha, ofstream & output);


#endif //INC_2025_1_FUNCIONES_HPP
