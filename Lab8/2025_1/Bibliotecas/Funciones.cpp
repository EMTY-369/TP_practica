//
// Created by User on 14/06/2026.
//

#include "Funciones.hpp"

void abrir_archivo_salida(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo de salida: "<<file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void encuadrar(const char * texto, int espacio, bool slash_n, ofstream & output) {
    int n = strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', slash_n, output);
}

void imprimir_titulo_encabezado1( ofstream & output) {
    encuadrar("MINISTERIO DE TRANSPORTES",ANCHO_REPORTE, true, output);
    encuadrar("LISTADO DE INFRACCIONES POR EMPRESA",ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    imprimir_linea(5,' ',false, output);
    encuadrar("EMPRESA",14+40+35+55, false, output);
    encuadrar("FECHA INF.",14, false, output);
    encuadrar("FECHA PAGO",14, false, output);
    imprimir_linea(28,' ',false, output);
    encuadrar("CANTIDAD",10, false, output);
    output<<endl;
    encuadrar("No.",5, false, output);
    output<<left<<setw(14)<<"DNI"<<setw(40)<<"NOMBRE"<<setw(35)<<"DISTRITO"<<setw(55)<<"   PLACAS"<<right;
    encuadrar("MAS ANTIGUA",14, false, output);
    encuadrar("MAS RECIENTE",14, false, output);
    encuadrar("TOTAL PAGADO",14, false, output);
    encuadrar("TOTAL DEUDA",14, false, output);
    encuadrar("DE FALTAS",10, false, output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
}

void imprimir_fecha(int aa, int mm, int dd, ofstream & output) {
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(2)<<aa<<setfill(' ');
}

void imprimir_reporte(const char * file_name, EmpresasRegistradas * empresas_registradas, int n_empresas,
                      TablaDeInfracciones * tabla_de_infracciones, int n_infrac) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    output<<fixed;
    output<<setprecision(2);

    imprimir_titulo_encabezado1(output);
    double suma_pago=0, suma_deuda=0;
    int suma_faltas=0;
    for (int i = 0; i < n_empresas; i++) {
        output<<setw(2)<<i+1<<")  "<<left<<setw(14)<<empresas_registradas[i].dni<<setw(40)<<empresas_registradas[i].nombre;
        output<<setw(35)<<empresas_registradas[i].distrito<<right;
        for (int j = 0; j < empresas_registradas[i].numPlacas; j++) {
            if (j!=0) output<<"/";
            output<<empresas_registradas[i].placas[j];
        }
        imprimir_linea(55 - empresas_registradas[i].numPlacas*9,' ',false, output);
        imprimir_linea(2,' ',false, output);
        imprimir_fecha(empresas_registradas[i].fechaDeInfraccion.aa, empresas_registradas[i].fechaDeInfraccion.mm,
                       empresas_registradas[i].fechaDeInfraccion.dd, output);
        imprimir_linea(4,' ',false, output);
        imprimir_fecha(empresas_registradas[i].fechaDePago.aa, empresas_registradas[i].fechaDePago.mm,
                       empresas_registradas[i].fechaDePago.dd, output);
        imprimir_linea(2,' ',false, output);
        output<<setw(12)<<empresas_registradas[i].totalPagado<<setw(14)<<empresas_registradas[i].totalAdeudado;
        output<<setw(8)<<empresas_registradas[i].cantidadDeFaltas<<endl;
        suma_pago+=empresas_registradas[i].totalPagado;
        suma_deuda+=empresas_registradas[i].totalAdeudado;
        suma_faltas+=empresas_registradas[i].cantidadDeFaltas;
    }
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<setw(ANCHO_REPORTE - 38)<<"TOTALES:  "<<setw(12)<<suma_pago<<setw(14)<<suma_deuda<<setw(8)<<suma_faltas<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    encuadrar("TABLA DE INFRACCIONES", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    imprimir_linea(20, ' ', false, output);
    output<<left<<setw(10)<<"CODIGO"<<setw(10)<<"MULTA"<<"DESCRIPCION"<<right<<endl;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    for (int i = 0; i < n_infrac; i++) {
        imprimir_linea(20, ' ', false, output);
        output<<left<<setw(10)<<tabla_de_infracciones[i].codigo<<setw(10)<<tabla_de_infracciones[i].multa<<tabla_de_infracciones[i].descripcion<<endl<<right;
    }
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
}

void swap_struct_infrac( TablaDeInfracciones & a, TablaDeInfracciones & b) {
    TablaDeInfracciones aux = a;
    a = b;
    b = aux;
}

void ordenar_infracciones(TablaDeInfracciones * tabla_de_infracciones, int n_infrac) {
    for (int i = 0; i < n_infrac-1; i++) {
        for (int j = i+1; j < n_infrac; j++) {
            if (strcmp(tabla_de_infracciones[i].codigo, tabla_de_infracciones[j].codigo)<0) {
                swap_struct_infrac(tabla_de_infracciones[i], tabla_de_infracciones[j]);
            }
        }
    }
}

void swap_struct( EmpresasRegistradas & a,  EmpresasRegistradas & b) {
    EmpresasRegistradas aux = a;
    a = b;
    b = aux;
}

void ordenar_empresas(EmpresasRegistradas * empresas_registradas, int n_empresas) {
    for (int i = 0; i < n_empresas-1; i++) {
        for (int j = i+1; j < n_empresas; j++) {
            int fecha_i=empresas_registradas[i].fechaDeInfraccion.aa*10000+empresas_registradas[i].fechaDeInfraccion.mm*100+empresas_registradas[i].fechaDeInfraccion.dd,
            fecha_j=empresas_registradas[j].fechaDeInfraccion.aa*10000+empresas_registradas[j].fechaDeInfraccion.mm*100+empresas_registradas[j].fechaDeInfraccion.dd;
            if (strcmp(empresas_registradas[i].distrito,empresas_registradas[j].distrito)>0 or
                (strcmp(empresas_registradas[i].distrito,empresas_registradas[j].distrito)==0 and fecha_i<fecha_j)) {
                swap_struct(empresas_registradas[i], empresas_registradas[j]);
            }
        }
    }
}

int buscar_empresa_placa(char * placa_leida, EmpresasRegistradas * empresas_registradas, int n_empresas) {
    for (int i = 0; i < n_empresas; i++) {
        for (int j = 0; j < empresas_registradas[i].numPlacas; j++) {
            if (strcmp(empresas_registradas[i].placas[j], placa_leida) == 0) return  i;
        }
    }
    return NO_ENCONTRADO;
}

int buscar_infraccion(char * codigo_infrac, TablaDeInfracciones * tabla_de_infracciones, int n_infrac) {
    for (int i = 0; i < n_infrac; i++) {
        if (strcmp(tabla_de_infracciones[i].codigo, codigo_infrac)==0) return i;
    }
    return NO_ENCONTRADO;
}

void actualizar_datos(EmpresasRegistradas & empresa, TablaDeInfracciones &infraccion, int aa, int mm, int dd, ifstream &input) {
    char c;
    int fecha_leida=aa*10000+mm*100+dd,
        fecha_infrac = empresa.fechaDeInfraccion.aa*10000+empresa.fechaDeInfraccion.mm*100+empresa.fechaDeInfraccion.dd,
        fecha_pago = empresa.fechaDePago.aa*10000 + empresa.fechaDePago.mm*100 + empresa.fechaDePago.dd;
    if (empresa.cantidadDeFaltas==0 or (fecha_infrac > fecha_leida)) {
        empresa.fechaDeInfraccion.aa=aa;
        empresa.fechaDeInfraccion.mm=mm;
        empresa.fechaDeInfraccion.dd=dd;
    }
    empresa.totalDeMultas += infraccion.multa;
    if (input.get() == 'P') {
        input>>c>>dd>>c>>mm>>c>>aa;
        fecha_leida=aa*10000+mm*100+dd;
        if (empresa.totalPagado==0 or (fecha_pago<fecha_leida)) {
            empresa.fechaDePago.aa=aa;
            empresa.fechaDePago.mm=mm;
            empresa.fechaDePago.dd=dd;
        }
        empresa.totalPagado+=infraccion.multa;
    } else {
        empresa.totalAdeudado+=infraccion.multa;
    }
    empresa.cantidadDeFaltas++;
}

void cargar_infracciones_cometidas(const char * file_name, EmpresasRegistradas *empresas_registradas, int n_empresas, TablaDeInfracciones *
                                   tabla_de_infracciones, int n_infrac) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    int fecha_leida, dd, mm, aa, pos_empresa, pos_infrac;
    char c, *placa_leida, *codigo_infrac;
    while (true) {
        input>>dd;
        if (input.eof()) break;
        input>>c>>mm>>c>>aa>>c;
        placa_leida = leer_candena(input, ',');
        codigo_infrac = leer_candena(input, ',');
        pos_empresa = buscar_empresa_placa(placa_leida,empresas_registradas, n_empresas);
        pos_infrac = buscar_infraccion(codigo_infrac ,tabla_de_infracciones, n_infrac);
        if (pos_empresa==NO_ENCONTRADO or pos_infrac==NO_ENCONTRADO) {
            input.ignore(50, '\n');
            cout<<"1"<<endl;
            continue;
        }
        actualizar_datos(empresas_registradas[pos_empresa],tabla_de_infracciones[pos_infrac],aa,mm,dd, input);
    }
    input.close();
}

int buscar_empresa(EmpresasRegistradas * empresas_registradas, int dni, int n_empresas) {
    for (int i = 0; i < n_empresas; i++) {
        if (empresas_registradas[i].dni == dni) return i;
    }
    return NO_ENCONTRADO;
}

void cargar_placas_registradas(const char * file_name, EmpresasRegistradas * empresas_registradas, int n_empresas) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    int dni,pos_empresa;
    while (true) {
        input>>dni;
        if (input.eof()) break;
        input.ignore();
        pos_empresa = buscar_empresa(empresas_registradas, dni, n_empresas);
        if (pos_empresa == NO_ENCONTRADO) {
            input.ignore(200, '\n');
            continue;
        }
        int n = empresas_registradas[pos_empresa].numPlacas;
        empresas_registradas[pos_empresa].placas[n] = leer_candena(input, '\n');
        empresas_registradas[pos_empresa].numPlacas ++;
    }
    input.close();
}

