//
// Created by User on 6/07/2026.
//

#ifndef PREGUNTA_2_CLIENTE_HPP
#define PREGUNTA_2_CLIENTE_HPP
#include "Cuenta.hpp"
struct Cliente {
    int dni;
    char *nombre;
    char tipoCliente;
    Cuenta *cuentas;
    int cantidadCuentas;
    double saldoTotal;
    int cantidadCuentasHabilitadas;
    int cantidadCuentasDeshabilitadas;
};
#endif //PREGUNTA_2_CLIENTE_HPP
