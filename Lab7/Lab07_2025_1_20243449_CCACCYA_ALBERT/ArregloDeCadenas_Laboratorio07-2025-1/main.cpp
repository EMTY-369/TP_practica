#include "Bibliotecas/funciones.h"




int main() {
    // 77763722,farfan salazar margot,La Molina

    int dni[MAXPERSON]{},fechaInfraAntig[MAXPERSON],fechaPagRec[MAXPERSON]{},cantFaltas[MAXPERSON]{},cantPerson=0;
    for(int i=0;i<MAXPERSON;i++) {
        fechaInfraAntig[i]=99999999;
    }
    double pagLev[MAXPERSON]{},pagGrav[MAXPERSON]{},pagMuyGrav[MAXPERSON]{};
    char*nombres[MAXPERSON]{},*distrito[MAXPERSON]{};
    char *placas[60]{};
    // G2007,425.23,No conducir por el carril de extremo derecho de la calzada un vehiculo de transporte p�blico de pasajeros o de carga.
    char *codInfracc[MAXINFRAC]{};
    double multaInfrac[MAXINFRAC]{};
    int cantInfra=0;
    lecturaEmpresasRegistradas("ArchivosDeDatos/EmpresasRegistradas_Lab07.csv",dni,nombres,distrito,cantPerson);
    lecturaPlacasRegistradas("ArchivosDeDatos/PlacasRegistradas_Lab07.txt",placas,dni,cantPerson);
    reportPlacasRegistradas("ArchivosDeReporte/ReporteDePrueba01.txt",placas,dni,cantPerson,nombres,distrito);
    lecturaTablaInfrac("ArchivosDeDatos/TablaDeInfracciones_Lab07.csv",codInfracc,multaInfrac,cantInfra);
    reportTablaInfrac("ArchivosDeReporte/ReporteDePrueba02.txt",codInfracc,multaInfrac,cantInfra);
    lecturaInfracCometidas("ArchivosDeDatos/InfraccionesCometidas_Lab07.csv",fechaInfraAntig,fechaPagRec,cantFaltas,pagLev,pagGrav,pagMuyGrav,cantPerson,codInfracc,cantInfra,multaInfrac,placas);
    ordenarArreglosFechaInfracc(dni,nombres,distrito,placas,fechaInfraAntig,fechaPagRec,pagLev,pagGrav,pagMuyGrav,cantFaltas,cantPerson);
    reporteFinal("ArchivosDeReporte/reporteFinal.txt",dni,nombres,distrito,placas,fechaInfraAntig,fechaPagRec,pagLev,pagGrav,pagMuyGrav,cantFaltas,cantPerson);
    return 0;
}
