//
// Created by User on 1/07/2026.
//

#ifndef INC_2026_1_ATENCION_HPP
#define INC_2026_1_ATENCION_HPP
#include "Fecha.hpp"
#include "Codigo.hpp"
#include "Hora.hpp"
struct Atencion {
    Fecha fecha;
    Hora duracion;
    Codigo paciente;
};
#endif //INC_2026_1_ATENCION_HPP
