

#include "Bibliotecas/Funciones.hpp"

int main() {
    int codigos_stream[MAX_STREAMS]{}, duraciones_stream[MAX_STREAMS]{}, codigos_idioma[MAX_STREAMS]{}, categorias_int[MAX_STREAMS]{};
    char categorias_char[MAX_STREAMS]{};
    int n_streams=0;
    int reps_antiguas[MAX_STREAMS]{}, reps_recientes[MAX_STREAMS]{}, cant_reproducciones[MAX_STREAMS]{}, tiempos_totales_repro[MAX_STREAMS]{};
    double prom_ratings_canales[MAX_STREAMS]{}, prom_drops_off[MAX_STREAMS]{};


    cargar_streams("ArchivosDeDatos/Lab5_Streams.txt",
                   codigos_stream,
                   duraciones_stream,
                   codigos_idioma,
                   categorias_int,
                   categorias_char,
                   n_streams);
    probar_carga_streams("ArchivosDeReporte/prueba_carga_streams.txt",
                          codigos_stream,
                          duraciones_stream,
                          codigos_idioma,
                          categorias_int,
                          categorias_char,
                          n_streams);

    cargar_canales("ArchivosDeDatos/Lab5_Canales.txt",
                   reps_antiguas,
                   reps_recientes,
                   cant_reproducciones,
                   tiempos_totales_repro,
                   prom_ratings_canales,
                   prom_drops_off,
                   n_streams,
                   codigos_stream,
                   duraciones_stream,
                   codigos_idioma,
                   categorias_int,
                   categorias_char);

    imprimir_reporte("ArchivosDeReporte/Reproducciones_Streams.txt",
                     codigos_stream,
                     duraciones_stream,
                     codigos_idioma,
                     categorias_int,
                     categorias_char,
                     reps_antiguas,
                     reps_recientes,
                     cant_reproducciones,
                     tiempos_totales_repro,
                     prom_ratings_canales,
                     prom_drops_off,
                     n_streams,
                     true);

    ordenar_categoria_drops_off(codigos_stream,
                     duraciones_stream,
                     codigos_idioma,
                     categorias_int,
                     categorias_char,
                     reps_antiguas,
                     reps_recientes,
                     cant_reproducciones,
                     tiempos_totales_repro,
                     prom_ratings_canales,
                     prom_drops_off,
                     n_streams);

    imprimir_reporte("ArchivosDeReporte/Reproducciones_Streams_2.txt",
                     codigos_stream,
                     duraciones_stream,
                     codigos_idioma,
                     categorias_int,
                     categorias_char,
                     reps_antiguas,
                     reps_recientes,
                     cant_reproducciones,
                     tiempos_totales_repro,
                     prom_ratings_canales,
                     prom_drops_off,
                     n_streams,
                     false);

    return 0;
}
