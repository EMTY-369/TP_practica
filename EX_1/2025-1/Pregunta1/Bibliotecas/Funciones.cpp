//
// Created by User on 17/05/2026.
//

#include "Funciones.hpp"

void abrir_archivo_lectura(const char *file_name, ifstream &input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura" << file_name << endl;
        exit(1);
    }
}

void abrir_archivo_escritura(const char *file_name, ofstream &output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura" << file_name << endl;
        exit(1);
    }
}

void imprimir_titulo( ofstream & output) {
    output<<setw((ANCHO_REPORTE+24)/2)<<"MINISTERIO DE TRANSPORTE"<<endl;
    output<<setw((ANCHO_REPORTE+40)/2)<<"LISTADO DE ESTADO DE MULTAS POR COMPANIA"<<endl;
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i=0; i<n; i++) output.put(c);
    output<<endl;
}

void imprimir_texto( ifstream & input, int espacio, char del,bool mayus, ofstream & output) {
    char c;
    int n=0;
    input>>ws;
    while (true) {
        input.get(c);
        if (c==del) break;
        if (c=='/' or c=='-') c=' ';
        if (mayus and c>='a' and c<='z') c-='a'-'A';
        output.put(c);
        n++;
        if (n==espacio-3) {
            output<<"...";
            break;
        }
    }
    for (int i=0; i<espacio-n; i++) output.put(' ');
}

void imprimir_encabezado(int dni, int i, ifstream &input, ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'=', output);
    output<<"COMPANIA No.  "<<setw(2)<<i<<endl;
    output<<"REPRESENTANTE LEGAL:  ";
    imprimir_texto(input, 44 , ' ', true, output);
    output<<"DNI:"<<setw(10)<<dni<<setw(19)<<"DISTRITO:  ";
    imprimir_texto(input, 28 , '\n', true, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'=', output);
}

void imprimir_tipo(char placa_char, ofstream & output) {
    if (placa_char=='P') output<<"PEQUENO";
    if (placa_char=='M') output<<"MEDIANO";
    if (placa_char=='G') output<<"GRANDE";
    output<<endl;
}

