//
// Created by User on 4/27/2026.
//

#include "Funciones.hpp"

void calcular_reporte(const char *file_entrada_empresas, const char *file_entrada_infracciones,
                      const char *file_entrada_tabla, const char *file_salida) {
    ifstream input_empresas, input_infracciones, input_tabla;
    apertura_archivos_lectura(file_entrada_empresas, input_empresas);
    apertura_archivos_lectura(file_entrada_infracciones, input_infracciones);
    apertura_archivos_lectura(file_entrada_tabla, input_tabla);

    ofstream output;
    apertura_archivos_escritura(file_salida, output);

    imprimir_titulo(output);
    int compania_mayor_infracciones, compania_menor_infracciones; //DNI de dueño
    double pago_mayor, pago_menor;
    leer_imprimir_companias(compania_mayor_infracciones, compania_menor_infracciones,
                            pago_mayor, pago_menor,
                            input_empresas, input_infracciones, input_tabla, output);
    imprimir_resumen_final(compania_mayor_infracciones,compania_menor_infracciones,pago_mayor,pago_menor,output);

    input_empresas.close();
    input_infracciones.close();
    input_tabla.close();
    output.close();
}

void apertura_archivos_lectura(const char *file_name,ifstream &input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout<<"Error al abrir el archivo de lectura: "<<file_name<<endl;
        exit(1);
    }
}

void apertura_archivos_escritura(const char *file_name,ofstream &output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"Errr al abrir el archivo de escritura"<<endl;
        exit(1);
    }
}

