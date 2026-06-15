cmake_minimum_required(VERSION 4.2)
project(2024_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(2024_2 main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.hpp
        Bibliotecas/Utils.hpp
        Estructuras/Distrito.hpp
        Estructuras/Plato.hpp
        Estructuras/PlatoPedido.hpp
        Estructuras/Cliente.hpp)
