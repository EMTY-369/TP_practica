#include "Bibliotecas/Funciones.hpp"



int main() {
    ListaCategoria lista_categorias;

    cargar_categorias("ArchivosDeDatos/Lab9_Categorias.csv", lista_categorias);
    probar_carga_categorias("ArchivosDeReporte/prueba_carga_categorias.txt",lista_categorias);
    cargar_streams("ArchivosDeDatos/Lab9_StreamsReproducidos.csv", lista_categorias);
    calcular_promedios_dropp_off(lista_categorias);
    imprimir_reporte("ArchivosDeReporte/ReportePorCategorias.txt", lista_categorias);
    eliminar_lista_por_dropp_off(lista_categorias, 3.5);
    imprimir_reporte("ArchivosDeReporte/ReporteDeCategoriasEliminadas.txt", lista_categorias);

    return 0;
}
