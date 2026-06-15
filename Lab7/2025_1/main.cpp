#include "Bibliotecas/Funciones.hpp"

int main() {
    int dnis_empresas[MAX_DNI]{}, infrac_mas_antiguas[MAX_DNI]{}, pagos_mas_recientes[MAX_DNI]{}, cants_faltas[MAX_DNI]{};
    double pagos_leves[MAX_DNI]{}, pagos_graves[MAX_DNI]{}, pagos_muy_graves[MAX_DNI]{};
    char *nombres[MAX_DNI]{}, *distritos[MAX_DNI]{}, *placas[MAX_DNI]{};
    int n_dnis=0;
    for (int i=0; i<MAX_DNI; i++) {
        placas[i] = new char[MAX_PLACAS]{};
    }
    for (int i=0; i<MAX_DNI; i++) {
        pagos_muy_graves[i] = 0;
    }

    cargar_empresas_registradas("ArchivosDeDatos/EmpresasRegistradas_Lab07.csv",
                                dnis_empresas,
                                nombres,
                                distritos,
                                n_dnis);
    cargar_placas("ArchivosDeDatos/PlacasRegistradas_Lab07.txt",
                  placas,
                  dnis_empresas,
                  n_dnis);
    prueba_carga_empresas_placas("ArchivosDeReporte/ReporteDePrueba01.txt",
                                 dnis_empresas,
                                 nombres,
                                 distritos,
                                 placas,
                                 n_dnis);
    int n_infrac=0;
    char *cods_infrac[MAX_INFRAC]{};
    double multas_infrac[MAX_INFRAC]{};
    cargar_infracciones("ArchivosDeDatos/TablaDeInfracciones_Lab07.csv",
                        cods_infrac,
                        multas_infrac,
                        n_infrac);
    prueba_carga_infracciones("ArchivosDeReporte/ReporteDePrueba02.txt",
                               cods_infrac,
                               multas_infrac,
                               n_infrac);
    cargar_infracciones_cometidas("ArchivosDeDatos/InfraccionesCometidas_Lab07.csv",
                                  placas,
                                  n_dnis,
                                  cods_infrac,
                                  multas_infrac,
                                  n_infrac,
                                  infrac_mas_antiguas,
                                  pagos_mas_recientes,
                                  cants_faltas,
                                  pagos_leves,
                                  pagos_graves,
                                  pagos_muy_graves);
    ordenar_arreglos(dnis_empresas,
                     nombres,
                     distritos,
                     placas,
                     infrac_mas_antiguas,
                     pagos_mas_recientes,
                     cants_faltas,
                     pagos_leves,
                     pagos_graves,
                     pagos_muy_graves,
                     n_dnis);
    imprimir_reporte("ArchivosDeReporte/Reporte_final.txt",
                     dnis_empresas,
                     nombres,
                     distritos,
                     placas,
                     infrac_mas_antiguas,
                     pagos_mas_recientes,
                     cants_faltas,
                     pagos_leves,
                     pagos_graves,
                     pagos_muy_graves, n_dnis);
    return 0;
}
