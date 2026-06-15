//
// Created by User on 1/06/2026.
//

#include "Funciones.hpp"

void colocar_espacios_minusculas(char * descripcion) {
    bool mayus=true;
    for (int i=0; descripcion[i]; i++) {
        if ((not mayus) and descripcion[i]>='A' and descripcion[i]<='Z') {
            descripcion[i]+=('a'-'A');
        }
        if (mayus) mayus=false;
        if (descripcion[i]=='_') {
            descripcion[i]=' ';
            mayus=true;
        }
    }
}

void modificarCadena(char * descripcion, char * catergoria, bool hayDescuento) {

    colocar_espacios_minusculas(descripcion);
    if (hayDescuento) strcat(descripcion,"-PROMOCIONADO");
    strcat(descripcion,"-");
    strcat(descripcion,catergoria);
}

void imprimir_titulo_encabezado( ofstream & output) {
    encuadrar_char("EMPRESA DE REPARTOS A DOMICILIO TP S. A.", ANCHO_REPORTE, output);
    output<<endl;
    encuadrar_char("RELACIÓN DE PLATOS VENDIDOS", ANCHO_REPORTE, output);
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<left<<setw(5)<<"NO."<<setw(60)<<"PLATO OFRECIDO"<<right;
    encuadrar_char("CANTIDAD VENDIDA", 20, output);
    encuadrar_char("PRECIO", 20, output);
    encuadrar_char("INGRESO BRUTO", 20, output);
    encuadrar_char("DESCUENTO", 20, output);
    encuadrar_char("TOTAL", 20, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void imprimir_reporte(const char * file_entrada, const char * file_salida, int * arr_codigos_platos, int * arr_num_platos_vendidos,
                      double * arr_precio, double * arr_ingreso_bruto, double * arr_descuento, double * arr_total,
                      bool * arr_tiene_descuento, int n_platos) {
    ofstream output;
    abrir_archivo_escritura(file_salida, output);
    ifstream input;
    abrir_archivo_lectura(file_entrada, input);

    output<<fixed;
    output.precision(2);
    int pos_plato, cod_plato_leido;
    double num;
    char descripcion[50]{}, catergoria[50]{},c ;
    imprimir_titulo_encabezado(output);
    int i=0;
    while (true) {
        input>>cod_plato_leido;
        if (input.eof()) break;
        input>>ws>>descripcion>>num>>ws>>catergoria;
        input.get(c);
        if (c==' ') input.ignore(30,'\n');
        pos_plato=busqueda_binaria(cod_plato_leido, arr_codigos_platos, n_platos);
        modificarCadena(descripcion, catergoria, arr_tiene_descuento[pos_plato]);
        output<<setfill('0')<<setw(3)<<i+1<<setfill(' ')<<") ";
        output<<left<<setw(8)<<arr_codigos_platos[pos_plato]<<right;
        output<<descripcion;
        int n = strlen(descripcion);
        output<<setw(60-n)<<"";
        output<<setw(10)<<arr_num_platos_vendidos[pos_plato]<<setw(18)<<arr_precio[pos_plato];
        output<<setw(20)<<arr_ingreso_bruto[pos_plato];
        if (arr_tiene_descuento[pos_plato]) output<<setw(16)<<arr_descuento[pos_plato]<<"%";
        else output<<setw(14)<<"-";
        output<<setw(18)<<arr_total[pos_plato]<<endl;
        i++;
    }
    imprimir_linea(ANCHO_REPORTE,'=', output);
}


void cargar_platos_ofrecidos(const char *file_name, double * arrPrecio, double * arrIngresoBruto, double * arrDescuento, double * arrTotal,
                             bool * arrTieneDescuento, int n_platos, int * arrCodigosPlatos, int * arrNumPlatosVendidos) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int cod_plato_leido, pos_plato;
    double precio, descuento;
    char c, palabra[100]{};
    while (true) {
        bool hayDescuento=false;
        input>>cod_plato_leido;
        if (input.eof()) break;
        input>>ws>>palabra>>precio>>ws>>palabra;
        input.get(c);
        if (c==' ') {
            input>>descuento>>c;
            hayDescuento=true;
        }
        pos_plato=busqueda_binaria(cod_plato_leido, arrCodigosPlatos, n_platos);
        if (pos_plato!=NO_ENCONTRADO) {
            arrPrecio[pos_plato]=precio;
            arrIngresoBruto[pos_plato]=precio*arrNumPlatosVendidos[pos_plato];
            if (hayDescuento) {
                arrTieneDescuento[pos_plato]=hayDescuento;
                arrDescuento[pos_plato]=descuento;
                arrTotal[pos_plato]=arrIngresoBruto[pos_plato]*(1-arrDescuento[pos_plato]/100.0);
            } else {
                arrTieneDescuento[pos_plato]=hayDescuento;
                arrDescuento[pos_plato]=0;
                arrTotal[pos_plato]=arrIngresoBruto[pos_plato];
            }
        }
    }

    input.close();
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura: "<<file_name << endl;
        exit(1);
    }
}