void imprimir_titulo_tablas(bool pagadas, ofstream & output) {
    if (pagadas) output<<setw(22)<<"MULTAS PAGADAS"<<endl;
    else output<<setw(33)<<"MULTAS PENDIENTES DE PAGO"<<endl;
    output<<setw(8)<<""<<left<<setw(8)<<"No."<<right;
    output<<setw(8)<<"FECHA";
    if (pagadas) {
        output<<setw(23)<<"FECHA DE PAGO";
    }
    output<<setw(20)<<"INFRACCION";
    output<<setw(16)<<"GRAVEDAD";
    output<<setw(17)<<"MULTA";
    output<<setw(21)<<"DESCRIPCION";
    output<<endl;
}
int leer_fecha(ifstream &input) {
    int dd,mm,aa;
    char c;
    input>>dd;
    if (input.eof()) return -1;
    input>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void imprimir_fecha(int fecha, ofstream & output) {
    int dd,mm,aa;
    aa=fecha/10000;
    fecha/=10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void imprimir_tipo_infrac(char infrac_char, ofstream & output) {
    output<<setw(14)<<""<<left<<setw(10);
    if (infrac_char=='L') output<<"LEVE";
    if (infrac_char=='G') output<<"GRAVE";
    if (infrac_char=='M') output<<"MUY GRAVE";
    output<<right;
}

void buscar_imprimir_infrac(char infrac_char, int infrac_int, double &multas, ifstream &input, ofstream & output) {
    input.clear();
    input.seekg (0, ios::beg);
    int infrac_int_leido, encontrado=1;
    double pago;
    char infrac_char_leido;
    while (true) {
        input>>ws>>infrac_char_leido;
        if (input.eof()) break;
        input>>infrac_int_leido>>pago;
        if (infrac_char==infrac_char_leido and infrac_int==infrac_int_leido) {
            output<<setw(16)<<pago<<setw(4)<<"";
            multas+=pago;
            imprimir_texto(input,50,'\n',false,output);
            output<<endl;
            encontrado=1;
            break;
        }else {
            encontrado=NO_ENCONTRADO;
            input.ignore(300,'\n');
        }
    }
    if (encontrado==NO_ENCONTRADO) {
        output<<setw(10)<<""<<"No se encontro esa infraccion"<<endl;
    }
}

void buscar_imprimir_multas( ifstream &input_infrac_cometidas, ifstream &input_tabla_infrac, ofstream &output,
                             char placa_char, int placa_int, bool pagadas, double &multas) {
    input_infrac_cometidas.clear();
    input_infrac_cometidas.seekg(0,ios::beg);
    int fecha, i=0, parte1, parte2, infrac_int, fecha_pagado;
    char placa_char_leido, c, infrac_char;
    while (true) {
        fecha=leer_fecha(input_infrac_cometidas);
        if (fecha==-1 or input_infrac_cometidas.eof()) break;
        input_infrac_cometidas>>ws>>placa_char_leido>>parte1>>c>>parte2>>ws>>infrac_char>>infrac_int;
        if (placa_char_leido==placa_char and placa_int==parte1*1000+parte2) {
            input_infrac_cometidas.get(c);
            if (pagadas and c==' ' or (not pagadas) and c=='\n') {
                i++;
                output<<setw(8)<<""<<setfill('0')<<setw(2)<<i<<setfill(' ')<<left<<setw(5)<<")"<<right<<setw(4)<<"";
                imprimir_fecha(fecha, output);
                if (pagadas) {
                    input_infrac_cometidas>>ws>>c;
                    fecha_pagado=leer_fecha(input_infrac_cometidas);
                    output<<setw(5)<<"";
                    imprimir_fecha(fecha_pagado, output);
                    output<<setw(17);
                } else {
                    output<<setw(9);
                }
                output<<infrac_int;
                imprimir_tipo_infrac(infrac_char, output);
                buscar_imprimir_infrac(infrac_char, infrac_int, multas, input_tabla_infrac, output);
            }
            if ((not pagadas) and c!='\n') input_infrac_cometidas.ignore(40,'\n');
        } else {
            input_infrac_cometidas.ignore(70, '\n');
        }
    }
}

void leer_imprimir_placas(ifstream &input_placas, ifstream &input_tabla_infrac, ifstream &input_infrac_cometidas, int dni,
                          double &multas_pagadas, double &multas_pendientes, ofstream & output) {
    input_placas.clear();
    input_placas.seekg(0,ios::beg);
    char placa_char,c;
    int parte1,parte2,dni_leido,i=0;
    while (true) {
        input_placas>>dni_leido;
        if (input_placas.eof()) break;
        input_placas>>ws;
        if (dni==dni_leido) {
            input_placas>>placa_char>>parte1>>c>>parte2;
            i++;
            output<<setw(2)<<""<<setfill('0')<<setw(2)<<i<<setfill(' ')<<")   ";
            output<<"PLACA:  "<<placa_char<<parte1<<"-"<<parte2;
            output<<setw(11)<<"TIPO:  ";
            imprimir_tipo(placa_char,output);
            imprimir_titulo_tablas(true, output);
            double placa_pagadas=0, placa_pendientes=0;
            buscar_imprimir_multas(input_infrac_cometidas,input_tabla_infrac,output,placa_char,parte1*1000+parte2,
                                   true,placa_pagadas);
            output<<setw(8)<<""<<"TOTAL MULTAS PAGADAS:  "<<placa_pagadas<<endl;
            imprimir_linea(ANCHO_REPORTE,'-',output);
            imprimir_titulo_tablas(false, output);
            buscar_imprimir_multas(input_infrac_cometidas,input_tabla_infrac,output,placa_char,parte1*1000+parte2,
            false, placa_pendientes);
            output<<setw(8)<<""<<"TOTAL MULTAS PENDIENTES DE PAGO:  "<<placa_pendientes<<endl;
            imprimir_linea(ANCHO_REPORTE,'=',output);
            multas_pagadas+=placa_pagadas;
            multas_pendientes+=placa_pendientes;
        } else {
            input_placas.ignore(10,'\n');
        }
    }
}

void imprimir_reporte(const char *file_empresas, const char *file_placas, const char *file_tabla, const char *file_infrac,
                      const char *file_salilda) {
    ifstream input_empresas, input_placas, input_tabla_infrac, input_infrac_cometidas;
    abrir_archivo_lectura(file_empresas,input_empresas);
    abrir_archivo_lectura(file_placas,input_placas);
    abrir_archivo_lectura(file_tabla,input_tabla_infrac);
    abrir_archivo_lectura(file_infrac,input_infrac_cometidas);
    ofstream output;
    abrir_archivo_escritura(file_salilda,output);

    output<<fixed;
    output.precision(2);
    imprimir_titulo(output);
    int DNI,i=0;
    while (true) {
        input_empresas>>DNI;
        if (input_empresas.eof()) break;
        i++;
        imprimir_encabezado(DNI, i, input_empresas, output);
        double multas_pagadas=0, multas_pendientes=0;
        leer_imprimir_placas(input_placas,input_tabla_infrac,input_infrac_cometidas,DNI,multas_pagadas,
                             multas_pendientes, output);
        output<<"TOTAL MULTAS PAGADAS POR LA COMPANIA:  "<<multas_pagadas<<endl;
        output<<"TOTAL MULTAS PENDIENTES DE PAGO POR LA COMPANIA:   "<<multas_pendientes<<endl;
    }
    input_empresas.close();
    input_placas.close();
    input_tabla_infrac.close();
    input_infrac_cometidas.close();
    output.close();
}
