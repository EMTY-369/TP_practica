cmake_minimum_required(VERSION 4.2)
project(2026_adaptado)

set(CMAKE_CXX_STANDARD 20)

add_executable(2026_adaptado main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.hpp
        Bibliotecas/Utils.hpp
        Estructuras/Medico.hpp
        Estructuras/Fecha.hpp
        Estructuras/Hora.hpp
        Estructuras/Codigo.hpp
        Estructuras/Atencion.hpp)
