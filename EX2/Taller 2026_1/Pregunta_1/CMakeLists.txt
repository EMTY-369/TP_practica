cmake_minimum_required(VERSION 4.2)
project(Pregunta_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pregunta_1 main.cpp
        Bibliotecas/Funciones.cpp
        Bibliotecas/Funciones.hpp
        Bibliotecas/Utils.hpp
        Estructuras/TipoCliente.hpp
        Estructuras/Transaccion.hpp
        Estructuras/Cuenta.hpp
        Estructuras/Cliente.hpp
)
