//
// Created by User on 3/07/2026.
//

#ifndef INC_2025_2_FUNCIONES_HPP
#define INC_2025_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Transmision.hpp"

void cargar_transmisiones(const char * file_name, Transmision *& transmisiones, int &n_transmisiones);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
int leer_int( ifstream & input);
int leer_fecha( ifstream & input);
void prueba_carga_transmisiones(const char * file_name, Transmision *&transmisiones, int n_transmisiones);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void centrear(const char * texto, int espacio, bool slas_n, ofstream & output);
void imprimir_linea(int n, char c, bool slas_n, ofstream & output);
void imprimir_fecha(int fecha, ofstream & output);
void cargar_streamers(const char * file_name, Transmision *&transmisiones, int n_transmisiones);
char * leer_candena( ifstream & input, char del);
void buscar_insertar_streamers(Transmision *&transmisiones, int n_transmisiones, int id_streamer_leido, char * canal, char * categoria,
                               int cant_seguidores);
char * asignar_cadena(char * origen);
void prueba_carga_streamers(const char * file_name, Transmision *&transmisiones, int n_transmisiones);
void imprimir_titulos_encabezado( ofstream & output);
void imprimir_datos_transmision(const Transmision & transmision, ofstream & output);
void cargar_comentarios(const char * file_name, Transmision *&transmisiones, int n_transmisiones);
int buscar_stream(Transmision *& transmision, int n_transmisiones, int cod_transmision);
char * pre_procesado_comentario(char *origen);
void imprimir_reporte_final(const char * file_name, Transmision *& transmisiones, int n_transmisiones);



#endif //INC_2025_2_FUNCIONES_HPP
