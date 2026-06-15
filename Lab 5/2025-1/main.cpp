
#include "Bibliotecas/Funciones.hpp"


int main() {
    //empresas
    int DNIs_empresas[MAX_EMPRESAS]{}, cants_leves[MAX_EMPRESAS]{}, cants_graves[MAX_EMPRESAS]{};
    int cants_muy_graves[MAX_EMPRESAS]{}, cants_totales[MAX_EMPRESAS]{}, n_empresas=0;
    double costos_leves[MAX_EMPRESAS]{}, costos_graves[MAX_EMPRESAS]{}, costos_muy_graves[MAX_EMPRESAS]{};
    double costos_totales[MAX_EMPRESAS]{};
    //infracciones
    int codigos_int_infrac[MAX_INFRACCIONES]{}, cants_infrac[MAX_INFRACCIONES]{}, n_infrac=0;
    double costos_infrac[MAX_INFRACCIONES]{}, monto_totales[MAX_INFRACCIONES]{};
    char codigos_char_infrac[MAX_INFRACCIONES]{};
    //placas
    char placas_char[MAX_PLACAS]{};
    int placas_int[MAX_PLACAS]{},DNIs_placas[MAX_PLACAS]{}, n_placas=0;



    cargar_empresas("ArchivosDeDatos/EmpresasRegistradas_Lab05.txt",
                    DNIs_empresas,
                    n_empresas);
    probar_carga_empresas("ArchivosDeReporte/prueba_carga_empresas.txt",
                          DNIs_empresas,
                          n_empresas);

    cargar_infracciones("ArchivosDeDatos/TablaDeInfracciones_Lab05.txt",
                        codigos_char_infrac,
                        codigos_int_infrac,
                        costos_infrac,
                        n_infrac);
    probar_carga_infracciones("ArchivosDeReporte/prueba_carga_infracciones.txt",
                              codigos_char_infrac,
                              codigos_int_infrac,
                              costos_infrac,
                              n_infrac);
    cargar_placas("ArchivosDeDatos/PlacasRegistradas_Lab05.txt",
                  placas_char,
                  placas_int,
                  DNIs_placas,
                  n_placas);

    cargar_multas("ArchivosDeDatos/InfraccionesCometidas_Lab05.txt",
                  cants_leves,
                  cants_graves,
                  cants_muy_graves,
                  cants_totales,
                  costos_leves,
                  costos_graves,
                  costos_muy_graves,
                  costos_totales,
                  n_empresas,
                  cants_infrac,
                  monto_totales,
                  n_infrac,
                  DNIs_empresas,
                  codigos_char_infrac,
                  codigos_int_infrac,
                  costos_infrac,
                  placas_char,
                  placas_int,
                  DNIs_placas,
                  n_placas);

    generar_reporte("ArchivosDeReporte/Reporte_final.txt",
                  cants_leves,
                  cants_graves,
                  cants_muy_graves,
                  cants_totales,
                  costos_leves,
                  costos_graves,
                  costos_muy_graves,
                  costos_totales,
                  n_empresas,
                  cants_infrac,
                  monto_totales,
                  n_infrac,
                  DNIs_empresas,
                  codigos_char_infrac,
                  codigos_int_infrac,
                  costos_infrac);


    return 0;
}
