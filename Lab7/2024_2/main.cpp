#include "Bibliotecas/Funciones.hpp"


int main() {
    int arr_dnis_repartidores[MAX_REPARTIDORES]{}, arr_cods_distrito[MAX_REPARTIDORES]{}, n_repartidores=0;
    char *arr_nombres_repartidores[MAX_REPARTIDORES]{}, *arr_movilidad[MAX_REPARTIDORES]{}, *arr_nombres_distritos[MAX_REPARTIDORES]{};
    int arr_cods_platos[MAX_PLATOS]{}, n_platos=0;
    double arr_precio_platos[MAX_PLATOS]{}, arr_descuentos_platos[MAX_PLATOS]{};
    char *arr_nombres_platos[MAX_PLATOS]{}, *arr_categoria_platos[MAX_PLATOS]{};

    cargar_repartidores("ArchivosDeDatos/lab7_Repartidores.txt",
                        arr_dnis_repartidores, arr_cods_distrito, arr_nombres_repartidores,arr_movilidad,
                        arr_nombres_distritos, n_repartidores);
    cargar_platos("ArchivosDeDatos/lab7_PlatosOfrecidos.txt",
                   arr_cods_platos, arr_precio_platos, arr_descuentos_platos,
                   arr_nombres_platos, arr_categoria_platos, n_platos);
    prueba_carga_repartidores_platos("ArchivosDeReporte/ReporteDePrueba.txt",
                                     arr_dnis_repartidores, arr_cods_distrito, arr_nombres_repartidores,arr_movilidad,
                                     arr_nombres_distritos, n_repartidores,
                                     arr_cods_platos, arr_precio_platos, arr_descuentos_platos,
                                     arr_nombres_platos, arr_categoria_platos, n_platos);
    ordenar_repartidores(arr_dnis_repartidores, arr_cods_distrito, arr_nombres_repartidores, arr_movilidad, arr_nombres_distritos, n_repartidores);
    prueba_carga_repartidores_platos("ArchivosDeReporte/ReporteOrdenadoDePrueba.txt",
                                    arr_dnis_repartidores, arr_cods_distrito, arr_nombres_repartidores,arr_movilidad,
                                    arr_nombres_distritos, n_repartidores,
                                    arr_cods_platos, arr_precio_platos, arr_descuentos_platos,
                                    arr_nombres_platos, arr_categoria_platos, n_platos);
    int arr_total_platos[MAX_REPARTIDORES]{};
    double arr_monto_total[MAX_REPARTIDORES]{}, arr_monto_descuent_platos[MAX_REPARTIDORES]{}, arr_descuento_cliente_repart[MAX_REPARTIDORES]{};
    double arr_pagos_respartidores[MAX_REPARTIDORES]{};
    int arr_cants[MAX_PLATOS]{};
    double arr_descuento_cliente_platos[MAX_PLATOS]{};
    return 0;
}
