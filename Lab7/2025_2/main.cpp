#include "Bibliotecas/Funciones.hpp"



int main() {
    int arr_fechas_streams[MAX_STREAMS]{}, arr_duraciones_streams[MAX_STREAMS]{}, n_streams=0;
    double arr_ratings_calidad[MAX_STREAMS]{}, arr_tasas_dropoffs[MAX_STREAMS]{};
    char *arr_nombres_canales[MAX_STREAMS]{}, *arr_categorias_streams[MAX_STREAMS]{};

    char *arr_lista_categorias[MAX_CATEGORIAS]{}, *arr_nombres_categorias[MAX_CATEGORIAS]{};
    int n_categorias=0;

    char categoria[]="steins_gate", *nombArch, *enlace;
    generarArchivoEnlace(categoria, nombArch, enlace);

    cargar_categorias("ArchivosDeDatos/Lab6_Categorias.txt",
                      arr_lista_categorias,arr_nombres_categorias, n_categorias);
    prueba_carga_catergorias("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt",
                             arr_lista_categorias,arr_nombres_categorias, n_categorias);
    cargar_streams("ArchivosDeDatos/Lab6_StreamsReproducidos.txt",
                   arr_fechas_streams, arr_duraciones_streams, arr_ratings_calidad, arr_tasas_dropoffs,
                   arr_nombres_canales, arr_categorias_streams, n_streams);
    prueba_carga_streams("ArchivosDeReporte/ReporteDePruebaDeStreamsReproducidos.txt",
                         arr_fechas_streams, arr_duraciones_streams, arr_ratings_calidad, arr_tasas_dropoffs,
                         arr_nombres_canales, arr_categorias_streams, n_streams);
    imprimir_reportes(arr_lista_categorias, arr_nombres_categorias, n_categorias,
                      arr_fechas_streams, arr_duraciones_streams, arr_tasas_dropoffs, arr_ratings_calidad,
                      arr_nombres_canales, arr_categorias_streams, n_streams);

    return 0;
}
