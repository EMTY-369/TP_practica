#include <iostream>
#include "Bibliotecas/Funciones.hpp"

int main() {

    calcular_reporte("ArchivosDeDatos/EmpresasRegistradas_Lab03.txt",
                     "ArchivosDeDatos/InfraccionesCometidas_Lab03.txt",
                     "ArchivosDeDatos/TablaDeInfracciones_Lab03.txt",
                     "ArchivosDeReporte/Reporte.txt");

    return 0;
}
