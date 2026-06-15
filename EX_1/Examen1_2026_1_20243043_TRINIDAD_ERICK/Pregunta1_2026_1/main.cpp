
//Nombre: Erick Miguel Trinidad Yanac Codigo: 20244043
//El programa en base a cada sede, vamos a buscar e imprimir las atenciones realizadas segun la fecha, el paciente revisado,
//la duracion de la consulta, el medico encargado con su especialidad y costo de atencion por hora.
//calculando asi el pago de la atencion
//por cada sede imprimimos el total de atenciones, el total pago en la sede y el tiempo total que duraron las atenciones
//como resumen final tenemos la cantidad de sedes, pago total recibido de todas las cedes e identificamos la sede con el mayor pago.

#include "Bibliotecas/Funciones.hpp"

int main() {

    imprimir_reporte("ArchivosDeDatos/Sedes_TP_Ex1.txt",
                     "ArchivosDeDatos/Pacientes_TP_Ex1.txt",
                     "ArchivosDeDatos/Especialidades_Medicos_TP_Ex1.txt",
                     "ArchivosDeDatos/Atenciones_TP_Ex1.txt",
                     "ArchivosDeReporte/Reporte.txt");

    return 0;
}
