//
// Created by User on 1/07/2026.
//

#ifndef INC_2026_1_MEDICO_HPP
#define INC_2026_1_MEDICO_HPP
#include "Atencion.hpp"
struct Medico {
    int codigo;
    char *nombre;
    char *especialidad;
    double tarifa;
    struct Atencion *atenciones;
    int num_atenciones;
    double ingresosPorAtencion;
};
#endif //INC_2026_1_MEDICO_HPP
