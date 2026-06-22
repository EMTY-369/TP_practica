//
// Created by User on 22/06/2026.
//

#ifndef INC_2026_ADAPTADO_ATENCION_HPP
#define INC_2026_ADAPTADO_ATENCION_HPP
#include "Fecha.hpp"
#include "Hora.hpp"
#include "Codigo.hpp"
struct Atencion {
    Fecha fecha;
    int codigoMedico;
    Hora duracion;
    Codigo paciente;
};
#endif //INC_2026_ADAPTADO_ATENCION_HPP
