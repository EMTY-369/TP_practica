#include "Bibliotecas/Funciones.hpp"


int main() {
    int arrCodigosPlatos[MAX_PLATOS]{}, arrNumPlatosVendidos[MAX_PLATOS]{}, n_platos=0;
    double arrPrecio[MAX_PLATOS]{}, arrIngresoBruto[MAX_PLATOS]{}, arrDescuento[MAX_PLATOS]{}, arrTotal[MAX_PLATOS]{};
    bool arrTieneDescuento[MAX_PLATOS]{};

    cargar_platos("ArchivosDeDatos/lab6_RepartosARealizar.txt",
                   arrCodigosPlatos,
                   arrNumPlatosVendidos,
                   n_platos);
    cargar_platos_ofrecidos("ArchivosDeDatos/lab6_PlatosOfrecidos.txt",
                            arrPrecio,
                            arrIngresoBruto,
                            arrDescuento,
                            arrTotal,
                            arrTieneDescuento,
                            n_platos,
                            arrCodigosPlatos,
                            arrNumPlatosVendidos);

    prueba_carga_platos_vendidos("ArchivosDeReporte/ReporteDePruebaDeCargaDeDatos.txt",
                        arrCodigosPlatos,
                        arrNumPlatosVendidos,
                        n_platos,
                        arrPrecio,
                        arrIngresoBruto,
                        arrDescuento,
                        arrTotal,
                        arrTieneDescuento);
    imprimir_reporte("ArchivosDeDatos/lab6_PlatosOfrecidos.txt",
                     "ArchivosDeReporte/ReporteDePagoPorPlato.txt",
                     arrCodigosPlatos,
                     arrNumPlatosVendidos,
                     arrPrecio,
                     arrIngresoBruto,
                     arrDescuento,
                     arrTotal,
                     arrTieneDescuento,
                     n_platos);

    return 0;
}
