

#include "Bibliotecas/Funciones.hpp"


int main() {
    ListaMedicosTAD lista_medicos;
    cargar_medicos("ArchivosDeDatos/Medicos_TP_Lab9.csv", lista_medicos);
    prueba_carga("ArchivosDeReporte/prueba_carga_medicos.txt", lista_medicos, false);
    cargar_atenciones("ArchivosDeDatos/Atenciones_TP_Lab9.csv", lista_medicos);
    prueba_carga("ArchivosDeReporte/pruena_carga_atenciones.txt", lista_medicos, true);
    

    return 0;
}
