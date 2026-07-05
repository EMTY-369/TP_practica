

#include "Bibliotecas/Funciones.hpp"


int main() {
    ListaPalabra lista_stopwords, palabras, lista_frecuencias;
    cargar_stopwrods("ArchivosDeDatos/stopwords.txt", lista_stopwords);
    prueba_carga("ArchivosDeReporte/reporteStopswords.txt", "PRUEBA DE CARGA DE STOPWORDS",
                 lista_stopwords, false);
    cargar_palabras("ArchivosDeDatos/comentarios.csv", palabras);
    prueba_carga("ArchivosDeReporte/reporteComentarios.txt", "PRUEBA DE CARGA DE PALABRAS EN COMENTARIOS",
                 palabras, true);
    eliminar_palabras_stopwords(lista_stopwords, palabras);
    prueba_carga("ArchivosDeReporte/reporteComentariosEliminados.txt", "PRUEBA DE CARGA DE PALABRAS EN COMENTARIOS - ELIMINADOS",
                 palabras, true);
    imprimir_lista_palabras("ArchivosDeReporte/palabras_frecuencia.txt", palabras);
    cargar_frecuencia("ArchivosDeReporte/palabras_frecuencia.txt", lista_frecuencias);
    prueba_carga("ArchivosDeReporte/reporteFrecuencias.txt", "PRUEBA DE CARGA DE FRECUENCIAS DE PALABRAS",
                 lista_frecuencias, true);

    return 0;
}
