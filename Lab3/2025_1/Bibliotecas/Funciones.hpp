//
// Created by User on 4/27/2026.
//

#ifndef INC_2025_1_FUNCIONES_HPP
#define INC_2025_1_FUNCIONES_HPP

#include "Utils.hpp"

void calcular_reporte(const char *file_entrada_empresas, const char *file_entrada_infracciones,
                      const char *file_entrada_tabla, const char *file_salida);
void apertura_archivos_lectura(const char *file_name,ifstream &input);
void apertura_archivos_escritura(const char *file_name,ofstream &output);
void imprimir_titulo(ofstream &output);
void imprimir_linea(int n,char c,ofstream &output);
void leer_imprimir_companias(int &compania_mayor_infracciones,int &compania_menor_infracciones, double &pago_mayor,
                             double &pago_menor,ifstream &input_empresas,ifstream &input_infracciones,
                             ifstream &input_tabla,ofstream &output);
void imprimir_encabezado(int cant_companias,int DNI,ifstream &input_empresas,ofstream &output);
void imprimir_nombre(bool camellizacion,ifstream &input,ofstream &output);
char a_mayuscula(char c);
void leer_imprimir_vehiculos(int &cant_f_leves,int &cant_f_graves,int &cant_f_muy_graves,
                             double &pago_f_leves,double &pago_f_graves,double &pago_f_muy_graves,
                             ifstream &input_empresas,ifstream &input_infracciones,ifstream &input_tabla,ofstream &output);
void imprimir_tipo_vehivulo(char c, ofstream &output);
void buscar_infracciones(double c_placa, int int1_placa, int int2_placa,
                         int &cant_f_leves, int &cant_f_graves, int &cant_f_muy_graves,
                         double &monto_leves, double &monto_graves, double &monto_muy_graves,
                         ifstream &input_infracciones, ifstream &input_tabla, ofstream &output);
int leer_fecha(ifstream &input);
void imprimir_fecha(int fecha,ofstream &output);
void buscar_tipo_infraccion(char c_infraccion, int int_infraccion, int &cant_f_leves, int &cant_f_graves,
                            int &cant_f_muy_graves, double &monto_leves, double &monto_graves, double &monto_muy_graves,
                            ifstream &input_tabla, ofstream &output);
void imprimir_resumen(int cant_f_leves,int cant_f_graves,int cant_f_muy_graves, double pago_total,
                      double pago_f_muy_graves,double pago_f_leves,double pago_f_graves,ofstream &output);
void imprimir_resumen_final(int compania_mayor_infracciones,int compania_menor_infracciones,
                            double pago_mayor,double pago_menor,ofstream &output);
#endif //INC_2025_1_FUNCIONES_HPP
