//
// Created by aml on 18/05/2026.
//

#ifndef PREGUNTA1_2026_1_FUNCIONES_HPP
#define PREGUNTA1_2026_1_FUNCIONES_HPP
#include "Utils.hpp"
void imprimir_reporte(const char *file_sedes, const char *file_pacientes, const char *file_especialidades,
                      const char *file_atenciones, const char *file_salida);
void imprimir_titulo( ofstream & output);
void imprimir_nombre(ifstream & input, int espacio, char del, ofstream & output);
void imprimir_encabezado( ofstream & output);
void buscar_imprimir_atenciones(int sede, ifstream & input_atenciones, ifstream & input_especialidades, ifstream & input_pacientes,
                                ofstream & output, double &pago_sede);
void buscar_imprimir_nombre_paciente( ifstream & input, int id, ofstream & output);
void buscar_imprimir_doc( ifstream &input, double &pago, int duracion, int doc, ofstream & output);
void imprimir_resumen_sede(int n, double pago_sede, int total_atenciones, ofstream & output);
void imprimir_resumen_final(int n_sedes, double pago_total, int sede_mayor, double sede_pago_mayor, ofstream & output);

void ignorar(char del, ifstream & input);
void imprimir_tiempo(int tiempo, ofstream & output);
void imprimir_fecha(int fecha, ofstream & output);
int leer_tiempo( ifstream & input);
int leer_fecha( ifstream & input);
void abrir_lectura(const char * file_name, ifstream & input);
void abrir_escritura(const char * file_name, ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void espacios(int n, ofstream & output);
#endif //PREGUNTA1_2026_1_FUNCIONES_HPP