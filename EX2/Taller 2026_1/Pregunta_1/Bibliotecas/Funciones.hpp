//
// Created by User on 5/07/2026.
//

#ifndef PREGUNTA_1_FUNCIONES_HPP
#define PREGUNTA_1_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Cliente.hpp"
#include "../Estructuras/Cuenta.hpp"

void cargar_tipos_cliente(const char * file_name, TipoCliente *&arr_tipos_clientes, int &n_tipos_clientes);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
char * leer_candena( ifstream & input, char del);
char * asignar_cadena(char * origin);
void prueba_carga_tipos_cliente(const char * file_name, TipoCliente *&arr_tipos_clientes, int n_tipos_clientes);
void abrir_archivo_escritura(const char * file_name, ofstream & output);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void cargar_clientes(const char * file_name, Cliente *&arr_clientes, int &n_clientes, TipoCliente *&arr_tipos_clientes, int n_tipos_clientes);
char *extraer_nombre(ifstream &input);
int buscar_tipo_cliente(char tipo_leido, TipoCliente *& arr_tipos_clientes, int n_tipos_clientes);
void camelizar(char * cadena);
void imprimir_reporte(const char * file_name, Cliente *&cliente, int n_clientes);
void imprimir_encabezado(const Cliente & cliente, ofstream & output);
void cargar_cuentas(const char * file_name, Cliente *&cliente, int n_clientes);
int leer_int( ifstream & input);
double leer_double( ifstream & input);
int buscar_cliente(Cliente *& cliente, int n_clientes, int dni_leido);
void imprimir_cuentas(const Cliente & cliente, ofstream & output);
void imprimir_encabezado2( ofstream & output);
void cargar_transacciones(const char * file_name, Cliente *&cliente, int n_clientes);
void buscar_cliente_cuenta(Cliente *&cliente, int n_clientes, int num_cuenta_leido, int &pos_cliente, int &pos_cuenta);
void imprimir_transacciones(const struct Cuenta & cuenta, ofstream & output);
void ordenar_clientes(Cliente *& cliente, int n_clientes);
void ordenar_cuentas( Cliente & cliente);
void swap_struct_cliente( Cliente & a, Cliente & b);
void swap_struct_cuenta( struct Cuenta & a, struct Cuenta & b);



#endif //PREGUNTA_1_FUNCIONES_HPP
