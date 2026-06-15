#include "Funciones.hpp"


void eliminar_aulas(int * arr_aulas_int, int * arr_cant_sesiones, int * arr_dia_temprano, int * arr_dia_tarde,
                    int * arr_hora_temprano, int * arr_hora_tarde, int * arr_cant_ses_fuera, bool * arr_ses_fuera,
                    double * arr_prom_alumnos, double * arr_ocupacion, char *arr_aulas_char, int &n_aulas) {

    for (int i = 0; i < n_aulas; i++) {
        if (arr_ocupacion[i]<=35.0) {
            for (int j = i; j < n_aulas; j++) {
                arr_aulas_int[j] = arr_aulas_int[j+1];
                arr_cant_sesiones[j] = arr_cant_sesiones[j+1];
                arr_dia_temprano[j] = arr_dia_temprano[j+1];
                arr_dia_tarde[j] = arr_dia_tarde[j+1];
                arr_hora_temprano[j] = arr_hora_temprano[j+1];
                arr_hora_tarde[j] = arr_hora_tarde[j+1];
                arr_cant_ses_fuera[j] = arr_cant_ses_fuera[j+1];
                arr_ses_fuera[j] = arr_ses_fuera[j+1];
                arr_prom_alumnos[j] = arr_prom_alumnos[j+1];
                arr_ocupacion[j] = arr_ocupacion[j+1];
                arr_aulas_char[j] = arr_aulas_char[j+1];
            }
            n_aulas--;
            i--;
        }
    }
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name);
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

void imprimir_encabezado( ofstream &output) {
    output<<setw(11)<<"AULA";
    output<<setw(17)<<"CANT.SESIONES";
    output<<setw(22)<<"PROM.ALUM.SESION";
    output<<setw(16)<<"%OCUPACION";
    output<<setw(20)<<"SES.INI.TEMP";
    output<<setw(23)<<"SES.TER.TARD";
    output<<setw(23)<<"SES.FUERA.DISP.";
    output<<setw(24)<<"CANT.SES.FUERA.DISP";
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void imprimir_nombre_dia(int i, ofstream & output) {
    output<<left<<setw(12);
    if (i==2) output<<"Lunes";
    if (i==3) output<<"Martes";
    if (i==4) output<<"Miercoles";
    if (i==5) output<<"Jueves";
    if (i==6) output<<"Viernes";
    if (i==7) output<<"Sabado";
    output<<right;
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora,minuto;
    hora=tiempo/60;
    minuto=tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<setfill(' ');
}

void imprimir_resumen(int total_sesiones, int total_ses_fuera, ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<"TOTAL SESIONES:  "<<total_sesiones<<endl;
    output<<"HAY SESIONES QUE SE DICTAN FUERA DE LA DISPONIBILIDAD: ";
    if (total_ses_fuera>0) output<<"SI - ";
    else output<<"NO - ";
    output<<total_ses_fuera<<" Sesiones";
}

void imprimir_reporte(const char *file_name, int * arr_aulas_int, int * arr_cant_sesiones, int * arr_dia_temprano,
                      int * arr_dia_tarde, int * arr_hora_temprano, int * arr_hora_tarde, int * arr_cant_ses_fuera,
                      bool * arr_ses_fuera, double * arr_prom_alumnos, double * arr_ocupacion, char * arr_aulas_char, int n_aulas) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    imprimir_titulo(output);
    imprimir_encabezado(output);
    output<<fixed;
    output.precision(2);
    int total_sesiones=0, total_ses_fuera=0;
    for (int i = 0; i < n_aulas; i++) {
        output<<setw(2)<<i+1<<")"<<setw(5)<<arr_aulas_char[i]<<arr_aulas_int[i];
        output<<setw(12)<<arr_cant_sesiones[i];
        output<<setw(20)<<arr_prom_alumnos[i];
        output<<setw(18)<<arr_ocupacion[i]<<left<<setw(10)<<" %"<<right;
        imprimir_nombre_dia(arr_dia_temprano[i], output);
        imprimir_tiempo(arr_hora_temprano[i], output);
        output<<setw(6)<<"";
        imprimir_nombre_dia(arr_dia_tarde[i], output);
        imprimir_tiempo(arr_hora_tarde[i], output);
        if (arr_ses_fuera[i]) output<<setw(14)<<"Si";
        else output<<setw(14)<<"No";
        output<<setw(22)<<arr_cant_ses_fuera[i];
        output<<endl;
        total_sesiones+=arr_cant_sesiones[i];
        total_ses_fuera+=arr_cant_ses_fuera[i];
    }
    imprimir_resumen(total_sesiones,total_ses_fuera,output);
}

void ignorar( ifstream & input, char del) {
    char c;
    input>>ws;
    while (true) {
        input.get(c);
        if (c == del) break;
    }
}

int buscar_aula(char aula_char, int aula_int, char * arr_aulas_char, int * arr_aulas_int, int n_aulas) {
    for (int i = 0; i < n_aulas; i++) {
        if (arr_aulas_char[i] == aula_char and arr_aulas_int[i]==aula_int) return  i;
    }
    return NO_ENCONTRADO;
}


