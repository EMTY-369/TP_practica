#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "Bibliotecas/funciones.h"

#define MAX_AULAS 50
#define MAX_DIAS 6

int main(){
    int arrDiasDis[MAX_DIAS],arrDiasIni[MAX_DIAS],arrDiasFin[MAX_DIAS],cantDias,
        arrNumAula[MAX_AULAS],arrSesionesAcum[MAX_AULAS]{},arrDiaTemp[MAX_AULAS]{},
        arrHorTemp[MAX_AULAS]{},arrDiaTard[MAX_AULAS]{},arrHorTard[MAX_AULAS]{},
        arrSesFDisp[MAX_AULAS]{},cantAulas;
    char arrLetrAula[MAX_AULAS];
    double arrPromAlumno[MAX_AULAS]{},arrOcupacionAula[MAX_AULAS]{};
    bool arrFueraDisp[MAX_AULAS]{};
    cargarDisponibilidad(arrDiasDis,arrDiasIni,arrDiasFin,cantDias);
    cargarAulas(arrDiasDis,arrDiasIni,arrDiasFin,cantDias,
        arrLetrAula,arrNumAula,arrOcupacionAula,arrSesionesAcum,arrPromAlumno,
        arrDiaTemp,arrHorTemp,arrDiaTard,arrHorTard,arrFueraDisp,arrSesFDisp,
        cantAulas);
    mostrarAulas("ArchivosDeReportes/reporteOcupacion.txt",arrLetrAula,
        arrNumAula,arrOcupacionAula,arrSesionesAcum,arrPromAlumno,
        arrDiaTemp,arrHorTemp,arrDiaTard,arrHorTard,arrFueraDisp,arrSesFDisp,cantAulas);
    eliminarAulas35PC(arrLetrAula,arrNumAula,arrOcupacionAula,arrSesionesAcum,
        arrPromAlumno,arrDiaTemp,arrHorTemp,arrDiaTard,arrHorTard,arrFueraDisp,
        arrSesFDisp,cantAulas);
    mostrarAulas("ArchivosDeReportes/reporteOcupacionMayor35PC.txt",arrLetrAula,
        arrNumAula,arrOcupacionAula,arrSesionesAcum,arrPromAlumno,
        arrDiaTemp,arrHorTemp,arrDiaTard,arrHorTard,arrFueraDisp,arrSesFDisp,cantAulas);
    return 0;
}