//
// Created by aml on 18/05/2026.
//

#ifndef PREGUNTA2_2026_1_FUNCIONES_HPP
#define PREGUNTA2_2026_1_FUNCIONES_HPP
#include "Utils.hpp"

void cargar_atenciones(const char *file_name, int *cods_medicos, int * cants_atenciones, int * tiempos_atenciones, int &n_medicos);
void abrir_lectura(const char * file_name, ifstream & input);
void abrir_escritura(const char * file_name, ofstream & output);
int leer_fecha( ifstream & input);
int leer_tiempo( ifstream & input);
void ignorar(char del, ifstream & input);
int buscar_med(int * cods_medicos, int n_medicos, int doc);
void probar_carga_atenciones(const char * file_name, int * cods_medicos, int * cants_atenciones, int * tiempos_atenciones, int n_medicos);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_tiempo(int tiempo, ofstream & output);
void cargar_especialidades(const char * file_name, int * cods_medicos, int n_medicos, int * espe_medico, double * tarifas_medicos);
void cargar_proms_pagos(int n_medicos, int * proms_atenciones, double * pagos_recibido, double * tarifas_medicos,
                        int * cants_atenciones, int * tiempos_atenciones);
void imprimir_reporte(const char *file_name, bool report1, int * cods_medicos, int * cants_atenciones,
                      int * tiempos_atenciones, int * espe_medico, double * tarifas_medicos, int * proms_atenciones,
                      double * pagos_recibido, int n_medicos);
void imprimir_encabezado( ofstream & output);
void espacios(int n, ofstream & output);
void imprimir_resumen( ofstream & output, double pago_total, int n_medicos);
void eliminar_med(int * cods_medicos, int * cants_atenciones, int * tiempos_atenciones, int * espe_medico,
                  double * tarifas_medicos, int * proms_atenciones, double * pagos_recibido, int &n_medicos);


#endif //PREGUNTA2_2026_1_FUNCIONES_HPP