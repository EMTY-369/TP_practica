

#include "Bibliotecas/Funciones.hpp"



int main() {
    Transmision *transmisiones;
    int n_transmisiones=0;

    cargar_transmisiones("ArchivosDeDatos/transmisiones.csv",
                         transmisiones, n_transmisiones);
    prueba_carga_transmisiones("ArchivosDeReporte/prueba_carga_transmisiones.txt",
                               transmisiones, n_transmisiones);
    cargar_streamers("ArchivosDeDatos/streamers.csv",
                     transmisiones, n_transmisiones);
    prueba_carga_streamers("ArchivosDeReporte/prueba_streamers.txt",
                           transmisiones, n_transmisiones);
    cargar_comentarios("ArchivosDeDatos/comentarios.csv",
                       transmisiones, n_transmisiones);
    imprimir_reporte_final("ArchivosDeReporte/reporte_final.txt",
                           transmisiones, n_transmisiones);
    return 0;
}
