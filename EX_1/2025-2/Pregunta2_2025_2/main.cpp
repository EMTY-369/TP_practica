


#include "Bibliotecas/Funciones.hpp"

int main() {
    int arr_codigos_streams[MAX_STREAMS]{},arr_duraciones_streams[MAX_STREAMS]{}, arr_codigos_idiomas[MAX_STREAMS]{};
    int arr_categorias_int[MAX_STREAMS]{}, n_streams=0;
    char arr_categorias_char[MAX_STREAMS]{};

    int arr_rep_antiguas[MAX_STREAMS]{}, arr_rep_recientes[MAX_STREAMS]{}, arr_n_rep[MAX_STREAMS]{};
    double arr_prom_rating[MAX_STREAMS]{}, arr_prom_drop[MAX_STREAMS]{};


    cargar_streams("ArchivosDeDatos/Streams.txt",
                   arr_codigos_streams,
                   arr_duraciones_streams,
                   arr_codigos_idiomas,
                   arr_categorias_int,
                   arr_categorias_char,
                   n_streams);
    probar_carga_streams("ArchivosDeReporte/prueba_carga_streams.txt",
                         arr_codigos_streams,
                         arr_duraciones_streams,
                         arr_codigos_idiomas,
                         arr_categorias_int,
                         arr_categorias_char,
                         n_streams);

    cargar_canales("ArchivosDeDatos/Canales (1).txt",
                   arr_codigos_streams,
                   n_streams,
                   arr_rep_antiguas,
                   arr_rep_recientes,
                   arr_n_rep,
                   arr_prom_rating,
                   arr_prom_drop);

    imprimir_reporte("ArchivosDeReporte/Reproducciones-Streams.txt",
                     true,
                     arr_codigos_streams,
                     arr_duraciones_streams,
                     arr_codigos_idiomas,
                     arr_categorias_int,
                     arr_categorias_char,
                     n_streams,
                     arr_rep_antiguas,
                     arr_rep_recientes,
                     arr_n_rep,
                     arr_prom_rating,
                     arr_prom_drop);
    ordenar_idioma_drop(arr_codigos_streams,
                        arr_duraciones_streams,
                        arr_codigos_idiomas,
                        arr_categorias_int,
                        arr_categorias_char,
                        n_streams,
                        arr_rep_antiguas,
                        arr_rep_recientes,
                        arr_n_rep,
                        arr_prom_rating,
                        arr_prom_drop);



    return 0;
}
