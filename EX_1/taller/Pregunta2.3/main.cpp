#include "Bibliotecas/Funciones.hpp"

int main() {
    int dia_semana[MAX_DISPO]{}, horas_inicio[MAX_DISPO]{}, horas_fin[MAX_DISPO]{}, n_dispo=0;
    int aulas_int[MAX_AULAS]{}, cants_sesiones_aulas[MAX_AULAS]{}, ses_temprano_horas[MAX_AULAS]{}, ses_tardes_horas[MAX_AULAS]{};
    int cant_ses_fueras[MAX_AULAS]{}, ses_temprano_dia[MAX_AULAS]{}, ses_tardes_dia[MAX_AULAS]{}, n_aulas=0;
    char aulas_char[MAX_AULAS]{};
    double proms_alums[MAX_AULAS]{}, ocupacion_aulas[MAX_AULAS]{};
    bool existen_ses_fueras[MAX_AULAS]{};
    cargar_disponibilidad("ArchivosDeDatos/disponibilidad.txt",
                          dia_semana,
                          horas_inicio,
                          horas_fin,
                          n_dispo);
    cargar_aulas("ArchivosDeDatos/Sesiones.txt",
                 dia_semana,
                 horas_inicio,
                 horas_fin,
                 n_dispo,
                 aulas_int,
                 cants_sesiones_aulas,
                 ses_temprano_horas,
                 ses_tardes_horas,
                 cant_ses_fueras,
                 aulas_char,
                 ses_temprano_dia,
                 ses_tardes_dia,
                 proms_alums,
                 ocupacion_aulas,
                 existen_ses_fueras,
                 n_aulas);

    imprimir_reporte("ArchivosDeReporte/Reporte2.txt",
                     aulas_int,
                     cants_sesiones_aulas,
                     ses_temprano_horas,
                     ses_tardes_horas,
                     cant_ses_fueras,
                     aulas_char,
                     ses_temprano_dia,
                     ses_tardes_dia,
                     proms_alums,
                     ocupacion_aulas,
                     existen_ses_fueras,
                     n_aulas);
    return 0;
}