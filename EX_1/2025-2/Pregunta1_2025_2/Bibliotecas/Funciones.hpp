//
// Created by User on 13/05/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP

#include "Utils.hpp"
void escribir_reporte(const char *file_entrada_canales, const char *file_entrada_streams, const char *file_entrada_categorias,
                      const char *file_entrada_idiomas, const char *file_salida);
void abrir_archivo_lectura(const char *file_name, ifstream & input);
void abrir_archivo_escritura(const char * file_salida, ofstream & output);
void imprimir_titulo( ofstream & output);
void imprimir_linea(int n, char c, ofstream & output);
void imprimir_streams(ofstream & output, ifstream & input_canales,ifstream &input_streams, ifstream &input_categorias,
                     ifstream & input_idiomas, int &n_streams, int &total_duraciones);
int leer_tiempo(ifstream & input);
void imprimir_encabezado(ofstream & output,ifstream & input_categorias, ifstream & input_idiomas, int cod_stream,
                         char categoria_char, int categoria_int, int cod_idioma, int duracion);
void buscar_imprimir_categoria(ifstream &input_categorias,ofstream & output, char categoria_char, int categoria_int);
void leer_imprimir_nombre(ifstream &input,ofstream & output, int espacio, bool all_mayus);
char to_mayus(char c);
void buscar_imprimir_idioma(ifstream & input_idiomas, ofstream & output, int cod_idioma);
void imprimir_tiempo(int tiempo, ofstream & output);
void imprimir_canales(ifstream &input_canales, ofstream &output, int cod_stream,int duracion, int &cant_repro, int &tiempo_stream, double &drop_menor,
                     double &drop_mayor, int &canal_mayor_int, int &canal_menor_int, char &canal_mayor_char, char &canal_menor_char);
int leer_fecha( ifstream &input);
void leer_imprimir_repro(ifstream &input_canales, ofstream &output, int cod_stream, int duracion, int cod_canal_int, char cod_canal_char,
                         double &prom_rating, double &prom_drop, double &drop_mayor, double &drop_menor, int &canal_mayor_int,
                         int &canal_menor_int, char &canal_menor_char, char &canal_mayor_char, int &n_repro, int &n_canales);
void imprimir_encabezado_2(ofstream &output, int n_canales, char cod_canal_char, int cod_canal_int);
void imprimir_fecha( ofstream & output, int fecha);

#endif //INC_2025_2_FUNCIONES_HPP
