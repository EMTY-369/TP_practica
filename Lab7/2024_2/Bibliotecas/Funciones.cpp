//
// Created by User on 8/06/2026.
//

#include "Funciones.hpp"

void swap_int(int &a, int &b) {
    int aux=a;
    a=b;
    b=aux;
}

void swap_str(char *& str1, char *& str2) {
    char *aux=str1;
    str1=str2;
    str2=aux;
}

void ordenar_repartidores(int * arr_dnis_repartidores, int * arr_cods_distrito, char ** arr_nombres_repartidores,
                          char ** arr_movilidad, char ** arr_nombres_distritos, int n_repartidores) {
    for (int i=0; i<n_repartidores-1; i++) {
        for (int j=i+1; j<n_repartidores; j++) {
            if (strcmp(arr_nombres_repartidores[i], arr_nombres_repartidores[j])>0) {
                swap_int(arr_dnis_repartidores[i], arr_dnis_repartidores[j]);
                swap_int(arr_cods_distrito[i], arr_cods_distrito[j]);
                swap_str(arr_movilidad[i], arr_movilidad[j]);
                swap_str(arr_nombres_repartidores[i], arr_nombres_repartidores[j]);
                swap_str(arr_nombres_distritos[i], arr_nombres_distritos[j]);
            }
        }
    }
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo de escritura: " << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i=0; i<n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void encuadrar(const char * texto, int espacio, ofstream & output) {
    int n=strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', false, output);
}

void imprimir_repartidores(int * arr_dnis_repartidores, char ** arr_nombres_repartidores, char ** arr_movilidad,
                           int * arr_cods_distrito, char ** arr_nombres_distritos, int n_repartidores, ofstream &output) {
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i=0; i<n_repartidores; i++) {
        output<<left<<setw(ANCHO_REPORTE/5)<<arr_dnis_repartidores[i];
        output<<setw(ANCHO_REPORTE/5)<<arr_nombres_repartidores[i];
        output<<setw(ANCHO_REPORTE/5)<<arr_movilidad[i]<<right;
        output<<setw(ANCHO_REPORTE/10)<<arr_cods_distrito[i];
        imprimir_linea(ANCHO_REPORTE/10, ' ', false,output);
        output<<left<<arr_nombres_distritos[i]<<right<<endl;
    }
}

void imprimir_platos(int * arr_cods_platos, double * arr_precio_platos, char ** arr_nombres_platos, char ** arr_categoria_platos,
                     double * arr_descuentos_platos, int n_platos, ofstream & output) {
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i=0; i<n_platos; i++) {
        output<<left<<setw(ANCHO_REPORTE/5)<<arr_cods_platos[i];
        output<<setw(ANCHO_REPORTE/5)<<arr_nombres_platos[i]<<right;
        output<<setw(ANCHO_REPORTE/10)<<arr_precio_platos[i];
        imprimir_linea(ANCHO_REPORTE/10, ' ', false,output);
        output<<left<<setw(ANCHO_REPORTE/5)<<arr_categoria_platos[i]<<right;
        output<<setw(ANCHO_REPORTE/10)<<arr_descuentos_platos[i]<<endl;
    }
}

void prueba_carga_repartidores_platos(const char * file_name, int * arr_dnis_repartidores, int * arr_cods_distrito,
                                      char ** arr_nombres_repartidores, char ** arr_movilidad, char ** arr_nombres_distritos,
                                      int n_repartidores, int * arr_cods_platos, double * arr_precio_platos, double * arr_descuentos_platos,
                                      char ** arr_nombres_platos, char ** arr_categoria_platos, int n_platos) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output<<setprecision(2);

    encuadrar("PRUEBA DE CARGA DE LOS REPARTIDORES", ANCHO_REPORTE, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    encuadrar("DNI", ANCHO_REPORTE/5, output);
    encuadrar("NOMBRE", ANCHO_REPORTE/5, output);
    encuadrar("VEHICULO", ANCHO_REPORTE/5, output);
    encuadrar("CODIGO DEL DISTRITO", ANCHO_REPORTE/5, output);
    encuadrar("NOMBRE DEL DISTRITO", ANCHO_REPORTE/5, output);
    output<<endl;
    imprimir_repartidores(arr_dnis_repartidores, arr_nombres_repartidores, arr_movilidad, arr_cods_distrito,
                          arr_nombres_distritos, n_repartidores, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    encuadrar("PRUEBA DE CARGA DE LOS PLATOS", ANCHO_REPORTE, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    encuadrar("CODIGO", ANCHO_REPORTE/5, output);
    encuadrar("NOMBRE", ANCHO_REPORTE/5, output);
    encuadrar("PRECIO", ANCHO_REPORTE/5, output);
    encuadrar("CATEGORIA", ANCHO_REPORTE/5, output);
    encuadrar("DESCUENTO", ANCHO_REPORTE/5, output);
    output<<endl;
    imprimir_platos(arr_cods_platos, arr_precio_platos, arr_nombres_platos, arr_categoria_platos, arr_descuentos_platos,
                    n_platos, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
}

void cargar_platos(const char * file_name, int * arr_cods_platos, double * arr_precio_platos, double * arr_descuentos_platos,
                   char ** arr_nombres_platos, char ** arr_categoria_platos, int &n_platos) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int cod;
    double descuento;
    while (true) {
        input>>cod;
        if (input.eof()) break;
        arr_nombres_platos[n_platos]= leer_cadena(input, ' ');
        input>>arr_precio_platos[n_platos];
        arr_categoria_platos[n_platos]= leer_cadena(input, ' ');
        if (input.get()==' ') {
            input>>arr_descuentos_platos[n_platos];
            // input>>descuento;
            // arr_descuentos_platos[n_platos] = arr_precio_platos[n_platos]*descuento/100;
            input.get();
        }
        arr_cods_platos[n_platos]= cod;
        n_platos++;
    }
}


void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: "<< file_name << endl;
        exit(1);
    }
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[MAX_TAM_CADENA]{}, *cadena;
    input>>ws;
    //input.getline(buffer, MAX_TAM_CADENA, del);
    input>>buffer;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void cargar_repartidores(const char * file_name, int * arr_dnis_repartidores, int * arr_cods_distrito,
                         char ** arr_nombres_repartidores, char ** arr_movilidad, char ** arr_nombres_distritos,
                         int &n_repartidores) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int cod;
    while (true) {
        input>>cod;
        if (input.eof()) break;
        arr_nombres_repartidores[n_repartidores]= leer_cadena(input, ' ');
        arr_movilidad[n_repartidores]= leer_cadena(input, ' ');
        input>>arr_cods_distrito[n_repartidores];
        arr_nombres_distritos[n_repartidores]= leer_cadena(input, '\n');
        arr_dnis_repartidores[n_repartidores]= cod;
        //cout<<arr_nombres_repartidores[n_repartidores]<<endl;
        n_repartidores++;
    }
}
