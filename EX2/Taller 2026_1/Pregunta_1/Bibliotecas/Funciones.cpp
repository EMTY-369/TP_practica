//
// Created by User on 5/07/2026.
//

#include "Funciones.hpp"

void swap_struct_cuenta( struct Cuenta & a, struct Cuenta & b) {
    Cuenta aux = a;
    a = b;
    b = aux;
}

void ordenar_cuentas( Cliente & cliente) {
    for (int i = 0; i < cliente.cantidad_cuentas-1; i++) {
        for (int j = i; j < cliente.cantidad_cuentas; j++) {
           if (cliente.cuentas[i].cantidadRetiros < cliente.cuentas[j].cantidadRetiros or
               (cliente.cuentas[i].cantidadRetiros == cliente.cuentas[j].cantidadRetiros and
                   cliente.cuentas[i].cantidadDepositos > cliente.cuentas[j].cantidadDepositos)) {
               swap_struct_cuenta(cliente.cuentas[i], cliente.cuentas[j]);
           }
        }
    }
}

void swap_struct_cliente( Cliente & a, Cliente & b) {
    Cliente aux = a;
    a = b;
    b = aux;
}

void ordenar_clientes(Cliente *& cliente, int n_clientes) {
    for (int i = 0; i < n_clientes - 1; i++) {
        for (int j = i; j < n_clientes; j++) {
            if (strcmp(cliente[i].nombre, cliente[j].nombre)>0) {
                ordenar_cuentas(cliente[j]);
                swap_struct_cliente(cliente[i], cliente[j]);
            } else ordenar_cuentas(cliente[i]);
        }
    }
}


void buscar_cliente_cuenta(Cliente *&cliente, int n_clientes, int num_cuenta_leido, int &pos_cliente, int &pos_cuenta) {
    for (int i = 0; i < n_clientes; i++) {
        for (int j = 0; j < cliente[i].cantidad_cuentas; j++) {
            if (cliente[i].cuentas[j].nroCuenta == num_cuenta_leido) {
                pos_cliente = i;
                pos_cuenta = j;
                return;
            }
        }
    }
    pos_cliente = -1;
    pos_cuenta = -1;
}

void cargar_transacciones(const char * file_name, Cliente *&cliente, int n_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int num_cuenta_leido, pos_cliente, pos_cuenta;
    double monto;
    char tipo_operacion;
    while (true) {
        input>>num_cuenta_leido;
        if (input.eof()) break;
        input.ignore();
        buscar_cliente_cuenta(cliente, n_clientes, num_cuenta_leido, pos_cliente, pos_cuenta);
        if (pos_cliente == -1 or pos_cuenta == -1) {
            input.ignore(120, '\n');
            continue;
        }
        while (true) {
            input>>tipo_operacion;
            input.ignore();
            input>>monto;
            int n = cliente[pos_cliente].cuentas[pos_cuenta].cantidadTransacciones;
            cliente[pos_cliente].cuentas[pos_cuenta].transacciones[n].monto = monto;
            cliente[pos_cliente].cuentas[pos_cuenta].transacciones[n].tipoTransaccion = tipo_operacion;
            if (tipo_operacion == 'D') {
                cliente[pos_cliente].cuentas[pos_cuenta].cantidadDepositos++;
                cliente[pos_cliente].cuentas[pos_cuenta].saldoFinal += monto;
            }
            if (tipo_operacion == 'R') {
                cliente[pos_cliente].cuentas[pos_cuenta].cantidadRetiros ++;
                cliente[pos_cliente].cuentas[pos_cuenta].saldoFinal -= monto;
            }
            char estado1[]="HABILITADO", estado2[]="INHABILITADO";
            delete cliente[pos_cliente].cuentas[pos_cuenta].estado;
            if (cliente[pos_cliente].cuentas[pos_cuenta].saldoFinal>=0) cliente[pos_cliente].cuentas[pos_cuenta].estado = asignar_cadena(estado1);
            else cliente[pos_cliente].cuentas[pos_cuenta].estado = asignar_cadena(estado2);
            cliente[pos_cliente].cuentas[pos_cuenta].cantidadTransacciones++;
            if (input.get()=='\n') break;
        }
    }
}


