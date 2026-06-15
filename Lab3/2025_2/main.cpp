

#include "Bibliotecas/Funciones.hpp"


int main() {
    double tarifa_duracion_etiqueta=0.78;

    calcular_reporte(tarifa_duracion_etiqueta,
                     "ArchivosDeDatos/lab3_Canales.txt",
                     "ArchivosDeDatos/lab3_Etiquetas.txt",
                     "ArchivosDeDatos/lab3_ReproduccionesDeEtiquetas.txt",
                     "ArchivosDeReporte/Reporte.txt");

    return 0;
}
