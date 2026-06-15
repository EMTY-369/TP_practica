

#include "Bibliotecas/Funciones.hpp"


int main() {
    //canales.txt
    int fecha_canales[MAX_CANALES]{}, codigos_int_canales[MAX_CANALES]{};
    char codigos_char_canales[MAX_CANALES]{};
    double ratings_canales[MAX_CANALES]{};
    int n_canales=0;
    //etiquetas.txt
    int codigos_etiquetas[MAX_ETIQUETAS]{}, tiempo_duracion_etiquetas[MAX_ETIQUETAS]{};
    int n_etiquetas=0;
    //reproducciones
    int cant_total_reproducciones_canales[MAX_CANALES]{}, tiempo_total_reproducciones_canales[MAX_CANALES]{};
    double ingresos_por_reproducciones[MAX_CANALES]{};
    int cant_total_reproducciones_etiquetas[MAX_ETIQUETAS]{}, tiempo_total_reproducciones_etiquetas[MAX_ETIQUETAS]{};


    double tarifa=0.78;

    cargar_canales("ArchivosDeDatos/Lab4_Canales.txt",
                   fecha_canales,
                   codigos_int_canales,
                   codigos_char_canales,
                   ratings_canales,
                   n_canales);
    probar_canales("ArchivosDeReporte/reporte_prueba_canales.txt",
                    fecha_canales,
                    codigos_int_canales,
                    codigos_char_canales,
                    ratings_canales,
                    n_canales);

    cargar_etiquetas("ArchivosDeDatos/Lab4_Etiquetas.txt",
                     codigos_etiquetas,
                     tiempo_duracion_etiquetas,
                     n_etiquetas);
    probar_etiquetas("ArchivosDeReporte/reporte_prueba_etiquetas.txt",
                     codigos_etiquetas,
                     tiempo_duracion_etiquetas,
                     n_etiquetas);

    procesar_reproducciones("ArchivosDeDatos/Lab4_ReproduccionesDeEtiquetas.txt",
                             codigos_char_canales,
                             codigos_int_canales,
                             codigos_etiquetas,
                             ratings_canales,
                             tiempo_duracion_etiquetas,
                             cant_total_reproducciones_canales,
                             cant_total_reproducciones_etiquetas,
                             ingresos_por_reproducciones,
                             tiempo_total_reproducciones_canales,
                             tiempo_total_reproducciones_etiquetas,
                             n_canales,
                             n_etiquetas,
                             tarifa);

    generar_reporte("ArchivosDeReporte/ReporetDeCanales_Y_Etiquetsa.txt",
                    fecha_canales,codigos_char_canales,codigos_int_canales,ratings_canales,n_canales,
                    codigos_etiquetas, tiempo_duracion_etiquetas, n_etiquetas,
                    cant_total_reproducciones_canales,cant_total_reproducciones_etiquetas,
                    ingresos_por_reproducciones, tarifa,
                    tiempo_total_reproducciones_canales,tiempo_total_reproducciones_etiquetas);



    return 0;
}
