//
// Created by User on 5/07/2026.
//

#ifndef PREGUNTA_1_CLIENTE_HPP
#define PREGUNTA_1_CLIENTE_HPP
#include "TipoCliente.hpp"
#include "Cuenta.hpp"
struct Cliente {
    int dni;
    char *nombre;
    struct TipoCliente tipo_cliente;
    struct Cuenta *cuentas;
    int cantidad_cuentas;
};
#endif //PREGUNTA_1_CLIENTE_HPP
