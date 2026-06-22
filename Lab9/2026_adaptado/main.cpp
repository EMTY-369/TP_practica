


#include "Bibliotecas/Funciones.hpp"


int main() {
    Medico *arrMedicos;
    Atencion *arrAtenciones;
    int n_med=0, n_atenciones=0;

    cargar_medicos("ArchivosDeDatos/Especialidades_Medicos_TP_Lab8.csv",
                   arrMedicos, n_med);
    prueba_carga_medicos("ArchivosDeReporte/prueba_carga_medicos.txt",
                          arrMedicos, n_med);
    cargar_atenciones("ArchivosDeDatos/Atenciones_TP_Lab8.csv",
                      arrAtenciones, n_atenciones);
    prueba_atenciones("ArchivosDeReporte/prueba_atenciones.txt",
                       arrAtenciones, n_atenciones);
    ordenar_atenciones(arrAtenciones, n_atenciones);
    prueba_atenciones("ArchivosDeReporte/prueba_atenciones_ordenado.txt",
                       arrAtenciones, n_atenciones);
    imprimir_reporte("ArchivosDeReporte/Reporte_Final.txt",
                     arrMedicos, n_med,
                     arrAtenciones, n_atenciones);
    return 0;
}
