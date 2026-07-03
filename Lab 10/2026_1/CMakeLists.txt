cmake_minimum_required(VERSION 4.2)
project(2026_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(2026_1 main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.hpp
        Bibliotecas/Utils.hpp
        Estructuras/Fecha.hpp
        Estructuras/Hora.hpp
        Estructuras/Codigo.hpp
        Estructuras/Atencion.hpp
        Estructuras/Medico.hpp
        Estructuras/Nodo.hpp
        Estructuras/ListaMedicosTAD.hpp)