void modificar_cadena(char * cadena) {

    for (int i = 0; cadena[i]; i++) {
        if (cadena[i]>='a' and cadena[i]<='z') cadena[i] -= 'a' - 'A';
    }
}

void cargar_empresas_registradas(const char * file_name, EmpresasRegistradas * empresas_registradas, int &n_empresas) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    int dni;
    while (true) {
        input>>dni;
        if (input.eof()) break;
        input.ignore();
        empresas_registradas[n_empresas].nombre = leer_candena(input, ',');
        modificar_cadena(empresas_registradas[n_empresas].nombre);
        empresas_registradas[n_empresas].distrito = leer_candena(input, '\n');
        modificar_cadena(empresas_registradas[n_empresas].distrito);
        empresas_registradas[n_empresas].dni = dni;
        n_empresas++;
    }
    input.close();
}

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada:" << file_name << endl;
        exit(1);
    }
}


char * leer_candena( ifstream & input, char del) {
    char buffer[MAX_CADENA]{}, *cadena;
    input>>ws;
    input.getline(buffer,MAX_CADENA, del);
    if (input.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.ignore();
    return dato;
}

void cargar_tabla_infracciones(const char * file_name, TablaDeInfracciones * tabla_de_infracciones, int &n_infrac) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    char* codigo;
    while (true) {
        codigo = leer_candena(input,',');
        if (codigo == nullptr or input.eof()) break;
        tabla_de_infracciones[n_infrac].multa = leer_double(input);
        tabla_de_infracciones[n_infrac].descripcion = leer_candena(input, '\n');
        modificar_cadena(tabla_de_infracciones[n_infrac].descripcion);
        tabla_de_infracciones[n_infrac].codigo = codigo;
        n_infrac++;
    }
    input.close();
}
