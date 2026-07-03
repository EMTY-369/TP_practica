//
// Created by User on 1/07/2026.
//

#ifndef INC_2026_1_FUNCIONES_HPP
#define INC_2026_1_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Medico.hpp"
#include "../Estructuras/ListaMedicosTAD.hpp"

void cargar_medicos(const char * file_name,struct ListaMedicosTAD &lista_medicos);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
void inicializar_lista(struct ListaMedicosTAD &lista_medicos);
char * leer_cadena( ifstream & input, char del);
double leer_double( ifstream & input);
void insertar_ordenado(struct ListaMedicosTAD &lista_medicos, struct Medico & medico);
void asignar_struct_med( struct Medico & dato, struct Medico & medico);
char * asignar_cadena(char * buffer);
void modificar_cadena(char *cadena);
void prueba_carga(const char * file_name, const ListaMedicosTAD &lista_medicos, bool atenciones);
void abrir_archivo_salida(const char * file_name, ofstream & output);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_atenciones(const char * file_name, ListaMedicosTAD &lista_medicos);
int leer_int( ifstream & input);
void leer_hora(Hora &tiempo, ifstream & input);
void asignar_hora(Hora &tiempo, int origen);
struct Nodo * buscar_medico(ListaMedicosTAD &lista_medicos, int cod_med);
void imprimir_atenciones(struct Atencion * &atencion, int num_atenciones, ofstream & output);



#endif //INC_2026_1_FUNCIONES_HPP
