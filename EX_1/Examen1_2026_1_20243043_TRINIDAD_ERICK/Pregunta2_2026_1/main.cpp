//Nombre: Erick Miguel Trinidad Yanac Codigo: 20244043
//el programa emplea arreglos en los cuales guardamos los medicos presentes en la clinica,
//con sus respectivas informaciones, imprime asi su especialdiad, tarifa por hora,
//cantidad de atenciones realizadas, tiempo promedio por atencion, tiempo total de las atenciones realizadas,
//y el pago recibido por todas las atenciones.
//Como resumen el programa imprime la cantidad de medicos y el pago total recibido.

#include "Bibliotecas/Funciones.hpp"


int main() {
    int cods_medicos[MAX_MEDICOS]{}, espe_medico[MAX_MEDICOS]{}, cants_atenciones[MAX_MEDICOS]{};
    int proms_atenciones[MAX_MEDICOS]{}, tiempos_atenciones[MAX_MEDICOS]{}, n_medicos=0;
    double tarifas_medicos[MAX_MEDICOS]{}, pagos_recibido[MAX_MEDICOS]{};

    cargar_atenciones("ArchivosDeDatos/Atenciones_TP_Ex1.txt",
                      cods_medicos,
                      cants_atenciones,
                      tiempos_atenciones,
                      n_medicos);
    probar_carga_atenciones("ArchivosDeReporte/prueba_carga_atenciones.txt",
                  cods_medicos,
                  cants_atenciones,
                  tiempos_atenciones,
                  n_medicos);
    cargar_especialidades("ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt",
                           cods_medicos,
                           n_medicos,
                           espe_medico,
                           tarifas_medicos);
    cargar_proms_pagos(n_medicos,
                       proms_atenciones,
                       pagos_recibido,
                       tarifas_medicos,
                       cants_atenciones,
                       tiempos_atenciones);
    imprimir_reporte("ArchivosDeReporte/Reporte_Atenciones_Medicos.txt",
                     true,
                     cods_medicos,
                     cants_atenciones,
                     tiempos_atenciones,
                     espe_medico,
                     tarifas_medicos,
                     proms_atenciones,
                     pagos_recibido,
                     n_medicos);

    eliminar_med(cods_medicos,
                 cants_atenciones,
                 tiempos_atenciones,
                 espe_medico,
                 tarifas_medicos,
                 proms_atenciones,
                 pagos_recibido,
                 n_medicos);
    imprimir_reporte("ArchivosDeReporte/Reporte_Atenciones_Medicos_MejorPagados.txt",
                     false,
                     cods_medicos,
                     cants_atenciones,
                     tiempos_atenciones,
                     espe_medico,
                     tarifas_medicos,
                     proms_atenciones,
                     pagos_recibido,
                     n_medicos);

    return 0;
}