int leer_int( ifstream & input) {
    int dato;
    input>>dato;
    input.ignore();
    return dato;
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.ignore();
    return dato;
}

int buscar_cliente(Cliente *& cliente, int n_clientes, int dni_leido) {
    for (int i = 0; i < n_clientes; i++) {
        if (cliente[i].dni == dni_leido) return i;
    }
    return -1;
}

void cargar_cuentas(const char * file_name, Cliente *&cliente, int n_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dni_leido, num_cuenta, pos_cliente;
    double saldo;
    while (true) {
        input>>dni_leido;
        if (input.eof()) break;
        input.ignore();
        num_cuenta = leer_int(input);
        saldo = leer_double(input);
        pos_cliente = buscar_cliente(cliente, n_clientes, dni_leido);
        if (pos_cliente != -1) {
            int n = cliente[pos_cliente].cantidad_cuentas;
            cliente[pos_cliente].cuentas[n].nroCuenta = num_cuenta;
            cliente[pos_cliente].cuentas[n].saldoInicial = saldo;
            cliente[pos_cliente].cuentas[n].saldoFinal = saldo;
            char estado1[]="HABILITADO", estado2[]="INHABILITADO";
            if (saldo>=0) cliente[pos_cliente].cuentas[n].estado = asignar_cadena(estado1);
            else cliente[pos_cliente].cuentas[n].estado = asignar_cadena(estado2);
            cliente[pos_cliente].cuentas[n].transacciones = new Transaccion[MAX_TRANSACCIONES]{};
            cliente[pos_cliente].cantidad_cuentas++;
        }
    }
}


void imprimir_encabezado(const Cliente & cliente, ofstream & output) {
    centrear("DNI", 15, false, output);
    centrear("NOMBRE", 50, false, output);
    centrear("TIPO - CLIENTE", 30, false, output);
    centrear("CANTIDAD DE CUENTAS", 25, false, output);
    output<<endl;
    imprimir_linea(3, ' ', false, output);
    output<<left<<setw(12)<<cliente.dni<<setw(50)<<cliente.nombre;
    output<<cliente.tipo_cliente.tipo<<"  -  "<<setw(24)<<cliente.tipo_cliente.descripcion<<right;
    output<<setw(14)<<cliente.cantidad_cuentas<<endl;
}

void imprimir_encabezado2( ofstream & output) {
    centrear("CUENTA", 15, false, output);
    centrear("SALDO INICIAL", 20, false, output);
    centrear("ESTADO", 15, false, output);
    centrear("CANT. DEP", 15, false, output);
    centrear("CANT. RET", 15, false, output);
    centrear("CANT. TRAN", 15, false, output);
    centrear("SALDO FINAL", 20, false, output);
    output<<endl;
}

void imprimir_transacciones(const struct Cuenta & cuenta, ofstream & output) {
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < cuenta.cantidadTransacciones; i++) {
        output<<setw(10)<<cuenta.transacciones[i].tipoTransaccion;
        output<<setw(16)<<cuenta.transacciones[i].monto<<endl;
    }
}

void imprimir_cuentas(const Cliente & cliente, ofstream & output) {
    for (int i = 0; i < cliente.cantidad_cuentas; i++) {
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        imprimir_encabezado2(output);
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        imprimir_linea(3, ' ', false, output);
        output<<left<<setw(17)<<cliente.cuentas[i].nroCuenta<<setw(17)<<cliente.cuentas[i].saldoInicial;
        output<<setw(12)<<cliente.cuentas[i].estado<<right;
        output<<setw(8)<<cliente.cuentas[i].cantidadDepositos<<setw(15)<<cliente.cuentas[i].cantidadRetiros;
        output<<setw(15)<<cliente.cuentas[i].cantidadTransacciones<<setw(22)<<cliente.cuentas[i].saldoFinal<<endl;
        output<<"   Transacciones"<<endl;
        if (cliente.cuentas[i].cantidadTransacciones >0) imprimir_transacciones(cliente.cuentas[i], output);
    }
}

void imprimir_reporte(const char * file_name, Cliente *&cliente, int n_clientes) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output.precision(2);

    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    centrear("LISTADO DE CLIENTES", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    for (int i = 0; i < n_clientes; i++) {
        imprimir_encabezado(cliente[i], output);
        if (cliente[i].cantidad_cuentas>0) imprimir_cuentas(cliente[i], output);
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
    }
    output.close();
}

