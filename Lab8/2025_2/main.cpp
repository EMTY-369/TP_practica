#include "Bibliotecas/Funciones.hpp"


int main() {
    Categoria *arr_categorias;
    int cant_categorias=0;

    cargar_categorias("ArchivosDeDatos/Lab7_Categorias.csv",
                      arr_categorias, cant_categorias);
    prueba_categorias("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
                      "PRUEBA DE CARGA DE LAS CATEGORIAS",
                      arr_categorias, cant_categorias, true);
    cargar_streams_reproducidos("ArchivosDeDatos/Lab7_Reproducciones.csv",
                                arr_categorias, cant_categorias);
    prueba_categorias("ArchivosDeReporte/ReporteDePruebaConReproducciones.txt",
                      "PRUEBA DE CARGA DE LOS STREAMS REPRODUCIDOS",
                      arr_categorias, cant_categorias, false);
    calculo_rating_prom_y_duraciones(arr_categorias, cant_categorias);
    imprimir_reporte("ArchivosDeReporte/ReportePorCategorias.txt",
                     arr_categorias, cant_categorias);

    return 0;
}
