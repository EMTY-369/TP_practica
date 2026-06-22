//
// Created by User on 22/06/2026.
//

#ifndef INC_2025_2_CATEGORIA_HPP
#define INC_2025_2_CATEGORIA_HPP
#include "Reproduccion.hpp"
struct Categoria {
    char *codigo;
    char *nombre;
    char *descripcion;
    Reproduccion *reproducciones;
    int numReproducciones;
    double promedioRating;
    Hora duracionTotal;
};
#endif //INC_2025_2_CATEGORIA_HPP
