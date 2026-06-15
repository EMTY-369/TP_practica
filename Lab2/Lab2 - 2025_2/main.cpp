#include "Bibliotecas/Funciones.hpp"

int main() {
    int fecha_inicio=20220910, fecha_final=20230101;
    double tarifa_reproduccion=2.57, tarifa_duracion=0.78;

    // cout << "Ingrese la fecha de inicio: ";
    // fecha_inicio = leer_fecha_consola();
    // cout << "Ingrese la fecha final: ";
    // fecha_final = leer_fecha_consola();
    // cout << "Ingrese tarifa por número de reproducciones y duración del stream (respectivamente): ";
    // cin >> tarifa_reproduccion >> tarifa_duracion;

    calcular_reporte(fecha_inicio,fecha_final,tarifa_reproduccion,tarifa_duracion, "ArchivosDeDatos/Lab2_twitchdataTP.txt", "ArchivosDeReporte/Reporte.txt");


    return 0;
}
