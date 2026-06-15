//
// Created by User on 31/05/2026.
//

#include "Funciones.hpp"

void encuadrar_char(const char *cadena, int ancho, ofstream &output) {
    int n=strlen(cadena);
    output<<setw((ancho+n)/2)<<cadena<<setw(ancho-(ancho+n)/2)<<"";
}

void imprimir_titulo_y_encabezado( ofstream & output) {
    output<<setw((ANCHO_REPORTE+25)/2)<<"MINISTERIO DE TRANSPORTES"<<endl;
    output<<setw((ANCHO_REPORTE+23)/2)<<"LISTADO DE INFRACCIONES"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw(5+10+50)<<"";
    encuadrar_char("MULTA MAS", 15, output);
    encuadrar_char("ULTIMA MULTA", 15, output);
    encuadrar_char("TOTAL EN", 15, output);
    encuadrar_char("MULTAS", 15, output);
    encuadrar_char("MULTAS", 15, output);
    output<<endl;
    output<<left<<setw(5)<<"No."<<setw(10)<<"DNI"<<setw(50)<<"PLACAS"<<right;
    encuadrar_char("MAS ANTIGUA", 15, output);
    encuadrar_char("PAGADA", 15, output);
    encuadrar_char("MULTAS", 15, output);
    encuadrar_char("PAGADAS", 15, output);
    encuadrar_char("PENDIENTES", 15, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

int contar_placas(const char * listaDePlacas) {
    int n_char_placas=0;
    for (int i=0; listaDePlacas[i]; i++) {
        if (listaDePlacas[i]!='/') n_char_placas++;
    }
    return n_char_placas/8;
}

void obtener_placa(const char * listaDePlacas, int n, char *placa) {
    //int n_placas = contar_placas(listaDePlacas);
    int j=(n-1)*9;
    for (int i=0; i<8; i++) {
        placa[i]=listaDePlacas[j];
        j++;
    }
    placa[8]='\0';
}

void agregar_placa(char *listaDePlacas, const char *placa) {
    int n_placas=contar_placas(listaDePlacas);
    char placa_lista[9]{};

    if (n_placas==0) {
        strcpy(listaDePlacas, placa);
        return;
    }
    for (int i=1; i<=n_placas; i++) {
        obtener_placa(listaDePlacas, i, placa_lista);
        if (strcmp(placa_lista, placa) == 0) return;
    }
    strcat(listaDePlacas, "/");
    strcat(listaDePlacas, placa);
}

void imprimir_placas(int dni, ofstream & output, ifstream & input) {
    char listaDePlacas[50]{}, placa[9]{};

    input.clear();
    input.seekg(0, ios::beg);

    int dni_leido;
    while (true) {
        input>>dni_leido;
        if (input.eof()) break;
        input>>placa;
        if (dni==dni_leido) {
            agregar_placa(listaDePlacas, placa);
        }
    }
    output<<listaDePlacas;
    int n=strlen(listaDePlacas);
    output<<setw(50-n)<<"";
}

void imprimir_fecha(int fecha, ofstream & output) {
    int dd, mm, aa;
    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void imprimir_reporte(const char * file_salida, const char * file_placas, int * arr_dni, int * arr_mas_multa_antigua,
                      int * arr_ultima_pendiente, double * arr_total_multas, double * arr_total_pagadas,
                      double * arr_total_pendientes, int n_cometidas) {
    ofstream output;
    abrir_archivo_escritura(file_salida, output);
    ifstream input;
    abrir_archivo_lectura(file_placas, input);

    output<<fixed;
    output.precision(2);
    imprimir_titulo_y_encabezado(output);
    double suma_multas=0, suma_pagadas=0, suma_pendientes=0;
    for (int i=0; i<n_cometidas; i++) {
        output<<setw(2)<<i+1<<")  "<<left<<setw(10)<<arr_dni[i]<<right;
        imprimir_placas(arr_dni[i], output, input);
        imprimir_fecha(arr_mas_multa_antigua[i], output);
        output<<setw(5)<<"";
        imprimir_fecha(arr_ultima_pendiente[i], output);
        output<<setw(15)<<arr_total_multas[i]<<setw(16)<<arr_total_pagadas[i]<<setw(15)<<arr_total_pendientes[i]<<endl;
        suma_multas+=arr_total_multas[i];
        suma_pagadas+=arr_total_pagadas[i];
        suma_pendientes+=arr_total_pendientes[i];
    }
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<left<<setw(5+10+50+30)<<"  TOTALES"<<right<<setw(10)<<suma_multas<<setw(16)<<suma_pagadas<<setw(15)<<suma_pendientes<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);

    input.close();
    output.close();
}

int leer_fecha( ifstream & input) {
    int dd, mm, aa;
    char c;
    input>>dd;
    if (input.eof()) return (-1);
    input>>c>>mm>>c>>aa;
    return aa*10000 + mm*100 + dd;
}

int busqueda_binaria(int value, int * arr, int n) {
    int limite_inferior=0, limite_superior=n-1, punto_medio;

    while (true) {
        if ( limite_inferior > limite_superior) return NO_ENCONTRADO;
        punto_medio=(limite_inferior+limite_superior)/2;
        if (value==arr[punto_medio]) return punto_medio;
        if (value<arr[punto_medio]) limite_superior=punto_medio-1;
        else limite_inferior=punto_medio+1;
    }
}

void insetar_ordenado_dni(int dni, int fecha, int fecha_pago, double costo, int * arr_dni, int * arr_mas_multa_antigua,
                         double * arr_total_multas, int * arr_ultima_pendiente, double * arr_total_pagadas,
                         double * arr_total_pendientes, int &n_cometidas) {
    int i=n_cometidas-1;
    while (i>=0 and arr_dni[i]>dni) {
        arr_dni[i+1]=arr_dni[i];
        arr_mas_multa_antigua[i+1]=arr_mas_multa_antigua[i];
        arr_total_multas[i+1]=arr_total_multas[i];
        arr_ultima_pendiente[i+1]=arr_ultima_pendiente[i];
        arr_total_pagadas[i+1]=arr_total_pagadas[i];
        arr_total_pendientes[i+1]=arr_total_pendientes[i];
        i--;
    }
    arr_dni[i+1]=dni;
    arr_mas_multa_antigua[i+1]=fecha;
    arr_total_multas[i+1]=costo;
    if (fecha_pago>0) {
        arr_ultima_pendiente[i+1]=fecha_pago;
        arr_total_pagadas[i+1]=costo;
        arr_total_pendientes[i+1]=0;
    }
    if (fecha_pago==0) {
        arr_total_pendientes[i+1]=costo;
        arr_ultima_pendiente[i+1]=0;
        arr_total_pagadas[i+1]=0;
    }
    n_cometidas++;
}

void insertar_ordenado_sin_repeticion(int dni, int fecha, double costo, int fecha_pago, int * arr_dni, int * arr_mas_multa_antigua,
                                      int * arr_ultima_pendiente, double * arr_total_multas, double * arr_total_pagadas,
                                      double * arr_total_pendientes, int & n_cometidas) {
    int pos_dni;
    pos_dni=busqueda_binaria(dni, arr_dni, n_cometidas);

    if (pos_dni==NO_ENCONTRADO) {
        insetar_ordenado_dni(dni, fecha, fecha_pago, costo, arr_dni, arr_mas_multa_antigua,arr_total_multas,
                             arr_ultima_pendiente, arr_total_pagadas, arr_total_pendientes, n_cometidas);
    } else {
        if (arr_mas_multa_antigua[pos_dni]<fecha or arr_mas_multa_antigua[pos_dni]==0) arr_mas_multa_antigua[pos_dni]=fecha;
        arr_total_multas[pos_dni]+=costo;
        if (fecha_pago>0) {
            if (arr_ultima_pendiente[pos_dni]<fecha_pago or arr_ultima_pendiente[pos_dni]==0) arr_ultima_pendiente[pos_dni]=fecha_pago;
            arr_total_pagadas[pos_dni]+=costo;
        }
        if (fecha_pago==0) {
            arr_total_pendientes[pos_dni]+=costo;
        }
    }
}

void cargar_infracciones_cometidas(const char *file_entrada, const char *file_new, int * arr_codigo_infraccion,
                                   double * arr_multas_infraccion, int n_infrac, int * arr_dni, int * arr_mas_multa_antigua,
                                   int * arr_ultima_pendiente, double * arr_total_multas, double * arr_total_pagadas,
                                   double * arr_total_pendientes, int & n_cometidas) {
    ifstream input;
    abrir_archivo_lectura(file_entrada, input);
    ofstream output;
    abrir_archivo_escritura(file_new, output);
    char placa[10]{}, c;
    int fecha, fecha_pago, dni, cod_infra_leido, pos_infrac;
    while (true) {
        fecha=leer_fecha(input);
        if (fecha==-1 or input.eof()) break;
        input>>ws>>placa>>dni>>cod_infra_leido;
        input.get(c);
        if (c!='\n') {
            input>>c;
            if (c=='P') fecha_pago=leer_fecha(input);
        } else fecha_pago=0;
        pos_infrac=busqueda_binaria(cod_infra_leido, arr_codigo_infraccion, n_infrac);
        double costo = arr_multas_infraccion[pos_infrac];
        insertar_ordenado_sin_repeticion(dni, fecha, arr_multas_infraccion[pos_infrac], fecha_pago,
                                         arr_dni, arr_mas_multa_antigua, arr_ultima_pendiente, arr_total_multas,
                                         arr_total_pagadas, arr_total_pendientes, n_cometidas);
        output<<left<<setw(12)<<dni<<placa<<right<<endl;
    }

    input.close();
    output.close();
}


void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura: " << file_name<< endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i=0; i<n; i++) output.put(c);
    output<<endl;
}

void probar_carga_infracciones(const char * file_name, int * arr_codigo_infraccion, double * arr_multas_infraccion, int n_infrac) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output.precision(2);
    output<<setw(135/2)<<"PRUEBA DE CARGA DE LAS INFRACCIONES" << endl;
    imprimir_linea(100, '=', output);
    output<<left<<setw(50)<<"CODIGO DE LA INFRACCION"<<setw(50)<<"VALOR DE LA MULTA"<<endl<<right;
    imprimir_linea(100, '-', output);
    for (int i=0; i<n_infrac; i++) {
        output<<setw(10)<<arr_codigo_infraccion[i];
        output<<setw(50)<<arr_multas_infraccion[i]<<endl;
    }
    imprimir_linea(100, '-', output);
    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: "<< file_name<< endl;
        exit(1);
    }
}

void insertar_ordenado_infracciones(int codigo, double multa, int * arr_codigo_infraccion, double * arr_multas_infraccion, int &n_infrac) {
    int i=n_infrac-1;

    while (i>=0 and arr_codigo_infraccion[i]>codigo) {
        arr_codigo_infraccion[i+1]=arr_codigo_infraccion[i];
        arr_multas_infraccion[i+1]=arr_multas_infraccion[i];
        i--;
    }

    arr_codigo_infraccion[i+1]=codigo;
    arr_multas_infraccion[i+1]=multa;
    n_infrac++;
}

void cargar_infracciones(const char *file_name, int *arr_codigo_infraccion, double *arr_multas_infraccion, int &n_infrac) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int codigo;
    double multa;
    while (true) {
        input>>codigo;
        if (input.eof()) break;
        input>>multa;
        insertar_ordenado_infracciones(codigo,multa,arr_codigo_infraccion,arr_multas_infraccion,n_infrac);
        input.ignore(200, '\n');
    }
    input.close();
}
