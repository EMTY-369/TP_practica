
#include "Bibliotecas/Funciones.hpp"

int main() {
    int arr_dia_semana[MAX_DISPONIBILIDAD]{}, arr_hora_inicio[MAX_DISPONIBILIDAD]{}, arr_hora_final[MAX_DISPONIBILIDAD]{};
    int n_dispo=0;

    int arr_aulas_int[MAX_AULAS]{}, arr_cant_sesiones[MAX_AULAS]{}, arr_dia_temprano[MAX_AULAS]{}, arr_dia_tarde[MAX_AULAS]{};
    int arr_hora_temprano[MAX_AULAS]{}, arr_hora_tarde[MAX_AULAS]{}, arr_cant_ses_fuera[MAX_AULAS]{}, n_aulas=0;
    bool arr_ses_fuera[MAX_AULAS]{};
    double arr_prom_alumnos[MAX_AULAS]{}, arr_ocupacion[MAX_AULAS]{};
    char arr_aulas_char[MAX_AULAS]{};


    cargar_disponibilidad("ArchivosDeDatos/disponibilidad.txt",
                           arr_dia_semana,
                           arr_hora_inicio,
                           arr_hora_final,
                           n_dispo);
    cargar_sesiones("ArchivosDeDatos/Sesiones.txt",
                    arr_dia_semana,
                    arr_hora_inicio,
                    arr_hora_final,
                    n_dispo,
                    arr_aulas_int,
                    arr_cant_sesiones,
                    arr_dia_temprano,
                    arr_dia_tarde,
                    arr_hora_temprano,
                    arr_hora_tarde,
                    arr_cant_ses_fuera,
                    arr_ses_fuera,
                    arr_prom_alumnos,
                    arr_ocupacion,
                    arr_aulas_char,
                    n_aulas);
    imprimir_reporte("ArchivosDeReporte/Reporte.txt",
                     arr_aulas_int,
                     arr_cant_sesiones,
                     arr_dia_temprano,
                     arr_dia_tarde,
                     arr_hora_temprano,
                     arr_hora_tarde,
                     arr_cant_ses_fuera,
                     arr_ses_fuera,
                     arr_prom_alumnos,
                     arr_ocupacion,
                     arr_aulas_char,
                     n_aulas);

    eliminar_aulas(arr_aulas_int,
                     arr_cant_sesiones,
                     arr_dia_temprano,
                     arr_dia_tarde,
                     arr_hora_temprano,
                     arr_hora_tarde,
                     arr_cant_ses_fuera,
                     arr_ses_fuera,
                     arr_prom_alumnos,
                     arr_ocupacion,
                     arr_aulas_char,
                     n_aulas);

    imprimir_reporte("ArchivosDeReporte/ReporteOcupacionMayor35PC.txt",
                     arr_aulas_int,
                     arr_cant_sesiones,
                     arr_dia_temprano,
                     arr_dia_tarde,
                     arr_hora_temprano,
                     arr_hora_tarde,
                     arr_cant_ses_fuera,
                     arr_ses_fuera,
                     arr_prom_alumnos,
                     arr_ocupacion,
                     arr_aulas_char,
                     n_aulas);

    return 0;
}
