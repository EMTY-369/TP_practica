//
// Created by aml on 5/06/2026.
//

#ifndef ARREGLODECADENAS_LABORATORIO07_2025_1_FUNCIONES_H
#define ARREGLODECADENAS_LABORATORIO07_2025_1_FUNCIONES_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#define ANCHOREPORT 203
#define MAXPERSON 50
#define MAXINFRAC 140
#define ANCHONOMBRE 40
#define ANCHODISTRI 27
void lecturaEmpresasRegistradas(const char * file_name, int * dni, char ** nombres, char * *distrito, int& cant_person);
void lecturaPlacasRegistradas(const char * file_name, char ** placas, int * dni, int cant_person);
bool verificaSiEstaLaPlaca(char * listaDePlacas, char * placa) ;
int buquedaDni(int dni_per, int * dni, int cant_person);
char * leerCadenaTexto( ifstream & input,char c);
void modificarCadena(char * str, int cant_caract);
void reportPlacasRegistradas(const char * file_name, char ** placas, int * dni, int cant_person,char ** nombres,char * * distrito);
void lecturaTablaInfrac(const char * file_name, char ** codInfracc, double * multaInfrac, int &cantInfra);
void reportTablaInfrac(const char * file_name, char ** codInfracc, double * multa_infrac, int cant_infra);
void lecturaInfracCometidas(const char * file_name, int * fechaInfraAntig, int * fecha_pag_rec, int * cant_faltas,
                           double * pag_lev, double * pag_grav, double * pag_muy_grav,
                           int cant_person, char ** cod_infracc, int cant_infra, double * multa_infrac,char**placas);
int buscarInfraccion(char ** cod_infracc, char * cod_infraccion, int cant_infra);
int buscarPlaca(char * placa_infrac, int cant_person, char ** placas);
void ordenarArreglosFechaInfracc(int * dni, char ** nombres, char ** distrito, char ** placas,
                                int * fecha_infra_antig, int * fecha_pag_rec, double * pag_lev, double * pag_grav,
                                double * pag_muy_grav, int * cant_faltas, int cant_person);
void swapInt(int &i, int &i1);
void swapDouble(double &x, double &x1);
void swapStr(char *&a, char * &b);
void reporteFinal(const char * file_name, int * dni, char ** nombres, char ** distrito, char ** placas,
                 int * fecha_infra_antig, int * fecha_pag_rec, double * pag_lev, double * pag_grav, double * pag_muy_grav,
                 int * cant_faltas, int cant_person);
char * asignarCadena(char * codigo_infraccion);
void leerArchivo(const char*file_name, ifstream&file);
void escribirArchivo(const char*file_name, ofstream&file);
void generarSimbolos(ofstream&output,char c);
int leerFecha(ifstream&input);
#endif //ARREGLODECADENAS_LABORATORIO07_2025_1_FUNCIONES_H
