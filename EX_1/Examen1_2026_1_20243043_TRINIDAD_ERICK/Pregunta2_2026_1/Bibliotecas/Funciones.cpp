//
// Created by aml on 18/05/2026.
//

#include "Funciones.hpp"

void eliminar_med(int * cods_medicos, int * cants_atenciones, int * tiempos_atenciones, int * espe_medico,
                  double * tarifas_medicos, int * proms_atenciones, double * pagos_recibido, int &n_medicos) {
    for (int i = 0; i < n_medicos; i++) {
        if (pagos_recibido[i]<5000) {
            for (int j = i; j < n_medicos; j++) {
                cods_medicos[j]=cods_medicos[j+1];
                cants_atenciones[j]=cants_atenciones[j+1];
                tiempos_atenciones[j]=tiempos_atenciones[j+1];
                espe_medico[j]=espe_medico[j+1];
                tarifas_medicos[j]=tarifas_medicos[j+1];
                proms_atenciones[j]=proms_atenciones[j+1];
                pagos_recibido[j]=pagos_recibido[j+1];
            }
            n_medicos--;
            i--;
        }
    }
}

void imprimir_encabezado( ofstream & output) {
    output<<"MEDICO"<<setw(18)<<"ESPECIALIDAD"<<setw(12)<<"TARIFA"<<setw(22)<<"CANT. ATENCIONES";
    output<<setw(29)<<"TIEMPO.TOTAL.ATENCIONES"<<setw(26)<<"TIEMPO.PROM.ATENCION"<<setw(19)<<"PAGO_RECIBIDO";
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', output);
}

void espacios(int n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(' ');
}

void imprimir_resumen( ofstream & output, double pago_total, int n_medicos) {
    imprimir_linea(ANCHO_REPORTE, '-', output);
    output<<"RESUMEN: "<<endl;
    output<<"TOTAL DE MEDICOS:  "<<n_medicos<<endl;
    output<<"PAGO TOTAL RECIBIDO:  s/.    "<<pago_total<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', output);
}

void imprimir_reporte(const char *file_name, bool report1, int * cods_medicos, int * cants_atenciones,
                      int * tiempos_atenciones, int * espe_medico, double * tarifas_medicos, int * proms_atenciones,
                      double * pagos_recibido, int n_medicos) {
    ofstream output;
    abrir_escritura(file_name, output);
    output<<fixed;
    output.precision(2);
    imprimir_linea(ANCHO_REPORTE, '=', output);
    output<<setw((ANCHO_REPORTE+29)/2)<<"CLINICA DE URGENCIAS TP_SALUD"<<endl;
    if (report1) output<<setw((ANCHO_REPORTE+21)/2)<<"ATENCIONES POR MEDICO"<<endl;
    else output<<setw((ANCHO_REPORTE+21)/2)<<"ATENCIONES MEDICOS MEJOR PAGADOS"<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', output);
    imprimir_encabezado(output);
    double pago_total=0;
    for (int i = 0; i < n_medicos; i++) {
        output<<setw(5)<<cods_medicos[i]<<setw(17)<<espe_medico[i];
        output<<setw(16)<<tarifas_medicos[i]<<setw(16)<<cants_atenciones[i];
        espacios(20,output);
        imprimir_tiempo(tiempos_atenciones[i],output);
        espacios(20,output);
        imprimir_tiempo(proms_atenciones[i],output);
        output<<setw(20)<<pagos_recibido[i]<<endl;
        pago_total+=pagos_recibido[i];
    }
    imprimir_resumen(output, pago_total, n_medicos);
}


void cargar_proms_pagos(int n_medicos, int * proms_atenciones, double * pagos_recibido, double * tarifas_medicos,
                        int * cants_atenciones, int * tiempos_atenciones) {

    for (int i = 0; i < n_medicos; i++) {
        if (cants_atenciones[i]>0) {
            proms_atenciones[i]=tiempos_atenciones[i]/cants_atenciones[i];
            pagos_recibido[i]=tiempos_atenciones[i]*tarifas_medicos[i]/3600.0;
        }
    }
}

