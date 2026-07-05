//
// Created by User on 3/07/2026.
//

#ifndef INC_2025_2_TRANSMISION_HPP
#define INC_2025_2_TRANSMISION_HPP
#include "Streamer.hpp"
#include "Comentario.hpp"
struct Transmision {
    int id_transmision;
    Streamer streamer;
    Comentario *comentarios;
    int fecha;
    int duracion;
    int cantidad_comentarios;
};
#endif //INC_2025_2_TRANSMISION_HPP
