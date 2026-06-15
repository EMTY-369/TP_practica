//
// Created by User on 15/06/2026.
//

#ifndef INC_2024_2_FUNCIONES_HPP
#define INC_2024_2_FUNCIONES_HPP
#include "Utils.hpp"
#include "../Estructuras/Plato.hpp"
#include "../Estructuras/Cliente.hpp"

void cargar_platos_ofrecidos(const char * file_name, Plato *&arr_platos, int &n_platos);
void abrir_archivo_entrada(const char * file_name, ifstream & input);
char * leer_cadena( ifstream & input, char del);
double leer_double( ifstream & input);
void cargar_distritos(const char * file_name, Distrito *&distrito, int &n_distritos);
void cargar_clientes(const char * file_name, Cliente *&arr_clientes, int &n_clientes);
void prueba_carga_platos_ofrecidos(const char * file_name, Plato * arr_platos, int n_platos);
void abrir_archivo_salida(const char * file_name, ofstream & output);
void centrear(const char * texto, int espacio, bool slash_n, ofstream & output);
void imprimir_linea(int n, char c, bool slash_n, ofstream & output);
void prueba_carga_distritos(const char * file_name, Distrito * arr_distritos, int n_distritos);
void prueba_carga_clientes(const char * file_name, Cliente * arr_clientes, int n_clientes);
void cargar_clientes_pedidos(const char * file_name, Cliente *&arr_clientes, int n_clientes, Distrito *&arr_distritos, int n_distritos,
                             Plato *&arr_platos, int n_platos);
int buscar_cliente(Cliente * arr_clientes, int dni_leido, int n_clientes);
int buscar_plato(Plato *&arr_platos, char * cod_plato_leido, int n_platos);
void ordenar_clientes_nombre(Cliente * arr_clientes, int n_clientes);
void swap_struc( Cliente & a,  Cliente & b);
void ordenar_platos_pedidos(Cliente * arr_clientes, int n_clientes);
void swap_struc_pedidos( PlatoPedido & a, PlatoPedido & b);
void imprimir_reporte(const char * file_name, Cliente * arr_clientes, int n_clientes, Plato *arr_platos, int n_platos);
void imprimir_titulo( ofstream & output);
void imprimir_encabezado(int i, const Cliente & cliente, ofstream & output);
void recuperar_nombre_distrito(Cliente &cliente, Distrito *&arr_distritos, int n_distritos);



#endif //INC_2024_2_FUNCIONES_HPP
