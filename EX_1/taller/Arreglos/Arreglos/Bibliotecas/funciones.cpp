#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//
// Created by svarg on 14/5/2026.
//

#include "funciones.h"

#define NO_ENCONTRADO -1
#define MINUTOS_MAXIMOS_SEMANA 5400
#define TAM_LINEA 140

void cargarDisponibilidad(int *arrDiasDis,int *arrDiasIni,int *arrDiasFin,int &cantDias){
    ifstream arch("ArchivosDeDatos/disponibilidad.txt",ios::in);
    if (not arch.is_open()) {
        cout<<"Error: el archivo ArchivosDeDatos/disponibilidad.txt no se pudo imprimir"<<endl;
        exit(1);
    }
    int d,hI,mI,hF,mF;
    char c;
    cantDias=0;
    while (true) {
        arch >> d;
        if (arch.eof()) break;
        arch>>hI>>c>>mI>>hF>>c>>mF;
        arrDiasDis[cantDias]=d;
        arrDiasIni[cantDias]=transformarMin(hI,mI);
        arrDiasFin[cantDias]=transformarMin(hF,mF);
        cantDias++;
    }
}

void cargarAulas(int *arrDiasDis,int *arrDiasIni,int *arrDiasFin,int cantDias,
    char *arrLetrAula,int *arrNumAula,double *arrOcupacionAula,
    int *arrSesionesAcum,double *arrPromAlumno,
    int *arrDiaTemp,int *arrHorTemp,int *arrDiaTard,int *arrHorTard,bool *arrFueraDisp,
    int *arrSesFDisp,int &cantAulas){
    ifstream arch("ArchivosDeDatos/sesiones.txt",ios::in);
    if (not arch.is_open()) {
        cout<<"Error: el archivo ArchivosDeDatos/sesiones.txt no se pudo imprimir"<<endl;
        exit(1);
    }
    char carAula,c;
    int idAula,aula,curso,horario,alu,prof,ses,hI,mI,hF,mF,dur,inicio,fin;
    cantAulas=0;
    while (true) {
        arch>>curso;
        if (arch.eof()) break;
        arch>>horario>>alu>>prof;
        while (true) {
            arch>>ses>>hI>>c>>mI>>hF>>c>>mF>>carAula>>aula;
            idAula=buscarAula(carAula,aula,arrLetrAula,arrNumAula,cantAulas);
            if (idAula==NO_ENCONTRADO) {
                arrLetrAula[cantAulas]=carAula;
                arrNumAula[cantAulas]=aula;
                idAula=cantAulas;
                cantAulas++;
            }
            inicio=transformarMin(hI,mI);
            fin=transformarMin(hF,mF);
            dur=fin-inicio;
            if (arrSesionesAcum[idAula]==0 or inicio<arrHorTemp[idAula]) {
                arrDiaTemp[idAula]=ses;
                arrHorTemp[idAula]=inicio;
            }
            if (arrSesionesAcum[idAula]==0 or fin>arrHorTard[idAula]) {
                arrDiaTard[idAula]=ses;
                arrHorTard[idAula]=fin;
            }
            arrOcupacionAula[idAula]+=dur;
            arrSesionesAcum[idAula]++;
            arrPromAlumno[idAula]+=alu;
            if (validarSinDisponibilidad(ses,inicio,fin,arrDiasDis,arrDiasIni,
                arrDiasFin,cantDias)) {
                arrFueraDisp[idAula]=true;
                arrSesFDisp[idAula]++;
            }
            if (arch.get()=='\n') break;
        }
    }
    actualizarCalculos(arrPromAlumno,arrSesionesAcum,arrOcupacionAula,cantAulas);
}

int buscarAula(char carAula,int aula,char *arrLetrAula,int *arrNumAula,
    int cantAulas){
    for (int i=0;i<cantAulas;i++)
        if (arrLetrAula[i]==carAula and arrNumAula[i]==aula) return i;
    return NO_ENCONTRADO;
}

int transformarMin(int h,int m){
    return h*60+m;
}

bool validarSinDisponibilidad(int ses,int inicio,int fin,int *arrDiasDis,int *arrDiasIni,
                int *arrDiasFin,int cantDias){
    int idDia=buscarDia(ses,arrDiasDis,cantDias);
    if (idDia==NO_ENCONTRADO)
        return false;
    else
        if (inicio>=arrDiasIni[idDia] and fin<=arrDiasFin[idDia])
            return false;
        else
            return true;
}

int buscarDia(int ses,int *arrDiasDis,int cantDias){
    for (int i=0;i<cantDias;i++)
        if (ses==arrDiasDis[i]) return i;
    return NO_ENCONTRADO;
}

void actualizarCalculos(double *arrPromAlumno,int *arrSesionesAcum,
    double *arrOcupacionAula,int cantAulas){
    for (int i=0;i<cantAulas;i++) {
        arrPromAlumno[i]/=arrSesionesAcum[i];
        arrOcupacionAula[i]/=MINUTOS_MAXIMOS_SEMANA;
        arrOcupacionAula[i]*=100;
    }
}

