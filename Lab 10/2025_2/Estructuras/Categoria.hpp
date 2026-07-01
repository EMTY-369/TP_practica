//
// Created by User on 29/06/2026.
//

#ifndef INC_2025_2_CATEGORIA_HPP
#define INC_2025_2_CATEGORIA_HPP
struct Categoria {
    char* codigo;
    char* nombre;
    char* descripcion;
    char* canalConDuracionMaxima;
    int duracionMaxima;
    int duracionTotal;
    double arrDropOff[20];
    int cantidadDeReproducciones;
    double promedioDropoff;
};
#endif //INC_2025_2_CATEGORIA_HPP
