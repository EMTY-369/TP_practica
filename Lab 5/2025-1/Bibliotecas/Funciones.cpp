//
// Created by User on 10/05/2026.
//

#include "Funciones.hpp"

void imprimir_titulo_1(ofstream & output) {
    output<<setw((ANCHO_REPORTE+24)/2)<<"MINISTERIO DE TRANSPORTE"<<endl;
    output<<setw((ANCHO_REPORTE+32)/2)<<"MULTAS IMPUESTAS A LAS COMPANIAS"<<endl;
}

void imprimir_encabezados(ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<"MULTAS APLICADAS SEGÚN LA GRAVEDAD:"<<endl;
    output<<setw(6)<<""<<setw((((ANCHO_REPORTE-6)/4)+6)/2)<<"LEVES "<<setw((((ANCHO_REPORTE-6)/4)-6)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/4)+6)/2)<<"GRAVES"<<setw((((ANCHO_REPORTE-6)/4)-6)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/4)+10)/2)<<"MUY GRAVES"<<setw((((ANCHO_REPORTE-6)/4)-10)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/4)+8)/2)<<"TOTALES "<<setw((((ANCHO_REPORTE-6)/4)-8)/2)<<""<<endl;

    output<<setw(6)<<""<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<"CANTIDAD"<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+16)/2)<<"TOTAL DE MULTAS "<<setw((((ANCHO_REPORTE-6)/8)-16)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<"CANTIDAD"<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+16)/2)<<"TOTAL DE MULTAS "<<setw((((ANCHO_REPORTE-6)/8)-16)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<"CANTIDAD"<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+16)/2)<<"TOTAL DE MULTAS "<<setw((((ANCHO_REPORTE-6)/8)-16)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+12)/2)<<"EN CANTIDAD "<<setw((((ANCHO_REPORTE-6)/8)-12)/2)<<"";
    output<<setw((((ANCHO_REPORTE-6)/8)+10)/2)<<"EN MULTAS "<<setw((((ANCHO_REPORTE-6)/8)-10)/2)<<""<<endl;
}

void imprimir_titulo_2_encabezado(ofstream & output) {
    output<<endl;
    output<<setw((ANCHO_REPORTE+31)/2)<<"MULTAS IMPUESTAS POR INFRACCION"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw(((ANCHO_REPORTE)/5+6)/2)<<"CODIGO"<<setw(((ANCHO_REPORTE/5)-6)/2)<<"";
    output<<setw(((ANCHO_REPORTE)/5+8)/2)<<"GRAVEDAD"<<setw(((ANCHO_REPORTE/5)-8)/2)<<"";
    output<<setw(((ANCHO_REPORTE)/5+6)/2)<<"MULTA "<<setw(((ANCHO_REPORTE/5)-6)/2)<<"";
    output<<setw(((ANCHO_REPORTE)/5+8)/2)<<"CANTIDAD"<<setw(((ANCHO_REPORTE/5)-8)/2)<<"";
    output<<setw(((ANCHO_REPORTE)/5+12)/2)<<"MONTO TOTAL "<<setw(((ANCHO_REPORTE/5)-12)/2)<<""<<endl;
}

