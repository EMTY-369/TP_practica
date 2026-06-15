#include "Bibliotecas/Funciones.hpp"


int main() {
    int arr_codigo_infraccion[MAX_INFRACACIONES]{},n_infrac=0;
    double arr_multas_infraccion[MAX_INFRACACIONES]{};
    int arr_dni[MAX_DNI]{}, arr_mas_multa_antigua[MAX_DNI]{}, arr_ultima_pendiente[MAX_DNI]{}, n_cometidas=0;
    double arr_total_multas[MAX_DNI]{}, arr_total_pagadas[MAX_DNI]{}, arr_total_pendientes[MAX_DNI]{};

    cargar_infracciones("ArchivosDeDatos/TablaDeInfracciones_Lab06.txt",
                        arr_codigo_infraccion,
                        arr_multas_infraccion,
                        n_infrac);
    probar_carga_infracciones("ArchivosDeReporte/PruebaTablaInf.txt",
                               arr_codigo_infraccion,
                               arr_multas_infraccion,
                               n_infrac);
    cargar_infracciones_cometidas("ArchivosDeDatos/InfraccionesCometidas_Lab06.txt",
                                  "ArchivosDeDatos/PlacasRegistradas.txt",
                                  arr_codigo_infraccion,
                                  arr_multas_infraccion,
                                  n_infrac,
                                  arr_dni,
                                  arr_mas_multa_antigua,
                                  arr_ultima_pendiente,
                                  arr_total_multas,
                                  arr_total_pagadas,
                                  arr_total_pendientes,
                                  n_cometidas);
    imprimir_reporte("ArchivosDeReporte/ReporteDeMultas.txt",
                     "ArchivosDeDatos/PlacasRegistradas.txt",
                     arr_dni,
                     arr_mas_multa_antigua,
                     arr_ultima_pendiente,
                     arr_total_multas,
                     arr_total_pagadas,
                     arr_total_pendientes,
                     n_cometidas);
    return 0;
}
