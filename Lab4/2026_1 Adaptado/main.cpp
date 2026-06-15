#include "Bibliotecas/Funciones.hpp"


int main() {
    //Pacientes
    int ID_pacientes[MAX_PACIENTES]{}, edad_pacientes[MAX_PACIENTES]{};
    char sexo_pacientes[MAX_PACIENTES]{};
    int n_pacientes = 0;
    //Triaje
    int fechas_atenciones[MAX_TRIAJE]{}, ID_triaje[MAX_TRIAJE]{}, frecuencia_cardiaca[MAX_TRIAJE]{};
    int sistolica[MAX_TRIAJE]{}, diastolica[MAX_TRIAJE]{}, saturacion_oxigeno[MAX_TRIAJE]{};
    double  temperatura[MAX_TRIAJE]{};
    int n_triaje = 0;

    cargar_pacientes("ArchivosDeDatos/Pacientes_TP_L3.txt",
                     ID_pacientes,
                     edad_pacientes,
                     sexo_pacientes,
                     n_pacientes);
    probar_carga_pacientes("ArchivosDeReporte/prueba_carga_pacientes.txt",
                           ID_pacientes,
                           edad_pacientes,
                           sexo_pacientes,
                           n_pacientes);

    carga_triaje("ArchivosDeDatos/Triaje_TP_L3.txt",
                 fechas_atenciones,
                 ID_triaje,
                 frecuencia_cardiaca,
                 sistolica,
                 diastolica,
                 temperatura,
                 saturacion_oxigeno,
                 n_triaje);
    probar_carga_triaje("ArchivosDeReporte/prueba_carga_triaje.txt",
                        fechas_atenciones,
                        ID_triaje,
                        frecuencia_cardiaca,
                        sistolica,
                        diastolica,
                        temperatura,
                        saturacion_oxigeno,
                        n_triaje);

    generar_reporte("ArchivosDeDatos/ClinicaDeUrgencias_TP_L3.txt",
                    "ArchivosDeReporte/Reporte_Final.txt",
                    ID_pacientes,
                    edad_pacientes,
                    sexo_pacientes,
                    n_pacientes,
                    fechas_atenciones,
                    ID_triaje,
                    frecuencia_cardiaca,
                    sistolica,
                    diastolica,
                    temperatura,
                    saturacion_oxigeno, n_triaje);

    return 0;
}
