//
// Created by svarg on 14/5/2026.
//

#ifndef ARREGLOS_FUNCIONES_H
#define ARREGLOS_FUNCIONES_H
void cargarDisponibilidad(int *arrDiasDis,int *arrDiasIni,int *arrDiasFin,int &cantDias);

void cargarAulas(int *arrDiasDis,int *arrDiasIni,int *arrDiasFin,int cantDias,
    char *arrLetrAula,int *arrNumAula,double *arrOcupacionAula,
    int *arrSesionesAcum,double *arrPromAlumno,
    int *arrDiaTemp,int *arrHorTemp,int *arrDiaTard,int *arrHorTard,bool *arrFueraDisp,
    int *arrSesFDisp,int &cantAulas);
int buscarAula(char carAula,int aula,char *arrLetrAula,int *arrNumAula,int cantAulas);
int transformarMin(int h,int m);
bool validarSinDisponibilidad(int ses,int inicio,int fin,int *arrDiasDis,int *arrDiasIni,
                int *arrDiasFin,int cantDias);
int buscarDia(int ses,int *arrDiasDis,int cantDias);
void actualizarCalculos(double *arrPromAlumno,int *arrSesionesAcum,
    double *arrOcupacionAula,int cantAulas);
void mostrarAulas(const char *nombArch,char *arrLetrAula,int *arrNumAula,double *arrOcupacionAula,
    int *arrSesionesAcum,double *arrPromAlumno,int *arrDiaTemp,int *arrHorTemp,
    int *arrDiaTard,int *arrHorTard,bool *arrFueraDisp,int *arrSesFDisp,int cantAulas);
void imprimirDia(int ses,ofstream &arch);
void imprimirHora(int dur,ofstream &arch);
void ordenarAulas(char *arrLetrAula,int *arrNumAula,double *arrOcupacionAula,
    int *arrSesionesAcum,double *arrPromAlumno,int *arrDiaTemp,int *arrHorTemp,
    int *arrDiaTard,int *arrHorTard,int cantAulas);
void cambiarChar(char &datoI,char &datoJ);
void cambiarInt(int &datoI,int &datoJ);
void cambiarDouble(double &datoI,double &datoJ);
void eliminarAulas35PC(char *arrLetrAula,int *arrNumAula,
    double *arrOcupacionAula,int *arrSesionesAcum,double *arrPromAlumno,
    int *arrDiaTemp,int *arrHorTemp,int *arrDiaTard,int *arrHorTard,bool *arrFueraDisp,
    int *arrSesFDisp,int &cantAulas);
void imprimirSimbolo(ofstream &archReporte,char simb,int cant);
#endif //ARREGLOS_FUNCIONES_H