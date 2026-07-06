//
// Created by User on 6/07/2026.
//

#ifndef PREGUNTA_2_FUNCIONES_HPP
#define PREGUNTA_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/ListaClientes.hpp"

void cargar_clientes(const char * file_name, ListaClientes &lista_clientes);
void abrir_archivo_lectura(const char * file_name, ifstream & input);
char * extraer_nombre( ifstream & input);
char * leer_cadena( ifstream & input, char del);
char * asignar_candena(char * origen);
void insertar_ordenado(ListaClientes &lista_clientes, const struct Cliente & c);
void inicializar_lista(ListaClientes &lista_clientes);
void asignar_struct_Cliente(Cliente & dato, const struct Cliente & cliente);
void modificar_cadena(char *cadena);
void imprimir_reporte(const char * file_name, const char * titulo, ListaClientes &lista_clientes);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void imprimir_encabezado(const Cliente & dato, ofstream & output);
void cargar_cuentas(const char * file_name, ListaClientes &lista_clientes);
struct Nodo * buscar_posicion_cliente(ListaClientes &lista_clientes, int dni);
int leer_int( ifstream & input);
double leer_double( ifstream & input);
void imprimir_cuenta(const Cuenta & cuenta, ofstream & output);
void imprimir_info_cuentas(const Cliente & dato, ofstream & output);
void cargar_transacciones(const char * file_name, ListaClientes &lista_clientes);
void buscar_cuenta(ListaClientes &lista_clientes, int &pos_cuenta, struct Nodo *& pos_cliente, int nroCuenta_leido);
void crear_listas(ListaClientes &lista_clientes, ListaClientes &lista_saldos_positivos, ListaClientes &lista_saldos_negativos);



#endif //PREGUNTA_2_FUNCIONES_HPP