void generar_reporte(const char *file_name, int *cants_leves, int *cants_graves, int *cants_muy_graves, int *cants_totales,
                     double * costos_leves, double * costos_graves, double * costos_muy_graves, double * costos_totales,
                     int n_empresas, int * cants_infrac, double * monto_totales, int n_infrac, int * DNIs_empresas,
                     char *codigos_char_infrac, int * codigos_int_infrac, double * costos_infrac) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    imprimir_titulo_1(output);
    for (int i=0; i<n_empresas; i++) {
        imprimir_linea(ANCHO_REPORTE,'=',output);
        output<<"COMPANIA No. "<<i+1<<" DNI DEL REPRESENTANTE LEGAL:  "<<DNIs_empresas[i]<<endl;
        output<<fixed;
        imprimir_encabezados(output);
        output<<setw(6)<<""<<setw((((ANCHO_REPORTE-6)/8)+2)/2)<<cants_leves[i]<<setw((((ANCHO_REPORTE-6)/8)-2)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<setprecision(2)<<costos_leves[i]<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+2)/2)<<cants_graves[i]<<setw((((ANCHO_REPORTE-6)/8)-2)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<costos_graves[i]<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+2)/2)<<cants_muy_graves[i]<<setw((((ANCHO_REPORTE-6)/8)-2)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<costos_muy_graves[i]<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+2)/2)<<cants_totales[i]<<setw((((ANCHO_REPORTE-6)/8)-2)/2)<<"";
        output<<setw((((ANCHO_REPORTE-6)/8)+8)/2)<<costos_totales[i]<<setw((((ANCHO_REPORTE-6)/8)-8)/2)<<""<<endl;
    }
    imprimir_linea(ANCHO_REPORTE,'/',output);
    int total_cant=0;
    double total_monto=0;
    imprimir_titulo_2_encabezado(output);
    for (int i=0; i<n_infrac; i++) {
        output<<setw(((ANCHO_REPORTE)/5+4)/2)<<codigos_int_infrac[i]<<setw(((ANCHO_REPORTE/5)-4)/2)<<"";
        output<<setw(8)<<"";
        if (codigos_char_infrac[i]=='L') output<<"LEVE"<<setw(ANCHO_REPORTE/5 -8-4)<<"";
        if (codigos_char_infrac[i]=='G') output<<"GRAVE"<<setw(ANCHO_REPORTE/5 -8-5)<<"";
        if (codigos_char_infrac[i]=='M') output<<"MUY GRAVE"<<setw(ANCHO_REPORTE/5 -8-9)<<"";
        output<<setw(((ANCHO_REPORTE)/5+6)/2)<<costos_infrac[i]<<setw(((ANCHO_REPORTE/5)-6)/2)<<"";
        output<<setw(((ANCHO_REPORTE)/5+2)/2)<<cants_infrac[i]<<setw(((ANCHO_REPORTE/5)-2)/2)<<"";
        output<<setw(((ANCHO_REPORTE)/5+8)/2)<<monto_totales[i]<<setw(((ANCHO_REPORTE/5)-8)/2)<<""<<endl;
        total_cant+=cants_infrac[i];
        total_monto+=monto_totales[i];
    }
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<setw(((ANCHO_REPORTE)/5+6)/2)<<"TOTAL "<<setw(((ANCHO_REPORTE/5)-6)/2)<<"";
    output<<setw(2*ANCHO_REPORTE/5)<<"";
    output<<setw(((ANCHO_REPORTE)/5+3)/2)<<total_cant<<setw(((ANCHO_REPORTE/5)-3)/2)<<"";
    output<<setw(((ANCHO_REPORTE)/5+8)/2)<<total_monto<<setw(((ANCHO_REPORTE/5)-8)/2)<<""<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output.close();
}

int buscar_representante(char placa_char_leido, int placa_int_leido, char * placas_char, int * placas_int, int * DNIs_placas, int n_placas) {

    for (int i=0; i<n_placas; i++) {
        if (placas_char[i]==placa_char_leido and placas_int[i]==placa_int_leido) return (DNIs_placas[i]);
    }
    return NO_ENCONTRADO;
}

int buscar_empresa(int DNI, int *DNIs_empresas, int n_empresas) {
    for (int i=0; i<n_empresas; i++) {
        if (DNIs_empresas[i]==DNI) return i;
    }
    return NO_ENCONTRADO;
}

int buscar_infraccion(char infrac_char_leido, int infrac_int_leido, char * codigos_char_infrac, int * codigos_int_infrac, int n_infrac) {
    for (int i=0; i<n_infrac; i++) {
        if (codigos_char_infrac[i]==infrac_char_leido and
            codigos_int_infrac[i]==infrac_int_leido) return i;
    }
    return NO_ENCONTRADO;
}

void cargar_multas(const char *file_name, int *cants_leves, int *cants_graves, int *cants_muy_graves, int *cants_totales,
                   double *costos_leves, double *costos_graves, double *costos_muy_graves, double *costos_totales,
                   int n_empresas, int * cants_infrac, double * monto_totales, int n_infrac,int * DNIs_empresas,
                   char *codigos_char_infrac, int *codigos_int_infrac, double * costos_infrac, char *placas_char,
                   int *placas_int, int *DNIs_placas,int n_placas) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    char placa_char_leido,c,infrac_char_leido;
    int dd,parte1,parte2,infrac_int_leido,DNI,pos_empresa,pos_infrac;
    while (true) {
        input>>dd;
        if (input.eof()) break;
        input.ignore(9,' ');
        input>>ws>>placa_char_leido>>parte1>>c>>parte2>>ws>>infrac_char_leido>>infrac_int_leido;
        DNI=buscar_representante(placa_char_leido,(parte1*1000+parte2),placas_char,placas_int,DNIs_placas,n_placas);
        if (DNI!=NO_ENCONTRADO) {
            pos_empresa=buscar_empresa(DNI,DNIs_empresas,n_empresas);
            if (pos_empresa!=NO_ENCONTRADO) {
                pos_infrac=buscar_infraccion(infrac_char_leido,infrac_int_leido,codigos_char_infrac,codigos_int_infrac,n_infrac);
                if (pos_infrac!=NO_ENCONTRADO) {
                    if (codigos_char_infrac[pos_infrac]=='L') {
                        cants_leves[pos_empresa]++;
                        costos_leves[pos_empresa]+=costos_infrac[pos_infrac];
                    }
                    if (codigos_char_infrac[pos_infrac]=='G') {
                        cants_graves[pos_empresa]++;
                        costos_graves[pos_empresa]+=costos_infrac[pos_infrac];
                    }
                    if (codigos_char_infrac[pos_infrac]=='M') {
                        cants_muy_graves[pos_empresa]++;
                        costos_muy_graves[pos_empresa]+=costos_infrac[pos_infrac];
                    }
                    cants_totales[pos_empresa]++;
                    costos_totales[pos_empresa]+=costos_infrac[pos_infrac];

                    cants_infrac[pos_infrac]++;
                    monto_totales[pos_infrac]+=costos_infrac[pos_infrac];
                }
            }
        }
    }
}

