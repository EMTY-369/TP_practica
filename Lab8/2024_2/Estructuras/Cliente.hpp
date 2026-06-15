//
// Created by User on 15/06/2026.
//

#ifndef INC_2024_2_CLIENTE_HPP
#define INC_2024_2_CLIENTE_HPP
#include "Distrito.hpp"
#include "PlatoPedido.hpp"
#include "../Bibliotecas/Utils.hpp"

struct Cliente {
    int dni;
    char* nombre;
    Distrito distrito;
    PlatoPedido pedidos[MAX_PEDIDOS];
    int cantidadDePedidos;
    double montoTotal;
};
#endif //INC_2024_2_CLIENTE_HPP
