cmake_minimum_required(VERSION 4.2)
project(Pregunta_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pregunta_2 main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.hpp
        Bibliotecas/Utils.hpp
        Estructuras/Cuenta.hpp
        Estructuras/Cliente.hpp
        Estructuras/Nodo.hpp
        Estructuras/ListaClientes.hpp)
