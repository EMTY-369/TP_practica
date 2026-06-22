

#include "Bibliotecas/Funciones.hpp"



int main() {
    Categoria *arrCategorias;
    int n_categorias=0;


    cargar_categorias("ArchivosDeDatos/Lab8_Categorias.csv",
                      arrCategorias, n_categorias);
    prueba_carga_Reporte_final("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
                            arrCategorias, n_categorias, 1);
    cargar_reproducciones("ArchivosDeDatos/Lab8_StreamsReproducidos.csv",
                          arrCategorias, n_categorias);
    prueba_carga_Reporte_final("ArchivosDeReporte/ReporteDePruebaConReproducciones.txt",
                               arrCategorias, n_categorias, 2);
    ordenar_nombre_categoria(arrCategorias, n_categorias);
    ordenar_canales_rating(arrCategorias, n_categorias);
    prueba_carga_Reporte_final("ArchivosDeReporte/ReporteDePruebaOrdenado.txt",
                               arrCategorias, n_categorias, 2);
    cargar_comentarios("ArchivosDeDatos/Lab8_ComentariosAlCanal.csv",
                       arrCategorias, n_categorias);
    prueba_carga_Reporte_final("ArchivosDeReporte/ReporteDePruebaConComentarios.txt",
                               arrCategorias, n_categorias, 3);

    return 0;
}