int buscar_dia(int dia, int * arr_dia_semana, int n_dispo) {
    for (int i = 0; i < n_dispo; i++) {
        if (arr_dia_semana[i]==dia) return  i;
    }
    return NO_ENCONTRADO;
}

void agregar_sin_repeticion(char aula_char, int aula_int,int n_alumnos, int hora_inicio, int hora_fin, int dia, int * arr_dia_semana,
                            int * arr_hora_inicio, int * arr_hora_final, int n_dispo, int * arr_aulas_int, int * arr_cant_sesiones,
                            int * arr_dia_temprano, int * arr_dia_tarde, int * arr_hora_temprano, int * arr_hora_tarde,
                            int * arr_cant_ses_fuera, bool * arr_ses_fuera, double * arr_prom_alumnos, double * arr_ocupacion,
                            char * arr_aulas_char, int &n_aulas) {
    int pos_aula,pos_dia, n;
    pos_aula = buscar_aula(aula_char,aula_int, arr_aulas_char, arr_aulas_int, n_aulas);
    if (pos_aula==NO_ENCONTRADO) {
        arr_aulas_int[n_aulas]=aula_int;
        arr_aulas_char[n_aulas]=aula_char;
        arr_ses_fuera[n_aulas]=false;
        n=n_aulas;
        n_aulas++;
    } else {
        n=pos_aula;
    }
    arr_cant_sesiones[n]++;
    arr_prom_alumnos[n]+=n_alumnos;
    arr_ocupacion[n]+=hora_fin-hora_inicio;
    if (arr_hora_temprano[n]==0 or hora_inicio<arr_hora_temprano[n]) {
        arr_hora_temprano[n]=hora_inicio;
        arr_dia_temprano[n]=dia;
    }
    if (arr_hora_tarde[n]==0 or hora_fin>arr_hora_tarde[n]) {
        arr_hora_tarde[n]=hora_fin;
        arr_dia_tarde[n]=dia;
    }
    pos_dia=buscar_dia(dia,arr_dia_semana, n_dispo);
    if (pos_dia!=NO_ENCONTRADO and hora_fin>arr_hora_final[pos_dia] or hora_inicio<arr_hora_inicio[pos_dia]) {
        arr_ses_fuera[n]=true;
        arr_cant_ses_fuera[n]++;
    }
}

void actualizar_prom_ocupaciones(double * arr_prom_alumnos, double * arr_ocupacion, int * arr_cant_sesiones, int n_aulas) {
    for (int i = 0; i < n_aulas; i++) {
        if (arr_cant_sesiones[i]!=0) {
            arr_prom_alumnos[i]/=arr_cant_sesiones[i];
            arr_ocupacion[i]=arr_ocupacion[i]*100/(15*6*60);
        }
    }
}

void cargar_sesiones(const char *file_name, int *arr_dia_semana, int * arr_hora_inicio, int * arr_hora_final, int n_dispo,
                     int * arr_aulas_int, int * arr_cant_sesiones, int * arr_dia_temprano, int * arr_dia_tarde,
                     int * arr_hora_temprano, int * arr_hora_tarde, int * arr_cant_ses_fuera, bool * arr_ses_fuera,
                     double * arr_prom_alumnos, double * arr_ocupacion, char *arr_aulas_char, int &n_aulas) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int cod_curso,dia,hora,minuto,hora_inicio,hora_fin,aula_int,n_alumnos;
    char c,aula_char;
    while (true) {
        input>>cod_curso;
        if (input.eof()) break;
        ignorar(input, ' ');
        input>>n_alumnos;
        ignorar(input, ' ');
        while (true) {
            input>>dia>>hora>>c>>minuto;
            hora_inicio = hora*60+minuto;
            input>>hora>>c>>minuto;
            hora_fin = hora*60+minuto;
            input>>ws>>aula_char>>aula_int;
            agregar_sin_repeticion(aula_char,aula_int,n_alumnos,hora_inicio,hora_fin,dia,arr_dia_semana, arr_hora_inicio, arr_hora_final,
                                   n_dispo, arr_aulas_int, arr_cant_sesiones, arr_dia_temprano, arr_dia_tarde, arr_hora_temprano,
                                   arr_hora_tarde, arr_cant_ses_fuera, arr_ses_fuera, arr_prom_alumnos, arr_ocupacion,
                                   arr_aulas_char, n_aulas);
            input.get(c);
            if (c=='\n') break;
        }
    }
    actualizar_prom_ocupaciones(arr_prom_alumnos,arr_ocupacion,arr_cant_sesiones,n_aulas);
}

void abrir_archivo_lectura(const char * file_name, ifstream  &input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura" <<file_name<< endl;
        exit(1);
    }
}

void cargar_disponibilidad(const char *file_name, int *arr_dia_semana, int *arr_hora_inicio, int *arr_hora_final, int &n_dispo) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dia, hora, minuto;
    char c;
    while (true) {
        input>>dia;
        if (input.eof()) break;
        arr_dia_semana[n_dispo] = dia;
        input>>hora>>c>>minuto;
        arr_hora_inicio[n_dispo] = hora*60+minuto;
        input>>hora>>c>>minuto;
        arr_hora_final[n_dispo] = hora*60+minuto;
        n_dispo++;
    }
}
