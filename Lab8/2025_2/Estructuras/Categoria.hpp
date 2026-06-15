//
// Created by User on 14/06/2026.
//

#ifndef INC_2025_2_CATEGORIA_HPP
#define INC_2025_2_CATEGORIA_HPP
#include "Reproduccion.hpp"
struct Categoria {
    char codigo[9]{};
    char *nombre;
    Reproduccion *reproducciones;
    int numReproducciones=0;
    double promedioRating=0;
    int duracionTotal=0;
};
#endif //INC_2025_2_CATEGORIA_HPP
