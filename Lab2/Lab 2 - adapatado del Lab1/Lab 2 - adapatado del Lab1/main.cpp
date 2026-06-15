#include "Bibliotecas/Funciones.hpp"

int main() {
    int fecha_inicio= 20230405, fecha_final= 20230427;

    calcular_el_reporte(fecha_inicio, fecha_final, "ArchivosDeDatos/ClinicaDeUrgencias_TP.txt", "ArchivosDeReporte/Reporte.txt");

    return 0;
}
