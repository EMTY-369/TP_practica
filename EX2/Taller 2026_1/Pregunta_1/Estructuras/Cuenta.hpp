//
// Created by User on 5/07/2026.
//

#ifndef PREGUNTA_1_CUENTA_HPP
#define PREGUNTA_1_CUENTA_HPP
#include "Transaccion.hpp"
struct Cuenta {
    int nroCuenta;
    double saldoInicial;
    double saldoFinal;
    int cantidadRetiros;
    int cantidadDepositos;
    char *estado;
    Transaccion *transacciones;
    int cantidadTransacciones;
};
#endif //PREGUNTA_1_CUENTA_HPP
