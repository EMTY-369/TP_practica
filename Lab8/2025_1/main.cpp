#include "Bibliotecas/Funciones.hpp"


int main() {
    TablaDeInfracciones arrTablaDeInfracciones[MAX_INFRACCIONES]{};
    EmpresasRegistradas arrEmpresasRegistradas[MAX_EMPRESAS]{};
    int n_infrac = 0, n_empresas = 0;

    cargar_tabla_infracciones("ArchivosDeDatos/TablaDeInfracciones_Lab08.csv",
                              arrTablaDeInfracciones, n_infrac);
    cargar_empresas_registradas("ArchivosDeDatos/EmpresasRegistradas_Lab08.csv",
                                 arrEmpresasRegistradas, n_empresas);
    cargar_placas_registradas("ArchivosDeDatos/PlacasRegistradas_Lab08.txt",
                              arrEmpresasRegistradas, n_empresas);
    cargar_infracciones_cometidas("ArchivosDeDatos/InfraccionesCometidas_Lab08.csv",
                                  arrEmpresasRegistradas, n_empresas, arrTablaDeInfracciones, n_infrac);
    ordenar_empresas(arrEmpresasRegistradas, n_empresas);
    ordenar_infracciones(arrTablaDeInfracciones, n_infrac);
    imprimir_reporte("ArchivosDeReporte/Reporte_final.txt",
                     arrEmpresasRegistradas, n_empresas,
                     arrTablaDeInfracciones, n_infrac);


    return 0;
}
