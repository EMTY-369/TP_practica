//
// Created by User on 18/05/2026.
//

#ifndef INC_2026_1_FUNCIONES_HPP
#define INC_2026_1_FUNCIONES_HPP
#include "Utils.hpp"
void imprimir_reporte(const char *file_pacientes, const char *file_triaje, const char *file_atenciones, const char *file_salida);
void abrir_lectura(const char * file_name, ifstream & input);
void abrir_escritura(const char * file_name, ofstream & output);
void imprimir_titulo( ofstream & output);
void imprimir_encabezado(int id, int i, ifstream &input, ofstream & output, int &edad);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_nombre( ifstream & input, int espacio,char del, ofstream & output);
void espacios(int n, ofstream & output);
void buscar_imprimir_triajes(ifstream &input_triaje, ifstream &input_atenciones, int id, int &id_temp_mayor, int &id_temp_menor,
                             double &temperatura_mayor, double &temperatura_menor, double &costo_total, ofstream & output, int edad);
int leer_fecha( ifstream &input);
void imprimir_titulos_tablas( ofstream & output);
void imprimir_fecha(int fecha, ofstream & output);
void buscar_imprimir_duracion_costo(ifstream &input, int fecha_aten, double &costo_atencion, int id, ofstream & output, int edad);
int leer_tiempo( ifstream & input);
void imprimir_tiempo(int tiempo, ofstream & output);
void imprimir_calcular_costo_atencion(int edad, double &costo_atencion, int duracion, double costo_hora, ofstream &output);
void determinar_amyor_menor(int id, double temp, int &id_temp_mayor, int &id_temp_menor, double &temperatura_mayor,
                           double &temperatura_menor);
void imprimir_resumen_final(double costo_total, int id_temp_mayor, int id_temp_menor, double temperatura_mayor, double temperatura_menor,
                            ofstream & output);
#endif //INC_2026_1_FUNCIONES_HPP