void mostrarAulas(const char *nombArch,char *arrLetrAula,int *arrNumAula,double *arrOcupacionAula,
    int *arrSesionesAcum,double *arrPromAlumno,int *arrDiaTemp,int *arrHorTemp,
    int *arrDiaTard,int *arrHorTard,bool *arrFueraDisp,int *arrSesFDisp,int cantAulas){
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error: el archivo "<<nombArch<<" no se pudo abrir"<<endl;
        exit(1);
    }
    int totSesiones=0,cantSesFD=0;
    bool sesFD=false;
    arch<<fixed<<setprecision(2);
    arch<<setw(80)<<"DETALLE DE OCUPACION DE AULAS"<<endl;
    imprimirSimbolo(arch,'=',TAM_LINEA);
    arch<<setw(10)<<"AULA"<<setw(17)<<"CANT.SESIONES"<<setw(20)<<"PROM.ALUM.SESION"
        <<setw(12)<<"%OCUPACION"<<setw(16)<<"SES.INI.TEMP"<<setw(20)<<"SES.TER.TARD"
        <<setw(20)<<"SES.FUERA.DISP."<<setw(22)<<"CANT.SES.FUERA.DISP"<<endl;
    imprimirSimbolo(arch,'-',TAM_LINEA);
    for (int i=0;i<cantAulas;i++) {
        arch<<setw(3)<<i+1<<") "<<setw(3)<<arrLetrAula[i]<<arrNumAula[i]
            <<setw(11)<<arrSesionesAcum[i]<<setw(20)<<arrPromAlumno[i]
            <<setw(14)<<arrOcupacionAula[i]<<" % ";
        imprimirDia(arrDiaTemp[i],arch);
        arch<<setw(3)<<' ';
        imprimirHora(arrHorTemp[i],arch);
        imprimirDia(arrDiaTard[i],arch);
        imprimirHora(arrHorTard[i],arch);
        if (arrFueraDisp[i]) {
            arch<<setw(8)<<' '<<"Si "<<setw(15)<<arrSesFDisp[i]<<endl;
            sesFD=true;
            cantSesFD+=arrSesFDisp[i];
        }
        else
            arch<<setw(8)<<' '<<"No"<<endl;
        totSesiones+=arrSesionesAcum[i];
    }
    imprimirSimbolo(arch,'=',TAM_LINEA);
    arch<<"TOTAL SESIONES: "<<setw(5)<<totSesiones<<endl;
    arch<<"HAY SESIONES QUE SE DICTAN FUERA DE LA DISPONIBILIDAD: ";
    if (sesFD)
        arch<<" SI - "<<setw(5)<<cantSesFD<<endl;
    else
        arch<<" NO"<<endl;
}

void imprimirDia(int ses,ofstream &arch){
    arch<<setw(2)<<' ';
    if (ses==2)
        arch<<"Lunes    ";
    else
        if (ses==3)
            arch<<"Martes   ";
        else
            if (ses==4)
                arch<<"Miercoles";
            else
                if (ses==5)
                    arch<<"Jueves   ";
                else
                    if (ses==6)
                        arch<<"Viernes  ";
                    else
                        if (ses==7)
                            arch<<"Sabado   ";
                        else
                            arch<<"Domingo ";

}

void imprimirHora(int dur,ofstream &arch){
    int h,m;
    h=dur/60;
    m=dur%60;
    arch<<setw(2)<<' '<<setfill('0')<<setw(2)<<h<<':'<<setw(2)<<m<<setfill(' ');
}

void eliminarAulas35PC(char *arrLetrAula,int *arrNumAula,
    double *arrOcupacionAula,int *arrSesionesAcum,double *arrPromAlumno,
    int *arrDiaTemp,int *arrHorTemp,int *arrDiaTard,int *arrHorTard,bool *arrFueraDisp,
    int *arrSesFDisp,int &cantAulas){
    int i=0;
    while (true) {
        if (arrOcupacionAula[i]<=35) {
            for (int j=i;j<cantAulas-1;j++) {
                arrLetrAula[j]=arrLetrAula[j+1];
                arrNumAula[j]=arrNumAula[j+1];
                arrOcupacionAula[j]=arrOcupacionAula[j+1];
                arrSesionesAcum[j]=arrSesionesAcum[j+1];
                arrPromAlumno[j]=arrPromAlumno[j+1];
                arrDiaTemp[j]=arrDiaTemp[j+1];
                arrHorTemp[j]=arrHorTemp[j+1];
                arrDiaTard[j]=arrDiaTard[j+1];
                arrHorTard[j]=arrHorTard[j+1];
                arrFueraDisp[j]=arrFueraDisp[j+1];
                arrSesFDisp[j]=arrSesFDisp[j+1];
            }
            cantAulas--;
        }
        else
            i++;
        if (i==cantAulas) break;
    }
}

void imprimirSimbolo(ofstream &archReporte,char simb,int cant){
    archReporte<<setfill(simb)<<setw(cant)<<simb<<setfill(' ')<<endl;
}