void imprimir_titulo(ofstream &output) {
    output<<setw((ANCHO_REPORTE+22)/2)<<"MINISTRO DE TRANSPORTE"<<endl;
    output<<setw((ANCHO_REPORTE+32)/2)<<"MULTAS IMPUESTAS A LAS COMPANIAS"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_linea(int n,char c,ofstream &output) {
    for (int i=0;i<n;i++) output.put(c);
    output<<endl;
}

void leer_imprimir_companias(int &compania_mayor_infracciones,int &compania_menor_infracciones, double &pago_mayor,
                             double &pago_menor,ifstream &input_empresas,ifstream &input_infracciones,
                             ifstream &input_tabla,ofstream &output) {
    int cant_companias=1, DNI, cant_f_leves, cant_f_graves, cant_f_muy_graves;
    double pago_f_leves, pago_f_graves, pago_f_muy_graves, pago_total;
    compania_mayor_infracciones=0,compania_menor_infracciones=0;

    while (1) {
        input_empresas>>DNI;
        if (input_empresas.eof()) break;
        pago_total=0;
        imprimir_encabezado(cant_companias,DNI,input_empresas,output);
        leer_imprimir_vehiculos(cant_f_leves, cant_f_graves, cant_f_muy_graves,
                                pago_f_leves, pago_f_graves, pago_f_muy_graves,
                                input_empresas, input_infracciones, input_tabla, output);
        pago_total=pago_f_leves+pago_f_graves+pago_f_muy_graves;
        imprimir_resumen(cant_f_leves, cant_f_graves, cant_f_muy_graves, pago_total,
                         pago_f_muy_graves, pago_f_leves,pago_f_graves,output);
        if (pago_total>compania_mayor_infracciones) {
            compania_mayor_infracciones=DNI;
            pago_mayor=pago_total;
        }
        if (pago_total<compania_menor_infracciones or compania_menor_infracciones==0) {
            compania_menor_infracciones=DNI;
            pago_menor=pago_total;
        }
        cant_companias++;
    }

}

void imprimir_encabezado(int cant_companias,int DNI,ifstream &input_empresas,ofstream &output) {

    output<<"COMPANIA No. "<<cant_companias<<endl;
    output<<"REPRESENTANTE LEGAL:  ";
    imprimir_nombre(true,input_empresas,output);
    output<<"DNI: "<<DNI;
    output<<"    DISTRITO: ";
    imprimir_nombre(true,input_empresas,output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

void imprimir_nombre(bool camellizacion,ifstream &input,ofstream &output) {
    int espacios=0;
    bool mayus=true;
    char c;

    input>>ws;
    while (1) {
        input.get(c);
        if (camellizacion) {
            if (c==' ') break;
            if (mayus) {
                if (c>='a' and c<='z') {
                    c=a_mayuscula(c);
                }
                mayus=false;
            }
            if (c=='/' or c=='-' or c=='_') {
                c=' ';
                mayus=true;
            }
        } else {
            if (c=='\n') break;
        }
        espacios++;
        output.put(c);
    }
    if (camellizacion) {
        output<<setw(ANCHO_REPORTE/3 - espacios)<<"";
    } else {
        output<<endl;
    }
}

char a_mayuscula(char c) {
    return c - abs('a' - 'A');
}

void leer_imprimir_vehiculos(int &cant_f_leves,int &cant_f_graves,int &cant_f_muy_graves,
                             double &pago_f_leves,double &pago_f_graves,double &pago_f_muy_graves,
                             ifstream &input_empresas,ifstream &input_infracciones,ifstream &input_tabla,ofstream &output) {
    int cant_vehiculos=1, int1_placa, int2_placa;
    char c_placa,c;
    cant_f_leves=0, cant_f_graves=0, cant_f_muy_graves=0;
    pago_f_leves=0, pago_f_graves=0, pago_f_muy_graves=0;

    output<<"VEHICULOS INFRACCIONADOS: "<<endl;
    while (1) {
        input_empresas>>ws>>c_placa>>int1_placa>>c>>int2_placa;
        output<<"  "<<setw(2)<<setfill('0')<<cant_vehiculos<<setfill(' ')<<")  ";
        output<<"PLACA: "<<c_placa<<int1_placa<<"-"<<int2_placa<<setw(6)<<""<<"TIPO:  ";
        imprimir_tipo_vehivulo(c_placa, output);
        output<<endl;
        output<<setw(7)<<""<<"No.    "<<left<<setw(ANCHO_REPORTE/8)<<"FECHA";
        output<<setw(ANCHO_REPORTE/8)<<"INFRACCION"<<setw(ANCHO_REPORTE/8)<<"GRAVEDAD";
        output<<setw(ANCHO_REPORTE/8)<<"MULTA"<<right<<"DESCRIPCION"<<endl;
        buscar_infracciones(c_placa,int1_placa,int2_placa,
                        cant_f_leves, cant_f_graves, cant_f_muy_graves,
                        pago_f_leves, pago_f_graves, pago_f_muy_graves,
                        input_infracciones, input_tabla, output);
        input_empresas.get(c);
        if (c=='\n') break;
        cant_vehiculos++;
    }
}

void imprimir_tipo_vehivulo(char c, ofstream &output) {
    if (c=='P') output<<"PEQUEÑO";
    if (c=='M') output<<"MEDIANO";
    if (c=='G') output<<"GRANDE";
}

void buscar_infracciones(double c_placa, int int1_placa, int int2_placa,
                         int &cant_f_leves, int &cant_f_graves, int &cant_f_muy_graves,
                         double &monto_leves, double &monto_graves, double &monto_muy_graves, ifstream &input_infracciones, ifstream &input_tabla, ofstream &output) {
    int cant_infracciones=0, fecha, int1_placa_leido, int2_placa_leido,int_infraccion;
    char c, c_placa_leido, c_infraccion;
    input_infracciones.clear();
    input_infracciones.seekg(0,ios::beg);

    while (1) {
        fecha=leer_fecha(input_infracciones);
        if (input_infracciones.eof()) break;
        input_infracciones>>ws>>c_placa_leido>>int1_placa_leido>>c>>int2_placa_leido;
        if (c_placa_leido==c_placa and int1_placa_leido==int1_placa and
            int2_placa_leido==int2_placa) {
            input_infracciones>>ws>>c_infraccion>>int_infraccion;
            output<<setw(7)<<""<<setw(2)<<setfill('0')<<cant_infracciones+1<<setfill(' ')<<")    ";
            imprimir_fecha(fecha,output);
            output<<setw(ANCHO_REPORTE/8 - 10)<<""<<left<<setw(ANCHO_REPORTE/8)<<int_infraccion<<right;
            buscar_tipo_infraccion(c_infraccion, int_infraccion, cant_f_leves, cant_f_graves, cant_f_muy_graves,
                                monto_leves, monto_graves, monto_muy_graves,
                                input_tabla, output);
            cant_infracciones++;
        }
        input_infracciones.ignore(40,'\n');
    }
    imprimir_linea(ANCHO_REPORTE,'-',output);
}

int leer_fecha(ifstream &input) {
    int dd,mm,aa;
    char c;

    input>>dd>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void imprimir_fecha(int fecha,ofstream &output) {
    int dd,mm,aa;

    aa=fecha/10000;
    fecha=fecha%10000;
    mm=fecha/100;
    dd=fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void buscar_tipo_infraccion(char c_infraccion, int int_infraccion, int &cant_f_leves, int &cant_f_graves,
                            int &cant_f_muy_graves, double &monto_leves, double &monto_graves, double &monto_muy_graves,
                            ifstream &input_tabla, ofstream &output) {
    int int_infraccion_leido;
    char c_infraccion_leido;
    double multa;


    input_tabla.clear();
    input_tabla.seekg(0,ios::beg);
    while (1) {
        input_tabla>>c_infraccion_leido>>int_infraccion_leido;
        if (input_tabla.eof()) {
            output<<"No se encontro esa infraccion."<<endl;
            break;
        }
        if (c_infraccion==c_infraccion_leido and int_infraccion==int_infraccion_leido) {
            input_tabla>>ws>>multa;
            output<<fixed<<left;
            if (c_infraccion=='L') {
                output<<setw(ANCHO_REPORTE/8)<<"LEVE";
                cant_f_leves++;
                monto_leves+=multa;
            }
            if (c_infraccion=='G') {
                output<<setw(ANCHO_REPORTE/8)<<"GRAVE";
                cant_f_graves++;
                monto_graves+=multa;
            }
            if (c_infraccion=='M') {
                output<<setw(ANCHO_REPORTE/8)<<"MUY GRAVE";
                cant_f_muy_graves++;
                monto_muy_graves+=multa;
            }
            output<<setw(ANCHO_REPORTE/8)<<setprecision(2)<<multa<<right;
            imprimir_nombre(false,input_tabla,output);
            break;
        }
        input_tabla.ignore(180, '\n');
    }
}

void imprimir_resumen(int cant_f_leves,int cant_f_graves,int cant_f_muy_graves, double pago_total,
                      double pago_f_muy_graves,double pago_f_leves,double pago_f_graves,ofstream &output) {
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<fixed;
    output<<setw(18)<<""<<left<<setw(14)<<"CANTIDAD"<<setw(14)<<"MONTO PAGADO"<<right<<endl;
    output<<"FALTA LEVES:      "<<setw(5)<<cant_f_leves<<setw(9)<<""<<setw(9)<<setprecision(2)<<pago_f_leves<<endl;
    output<<"FALTA GRAVES:     "<<setw(5)<<cant_f_graves<<setw(9)<<""<<setw(9)<<setprecision(2)<<pago_f_graves<<endl;
    output<<"FALTA MUY GRAVES: "<<setw(5)<<cant_f_muy_graves<<setw(9)<<""<<setw(9)<<setprecision(2)<<pago_f_muy_graves<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<"PAGO TOTAL :      "<<setw(23)<<setprecision(2)<<pago_total<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_resumen_final(int compania_mayor_infracciones,int compania_menor_infracciones,
                            double pago_mayor,double pago_menor,ofstream &output) {

    output<<fixed;
    imprimir_linea(50,'+',output);
    output<<"+ "<<"COMPANIA CON MAYOR PAGO POR INFRACCIONES:      +"<<endl;
    output<<"+ "<<"DNI:              "<<setw(8)<<compania_mayor_infracciones<<setw(21)<<"+"<<endl;
    output<<"+ "<<"TOTAL PAGADO:     "<<setw(6)<<setprecision(2)<<pago_mayor<<setw(21)<<"+"<<endl;
    imprimir_linea(50,'+',output);
    output<<"+ "<<"COMPANIA CON MENOR PAGO POR INFRACCIONES:      +"<<endl;
    output<<"+ "<<"DNI:              "<<setw(8)<<compania_menor_infracciones<<setw(21)<<"+"<<endl;
    output<<"+ "<<"TOTAL PAGADO:     "<<setw(6)<<setprecision(2)<<pago_menor<<setw(21)<<"+"<<endl;
}