void encuadrar_char(const char * cadena, int ancho, ofstream &output) {
    int n=strlen(cadena);
    output<<setw((ancho+n)/2)<<cadena<<setw(ancho - (ancho+n)/2)<<"";
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i=0; i<n; i++) output.put(c);
    output<<endl;
}

void prueba_carga_platos_vendidos(const char * file_name, int * arrCodigosPlatos, int * arr_num_platos_vendidos, int n_platos,
                                  double * arr_precio, double * arr_ingreso_bruto, double * arr_descuento, double * arr_total,
                                  bool * arr_tiene_descuento){
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    encuadrar_char("PRUEBA DE CARGA DE LOS PLATOS VENDIDOS", ANCHO_REPORTE, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', output);
    encuadrar_char("CODIGO PLATO", ANCHO_REPORTE/7, output);
    encuadrar_char("CANT.PLATOS.VEND.", ANCHO_REPORTE/7, output);
    encuadrar_char("PRECIO", ANCHO_REPORTE/7, output);
    encuadrar_char("INGRESO BRUTO", ANCHO_REPORTE/7, output);
    encuadrar_char("TIENE DESC.", ANCHO_REPORTE/7, output);
    encuadrar_char("DESCUENTO", ANCHO_REPORTE/7, output);
    encuadrar_char("TOTAL PAGADO", ANCHO_REPORTE/7, output);
    output<<endl;

    for (int i=0; i<n_platos; i++) {
        output<<setw(ANCHO_REPORTE/7)<<arrCodigosPlatos[i];
        output<<setw(ANCHO_REPORTE/7)<<arr_num_platos_vendidos[i];
        output<<setw(ANCHO_REPORTE/7)<<arr_precio[i];
        output<<setw(ANCHO_REPORTE/7)<<arr_ingreso_bruto[i];
        output<<setw(ANCHO_REPORTE/7)<<arr_tiene_descuento[i];
        output<<setw(ANCHO_REPORTE/7)<<arr_descuento[i];
        output<<setw(ANCHO_REPORTE/7)<<arr_total[i]<<endl;
    }
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: "<<file_name<< endl;
        exit(1);
    }
}

int busqueda_binaria(int value, int * arr, int n) {
    int limite_inferior=0, limite_superior=n-1, punto_medio;

    while (true) {
        if (limite_inferior > limite_superior) return NO_ENCONTRADO;
        punto_medio=(limite_inferior+limite_superior)/2;
        if (arr[punto_medio] == value) return punto_medio;
        if (value > arr[punto_medio]) limite_superior=punto_medio-1;
        else limite_inferior=punto_medio+1;
    }
}

void insertar_ordenado(int cant, int cod_plato, int * arr_codigos_platos, int * arr_num_platos_vendidos, int &n_platos) {
    int i=n_platos-1;

    while (i>=0 and arr_codigos_platos[i] < cod_plato) {
        arr_codigos_platos[i+1]=arr_codigos_platos[i];
        arr_num_platos_vendidos[i+1]=arr_num_platos_vendidos[i];
        i--;
    }
    arr_codigos_platos[i+1]=cod_plato;
    //cout<<cod_plato<<endl;
    arr_num_platos_vendidos[i+1]=cant;
    n_platos++;
}

void insertar_ordenado_sin_repeticion(int cant, int cod_plato, int * arr_codigos_platos, int * arr_num_platos_vendidos, int & n_platos) {
    int pos_plato;
    pos_plato=busqueda_binaria(cod_plato, arr_codigos_platos, n_platos);
    if (pos_plato == NO_ENCONTRADO) {
        insertar_ordenado(cant, cod_plato, arr_codigos_platos,arr_num_platos_vendidos, n_platos);
    } else {
        arr_num_platos_vendidos[pos_plato]+=cant;
    }
}

void cargar_platos(const char *file_name, int *arrCodigosPlatos, int *arrNumPlatosVendidos, int &n_platos) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dni, n_pedido, cant, cod_plato;
    char c;
    while (true) {
        input>>n_pedido;
        if (input.eof()) break;
        input>>dni;
        while (true) {
            input>>cant>>cod_plato;
            insertar_ordenado_sin_repeticion(cant, cod_plato, arrCodigosPlatos, arrNumPlatosVendidos, n_platos);
            input.get(c);
            if (c=='\n') break;
        }
    }
}
