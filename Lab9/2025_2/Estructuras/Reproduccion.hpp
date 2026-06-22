//
// Created by User on 22/06/2026.
//

#ifndef INC_2025_2_REPRODUCCION_HPP
#define INC_2025_2_REPRODUCCION_HPP
#include "Hora.hpp"
struct Reproduccion {
    char *canal;
    double rating;
    Hora duracion;
    char **comentarios;
    int numComentarios;
};
#endif //INC_2025_2_REPRODUCCION_HPP
