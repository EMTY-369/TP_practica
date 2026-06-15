//
// Created by User on 14/06/2026.
//

#ifndef INC_2025_1_EMPRESASREGISTRADAS_HPP
#define INC_2025_1_EMPRESASREGISTRADAS_HPP
#include "Fecha.hpp"
struct EmpresasRegistradas {
    int dni;
    char *nombre;
    char *distrito;
    char *placas[10];
    int numPlacas;
    Fecha fechaDeInfraccion;
    Fecha fechaDePago;
    double totalDeMultas;
    double totalPagado;
    double totalAdeudado;
    int cantidadDeFaltas;
};
#endif //INC_2025_1_EMPRESASREGISTRADAS_HPP