void cargar_placas(const char *file_name, char *placas_char, int *placas_int, int *DNIs_placas, int &n_placas) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    char c;
    int DNI_leido, parte1, parte2;
    while (true) {
        input>>DNI_leido;
        if (input.eof()) break;
        input>>ws>>placas_char[n_placas]>>parte1>>c>>parte2;
        placas_int[n_placas]=parte1*1000+parte2;
        DNIs_placas[n_placas]=DNI_leido;
        n_placas++;
    }
}

void probar_carga_infracciones(const char *file_name, char *codigos_char_infrac, int *codigos_int_infrac,
                               double *costos_infrac, int n_infrac) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    output<<setw((ANCHO_REPORTE+24)/2)<<"PRUEBA DE CARGA DE INFRACCIONES"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<left<<setw(ANCHO_REPORTE/2)<<"CODIGOS";
    output<<setw(ANCHO_REPORTE/2)<<"VALOR DE LA MULTA"<<endl;
    output<<fixed<<right;
    for (int i=0; i<n_infrac; i++) {
        output<<codigos_char_infrac[i]<<codigos_int_infrac[i]<<setw(ANCHO_REPORTE/2 -5)<<"";
        output<<setw(11)<<setprecision(2)<<costos_infrac[i]<<setw(ANCHO_REPORTE/2 - 11)<<""<<endl;
    }
    output.close();
}

void insertar_ordenar_infrac(int codigo_int_leido, char codigo_char_leido, double costo_leido, int n_infrac, int * codigos_int_infrac,
                            char * codigos_char_infrac, double * costos_infrac) {
    int i=n_infrac-1;

    while (i>=0 and codigos_int_infrac[i]>codigo_int_leido) {
        codigos_int_infrac[i+1]=codigos_int_infrac[i];
        codigos_char_infrac[i+1]=codigos_char_infrac[i];
        costos_infrac[i+1]=costos_infrac[i];
        i--;
    }

    codigos_int_infrac[i+1]=codigo_int_leido;
    codigos_char_infrac[i+1]=codigo_char_leido;
    costos_infrac[i+1]=costo_leido;
}

void cargar_infracciones(const char *file_name, char *codigos_char_infrac, int *codigos_int_infrac, double *costos_infrac, int &n_infrac) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int codigo_int_leido;
    double costo_leido;
    char codigo_char_leido;
    while (true) {
        input>>codigo_char_leido;
        if (input.eof()) break;
        input>>codigo_int_leido>>costo_leido;
        insertar_ordenar_infrac(codigo_int_leido, codigo_char_leido, costo_leido, n_infrac, codigos_int_infrac,
                                codigos_char_infrac, costos_infrac);
        n_infrac++;
        input>>ws;
        input.ignore(300, '\n');
    }
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo: " << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i=0; i<n; i++) output.put(c);
    output<<endl;
}

void probar_carga_empresas(const char *file_name, int *DNIs_empresas, int n_empresas) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    output<<setw((60+24)/2)<<"PRUEBA DE CARGA EMPRESAS"<<endl;
    imprimir_linea(60,'=',output);
    output<<left<<setw(60)<<"CODIGOS"<<endl;
    imprimir_linea(60,'-',output);
    for (int i=0; i<n_empresas; i++) {
        output<<DNIs_empresas[i]<<endl;
    }
    output<<right;
    imprimir_linea(60,'-',output);
    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: " << file_name << endl;
        exit(1);
    }
}

void insertar_ordenar_dni(int DNI, int * DNIs_empresas, int n_empresas) {
    int i=n_empresas-1;

    while (i>=0 and DNIs_empresas[i]>DNI) {
        DNIs_empresas[i+1]=DNIs_empresas[i];
        i--;
    }

    DNIs_empresas[i+1]=DNI;
}

void cargar_empresas(const char *file_name, int *DNIs_empresas, int  &n_empresas) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int DNI;
    while (true) {
        input>>DNI;
        if (input.eof()) break;
        insertar_ordenar_dni(DNI, DNIs_empresas, n_empresas);
        n_empresas++;
        input>>ws;
        input.ignore(300, '\n');
    }
}