char *extraer_nombre(ifstream &input) {
    char nombre_completo[50]{}, *palabra1, *palabra2, *palabra3;
    palabra1 = leer_candena(input, ',');
    palabra2 = leer_candena(input, ',');
    palabra3 = leer_candena(input, ',');
    strcpy(nombre_completo, palabra2);
    strcat(nombre_completo, "/");
    strcat(nombre_completo, palabra3);
    strcat(nombre_completo, "/");
    strcat(nombre_completo, palabra1);
    delete palabra1;
    delete palabra2;
    delete palabra3;
    return asignar_cadena(nombre_completo);
}

int buscar_tipo_cliente(char tipo_leido, TipoCliente *& arr_tipos_clientes, int n_tipos_clientes) {
    for (int i = 0; i < n_tipos_clientes; i++) {
        if (tipo_leido == arr_tipos_clientes[i].tipo) return i;
    }
    return (-1);
}

void camelizar(char * cadena) {
    bool mayus= true;

    for (int i = 0; cadena[i]; i++) {
        if (cadena[i]>='A' and cadena[i]<='Z') {
            if (not mayus)cadena[i] = tolower(cadena[i]);
            mayus = false;
        } else mayus = true;
    }
}

void cargar_clientes(const char * file_name, Cliente *&arr_clientes, int &n_clientes, TipoCliente *&arr_tipos_clientes, int n_tipos_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    arr_clientes = new Cliente[80]{};

    int id, pos_tipo;
    char tipo_leido;
    while (true) {
        input>>id;
        if (input.eof()) break;
        input.ignore();
        arr_clientes[n_clientes].dni = id;
        arr_clientes[n_clientes].nombre = extraer_nombre(input);
        camelizar(arr_clientes[n_clientes].nombre);
        input>>tipo_leido;
        pos_tipo = buscar_tipo_cliente(tipo_leido, arr_tipos_clientes,n_tipos_clientes);
        if (pos_tipo != -1) arr_clientes[n_clientes].tipo_cliente = arr_tipos_clientes[pos_tipo];
        arr_clientes[n_clientes].cuentas = new struct Cuenta[MAX_CUENTAS]{};
        arr_clientes[n_clientes].cantidad_cuentas = 0;
        n_clientes++;
    }
    input.close();
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura: "<< file_name << endl;
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void centrear(const char * texto, int espacio, bool slash_n, ofstream & output){
    int n = strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', slash_n, output);
}

void prueba_carga_tipos_cliente(const char * file_name, TipoCliente *&arr_tipos_clientes, int n_tipos_clientes) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    centrear("PRUEBA DE CARGA DE LOS TIPOS DE CLIENTE", 60, true, output);
    imprimir_linea(60, '=', true, output);
    output<<left<<setw(20)<<"TIPO DE CLIENTE"<<setw(40)<<"DESCRIPCION"<<endl<<right;
    for (int i = 0; i < n_tipos_clientes; i++) {
        output<<left<<setw(20)<<arr_tipos_clientes[i].tipo;
        output<<setw(40)<<arr_tipos_clientes[i].descripcion<<endl<<right;
    }
    output.close();
}


void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: "<< file_name << endl;
        exit(1);
    }
}

char * asignar_cadena(char * origin) {
    char *cadena;
    cadena = new char[strlen(origin)+1];
    strcpy(cadena, origin);
    return cadena;
}

char * leer_candena( ifstream & input, char del){
    char buffer[50]{};
    input.getline(buffer, 50, del);
    return asignar_cadena(buffer);
}

void cargar_tipos_cliente(const char * file_name, TipoCliente *&arr_tipos_clientes, int &n_tipos_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    arr_tipos_clientes = new TipoCliente[6]{};
    char tipo, *descripcion;
    while (true) {
        input>>tipo;
        if (input.eof()) break;
        input>>ws;
        descripcion = leer_candena(input, '\n');
        arr_tipos_clientes[n_tipos_clientes].tipo = tipo;
        arr_tipos_clientes[n_tipos_clientes].descripcion = descripcion;
        n_tipos_clientes++;
    }
    input.close();
}
