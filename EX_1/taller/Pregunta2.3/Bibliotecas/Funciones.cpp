//
// Created by User on 18/05/2026.
//

#include "Funciones.hpp"
void abrir_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura" << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    output<<endl;
}

void imprimir_titulo( ofstream & output) {
    output<<setw((ANCHO_REPORTE+29)/2)<<"DETALLE DE OCUPACION DE AULAS"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_encabezado( ofstream & output) {
    output<<setw(10)<<"AULA"<<setw(17)<<"CANT.SESIONES"<<setw(22)<<"PROM.ALUM.SESION"<<setw(14)<<"%OCUPACION";
    output<<setw(20)<<"SES.INI.TEMP"<<setw(20)<<"SES.TER.TARD"<<setw(23)<<"SES.FUERA.DIPS."<<setw(23)<<"CANT.SES.FUERA.DISP";
    output<<endl;
}

void imprimir_dia(int dia, ofstream & output) {
    output<<left<<setw(16);
    if (dia == 2) output<<"Lunes";
    if (dia == 3) output<<"Martes";
    if (dia == 4) output<<"Miercoles";
    if (dia == 5) output<<"Jueves";
    if (dia == 6) output<<"Viernes";
    if (dia == 7) output<<"Sabado";
    output<<right;
}

void imprimir_hora(int tiempo, ofstream & output) {
    int hora, minuto;
    hora=tiempo/60;
    minuto=tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<setfill(' ');
}

void imprimir_reporte(const char *file_name, int *aulas_int, int * cants_sesiones_aulas, int * ses_temprano_horas, int * ses_tardes_horas, int * cant_ses_fueras,
                      char * aulas_char, int * ses_temprano_dia, int * ses_tardes_dia, double * proms_alums, double * ocupacion_aulas, bool * existen_ses_fueras,
                      int n_aulas) {
    ofstream output;
    abrir_escritura(file_name, output);
    output<<fixed;
    output.precision(2);
    imprimir_titulo(output);
    imprimir_encabezado(output);
    int total_sesiones = 0, total_ses_fuera=0;
    for (int i = 0; i < n_aulas; i++) {
        output<<setw(2)<<i+1<<left<<setw(4)<<")"<<right;
        output<<aulas_char[i]<<aulas_int[i];
        output<<setw(12)<<cants_sesiones_aulas[i];
        output<<setw(28)<<proms_alums[i];
        output<<setw(16)<<ocupacion_aulas[i]<<left<<setw(10)<<" %"<<right;
        imprimir_dia(ses_temprano_dia[i], output);
        imprimir_hora(ses_temprano_horas[i], output);
        output<<setw(6)<<"";
        imprimir_dia(ses_tardes_dia[i], output);
        imprimir_hora(ses_tardes_horas[i], output);
        if (existen_ses_fueras[i]) {
            output<<setw(10)<<"Si"<<setw(30)<<cant_ses_fueras[i];
            total_ses_fuera+=cant_ses_fueras[i];
        }
        else output<<setw(10)<<"No"<<setw(30)<<cant_ses_fueras[i];
        output<<endl;
    }
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<"TOTAL SESIONES:  "<<total_sesiones<<endl;
    output<<"HAY SESIONES QUE SE DICTAN FUERA DE LA DISPONIBILIDAD: ";
    if (total_ses_fuera>0) output<<"SI - "<<total_ses_fuera<<" Sesiones"<<endl;
    else output<<"No"<<endl;
}

void ignorar(char del, ifstream & input) {
    char c;
    input>>ws;
    while (true) {
        input.get(c);
        if (c==del) break;
    }
}

int buscar_aula(char aula_char, int aula_int, int * aulas_int, char * aulas_char, int n_aulas) {
    for (int i = 0; i < n_aulas; i++) {
        if (aulas_char[i]==aula_char and aulas_int[i]==aula_int) return i;
    }
    return NO_ENCONTRADO;
}

void insertar_ordenado_sin_repeticion(char aula_char, int aula_int, int * aulas_int, char * aulas_char, bool * existen_ses_fueras,
                                      int &pos_aula, int &n_aulas) {
    pos_aula=buscar_aula(aula_char,aula_int, aulas_int, aulas_char, n_aulas);
    if (pos_aula==NO_ENCONTRADO) {
        int i=n_aulas-1;
        while (i>=0 and aulas_char[i]>aula_char or aulas_char[i]==aula_char
               and aulas_int[i]>aula_int) {
            aulas_char[i+1]=aulas_char[i];
            aulas_int[i+1]=aulas_int[i];
            existen_ses_fueras[i+1]=existen_ses_fueras[i];
            i--;
               }
        aulas_char[i+1]=aula_char;
        aulas_int[i+1]=aula_int;
        existen_ses_fueras[i+1]=false;
        n_aulas++;
    }
}

int buscar_dispo(int * dia_semana, int n_dispo, int dia) {
    for (int i = 0; i < n_dispo; i++) {
        if (dia_semana[i]==dia) return i;
    }
    return NO_ENCONTRADO;
}

void actualizar_prom_ocupacion(double * proms_alums, double * ocupacion_aulas, int n_aulas, int * cants_sesiones_aulas) {
    for (int i = 0; i < n_aulas; i++) {
        if (cants_sesiones_aulas[i]!=0) {
            proms_alums[i]=proms_alums[i]/cants_sesiones_aulas[i];
            ocupacion_aulas[i]=ocupacion_aulas[i]/(15*60*6)*100;
        }
    }
}

void leer_sesiones_clases(ifstream & input, int * dia_semana, int * horas_inicio, int * horas_fin, int n_dispo, int * aulas_int,
                          int * cants_sesiones_aulas, int * ses_temprano_horas, int * ses_tardes_horas, int * cant_ses_fueras,
                          char * aulas_char, int *ses_temprano_dia, int *ses_tardes_dia, double * proms_alums,
                          double * ocupacion_aulas, bool * existen_ses_fueras, int &n_aulas, int n_alumnos) {
    int dia,hora,minuto,hora_inicio,hora_fin,aula_int, pos_aula, n, pos_dia;
    char aula_char,c;
    while (true) {
        input>>dia>>hora>>c>>minuto;
        hora_inicio=hora*60+minuto;
        input>>hora>>c>>minuto;
        hora_fin=hora*60+minuto;
        input>>ws>>aula_char>>aula_int;
        insertar_ordenado_sin_repeticion(aula_char,aula_int, aulas_int, aulas_char, existen_ses_fueras,pos_aula, n_aulas);
        if (pos_aula!=NO_ENCONTRADO) n=pos_aula;
        else n=buscar_aula(aula_char,aula_int, aulas_int, aulas_char, n_aulas);
        cants_sesiones_aulas[n]++;
        proms_alums[n]+=n_alumnos;
        ocupacion_aulas[n]+=(hora_fin-hora_inicio);
        if (ses_temprano_horas[n]==0 or ses_temprano_horas[n]>hora_inicio) {
            ses_temprano_horas[n]=hora_inicio;
            ses_temprano_dia[n]=dia;
        }
        if (ses_tardes_horas[n]==0 or ses_tardes_horas[n]<hora_fin) {
            ses_tardes_horas[n]=hora_fin;
            ses_tardes_dia[n]=dia;
        }
        pos_dia=buscar_dispo(dia_semana,n_dispo, dia);
        if (pos_dia!=NO_ENCONTRADO and hora_inicio<horas_inicio[pos_dia] and hora_fin>horas_fin[n]) {
            existen_ses_fueras[n]=true;
            cant_ses_fueras[n]++;
        }
        input.get(c);
        if (c=='\n') break;
    }
    actualizar_prom_ocupacion(proms_alums, ocupacion_aulas, n_aulas, cants_sesiones_aulas);
}

void cargar_aulas(const char *file_name, int * dia_semana, int * horas_inicio, int * horas_fin, int n_dispo, int * aulas_int,
                  int * cants_sesiones_aulas, int * ses_temprano_horas, int * ses_tardes_horas, int * cant_ses_fueras,
                  char * aulas_char, int *ses_temprano_dia, int *ses_tardes_dia, double * proms_alums, double * ocupacion_aulas,
                  bool * existen_ses_fueras, int &n_aulas) {
    ifstream input;
    abrir_lectura(file_name, input);

    int cod_curso, n_alumnos;
    while (true) {
        input>>cod_curso;
        if (input.eof()) break;
        ignorar(' ',input);
        input>>n_alumnos;
        ignorar(' ',input);
        leer_sesiones_clases(input, dia_semana, horas_inicio, horas_fin, n_dispo, aulas_int, cants_sesiones_aulas,
                             ses_temprano_horas,ses_tardes_horas,cant_ses_fueras,aulas_char, ses_temprano_dia,
                             ses_tardes_dia, proms_alums,ocupacion_aulas,existen_ses_fueras, n_aulas, n_alumnos);
    }
}

void abrir_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de lectura" << file_name<< endl;
        exit(1);
    }
}

void cargar_disponibilidad(const char *file_name, int * dia_semana, int * horas_inicio, int * horas_fin, int &n_dispo) {
    ifstream input;
    abrir_lectura(file_name, input);
    int dia,hora,minuto;
    char c;
    while (true) {
        input>>dia;
        if (input.eof()) break;
        input>>hora>>c>>minuto;
        horas_inicio[n_dispo] = hora*60+minuto;
        input>>hora>>c>>minuto;
        horas_fin[n_dispo] = hora*60+minuto;
        dia_semana[n_dispo] = dia;
        n_dispo++;
    }
}