void cargar_especialidades(const char * file_name, int * cods_medicos, int n_medicos, int * espe_medico, double * tarifas_medicos) {
    ifstream input;
    abrir_lectura(file_name, input);

    int cod_espe, cod_medico_leido, pos_med;
    double tarifa;
    char c;
    while (true) {
        input>>cod_espe;
        if (input.eof()) break;
        ignorar(' ',input);
        while (true) {
            //9846    AMEZQUITA/EPIQUEN/EVERT_ROBERTO    418.17
            input>>cod_medico_leido;
            ignorar(' ',input);
            input>>tarifa;
            pos_med=buscar_med(cods_medicos,n_medicos,cod_medico_leido);
            if (pos_med!=NO_ENCONTRADO) {
                espe_medico[pos_med]=cod_espe;
                tarifas_medicos[pos_med]=tarifa;
            }
            input.get(c);
            if (c=='\n') break;
        }
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    output<<endl;
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora, minuto, segundo;
    hora = tiempo/3600;
    tiempo %= 3600;
    minuto = tiempo/60;
    segundo = tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

void probar_carga_atenciones(const char * file_name, int * cods_medicos, int * cants_atenciones, int * tiempos_atenciones, int n_medicos) {
    ofstream output;
    abrir_escritura(file_name, output);

    output<<setw((ANCHO_REPORTE+29)/2)<<"PRUEBA DE CARGA DE ATENCIONES"<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', output);
    output<<left<<setw(ANCHO_REPORTE/3)<<"CODIGOS MEDICOS";
    output<<setw(ANCHO_REPORTE/3)<<"CANTIDAD DE ATENCIONES";
    output<<setw(ANCHO_REPORTE/3)<<"TIEMPO TOTAL DE ATENCIONES"<<endl;
    for (int i=0; i<n_medicos; i++) {
        output<<left<<setw(ANCHO_REPORTE/3)<<cods_medicos[i];
        output<<setw(ANCHO_REPORTE/3)<<cants_atenciones[i]<<right;
        imprimir_tiempo(tiempos_atenciones[i],output);
        output<<endl;
    }
}

int leer_fecha( ifstream & input) {
    int dd,mm,aa;
    char c;
    input>>dd;
    if (input.eof()) return NO_ENCONTRADO;
    input>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void abrir_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada"<<file_name << endl;
        exit(1);
    }
}

void abrir_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"Error al abrir el archivo de salida"<<file_name << endl;
        exit(1);
    }
}

int leer_tiempo( ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void ignorar(char del, ifstream & input) {
    char c;
    input>>ws;
    while (true) {
        input.get(c);
        if (c==del) break;
    }
}

int buscar_med(int * cods_medicos, int n_medicos, int doc) {
    for (int i=0; i<n_medicos; i++) {
        if (cods_medicos[i]==doc) return i;
    }
    return NO_ENCONTRADO;
}

void cargar_atenciones(const char *file_name, int *cods_medicos, int * cants_atenciones, int * tiempos_atenciones, int &n_medicos) {
    ifstream input;
    abrir_lectura(file_name, input);

    int fecha, sede, doc, hora_entrada, hora_salida,pos_med;
    char c;
    //895    01:21:00    691-12-9990    03:13:54    4393
    while (true) {
        fecha=leer_fecha(input);
        if (fecha==NO_ENCONTRADO or input.eof()) break;
        while (true) {
            input>>sede;
            hora_entrada=leer_tiempo(input);
            ignorar(' ',input);
            hora_salida=leer_tiempo(input);
            input>>doc;
            pos_med=buscar_med(cods_medicos,n_medicos,doc);
            if (pos_med==NO_ENCONTRADO) {
                cods_medicos[n_medicos]=doc;
                cants_atenciones[n_medicos]++;
                tiempos_atenciones[n_medicos]+=(hora_salida-hora_entrada);
                n_medicos++;
            } else {
                cants_atenciones[pos_med]++;
                tiempos_atenciones[pos_med]+=(hora_salida-hora_entrada);
            }
            input.get(c);
            if (c=='\n') break;
        }
    }
}
