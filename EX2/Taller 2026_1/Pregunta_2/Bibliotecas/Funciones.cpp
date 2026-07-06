//
// Created by User on 6/07/2026.
//

#include "Funciones.hpp"


void insertar_ordenado_saldo(ListaClientes &lista_clientes, const Cliente & dato) {
    struct Nodo *nuevo_nodo;
    nuevo_nodo = new struct Nodo;
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = nullptr;

    struct Nodo *recorrido = lista_clientes.inicio, *anterior=nullptr;

    while (recorrido != nullptr) {
        if (nuevo_nodo->dato.saldoTotal > recorrido->dato.saldoTotal) break;
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }

    nuevo_nodo->siguiente = recorrido;
    if (anterior != nullptr) anterior->siguiente = nuevo_nodo;
    else lista_clientes.inicio = nuevo_nodo;
}

void crear_listas(ListaClientes &lista_clientes, ListaClientes &lista_saldos_positivos, ListaClientes &lista_saldos_negativos) {
    struct Nodo *recorrido=lista_clientes.inicio;
    inicializar_lista(lista_saldos_positivos);
    inicializar_lista(lista_saldos_negativos);

    while (recorrido != nullptr) {
        if (recorrido->dato.saldoTotal >= 0) insertar_ordenado_saldo(lista_saldos_positivos, recorrido->dato);
        if (recorrido->dato.saldoTotal < 0) insertar_ordenado_saldo(lista_saldos_negativos, recorrido->dato);
        recorrido = recorrido->siguiente;
    }
}


void buscar_cuenta(ListaClientes &lista_clientes, int &pos_cuenta, struct Nodo *& pos_cliente, int nroCuenta_leido) {
    struct Nodo *recorrido = lista_clientes.inicio;

    while (recorrido != nullptr) {
        for (int i = 0; i < recorrido->dato.cantidadCuentas; i++) {
            if (recorrido->dato.cuentas[i].nroCuenta == nroCuenta_leido) {
                pos_cliente = recorrido;
                pos_cuenta = i;
                return;
            }
        }
        recorrido = recorrido->siguiente;
    }
    pos_cliente = nullptr;
    pos_cuenta = -1;
}

void cargar_transacciones(const char * file_name, ListaClientes &lista_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int nroCuenta_leido, pos_cuenta;
    double monto;
    char tipo;
    struct Nodo *pos_cliente;
    while (true) {
        input>>nroCuenta_leido;
        if (input.eof()) break;
        input.ignore();
        buscar_cuenta(lista_clientes, pos_cuenta, pos_cliente, nroCuenta_leido);
        if (pos_cliente == nullptr or pos_cuenta == -1) {
            input.ignore(100, '\n');
            continue;
        }
        while (true) {
            input>>tipo;
            input.ignore();
            input>>monto;
            if (tipo == 'D') {
                pos_cliente->dato.cuentas[pos_cuenta].saldoFinal += monto;
                pos_cliente->dato.cuentas[pos_cuenta].cantidadDepositos++;
                pos_cliente->dato.saldoTotal += monto;
            }
            if (tipo == 'R') {
                pos_cliente->dato.cuentas[pos_cuenta].saldoFinal -= monto;
                pos_cliente->dato.cuentas[pos_cuenta].cantidadRetiros++;
                pos_cliente->dato.saldoTotal -= monto;
            }
            char estado1[]="HABILITADO", estado2[]="INHABILITADO";
            if (strcmp(pos_cliente->dato.cuentas[pos_cuenta].estado, estado1) != 0 and  pos_cliente->dato.cuentas[pos_cuenta].saldoFinal >= 0) {
                delete  [] pos_cliente->dato.cuentas[pos_cuenta].estado;
                pos_cliente->dato.cuentas[pos_cuenta].estado = asignar_candena(estado1);
                pos_cliente->dato.cantidadCuentasDeshabilitadas --;
                pos_cliente->dato.cantidadCuentasHabilitadas ++;
            } else if (strcmp(pos_cliente->dato.cuentas[pos_cuenta].estado, estado2) != 0 and  pos_cliente->dato.cuentas[pos_cuenta].saldoFinal < 0) {
                delete  [] pos_cliente->dato.cuentas[pos_cuenta].estado;
                pos_cliente->dato.cuentas[pos_cuenta].estado = asignar_candena(estado2);
                pos_cliente->dato.cantidadCuentasDeshabilitadas ++;
                pos_cliente->dato.cantidadCuentasHabilitadas --;
            }
            if (input.get()=='\n') break;
        }
    }
    input.close();
}


struct Nodo * buscar_posicion_cliente(ListaClientes &lista_clientes, int dni) {
    struct Nodo *recorrido = lista_clientes.inicio;
    while (recorrido != nullptr) {
        if (recorrido->dato.dni == dni) return recorrido;
        recorrido = recorrido->siguiente;
    }
    return nullptr;
}

int leer_int( ifstream & input) {
    int dato;
    input >> dato;
    input.ignore();
    return dato;
}

double leer_double( ifstream & input) {
    double dato;
    input >> dato;
    input.ignore();
    return dato;
}

void cargar_cuentas(const char * file_name, ListaClientes &lista_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);

    int dni;
    struct Nodo *pos_cliente;
    while (true) {
        input>>dni;
        if (input.eof()) break;
        input.ignore();
        pos_cliente = buscar_posicion_cliente(lista_clientes, dni);
        if (pos_cliente == nullptr) {
            input.ignore(60, '\n');
            continue;
        }
        int n = pos_cliente->dato.cantidadCuentas;
        pos_cliente->dato.cuentas[n].nroCuenta = leer_int(input);
        pos_cliente->dato.cuentas[n].saldoInicial = leer_double(input);
        pos_cliente->dato.cuentas[n].saldoFinal = pos_cliente->dato.cuentas[n].saldoInicial;
        pos_cliente->dato.saldoTotal += pos_cliente->dato.cuentas[n].saldoFinal;
        char estado1[]="HABILITADO", estado2[]="INHABILITADO";
        if (pos_cliente->dato.cuentas[n].saldoFinal >= 0) {
            pos_cliente->dato.cantidadCuentasHabilitadas ++;
            pos_cliente->dato.cuentas[n].estado = asignar_candena(estado1);
        }
        else {
            pos_cliente->dato.cantidadCuentasDeshabilitadas ++;
            pos_cliente->dato.cuentas[n].estado = asignar_candena(estado2);
        }
        pos_cliente->dato.cantidadCuentas++;
    }
    input.close();
}

void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir archivo: "<<file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void centrear(const char * texto, int espacio, bool slash_n, ofstream & output) {
    int n = strlen(texto);
    output << setw((espacio + n)/ 2) << texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', slash_n, output);
}

void imprimir_titulos_encabezado(ofstream &output) {
    centrear("DNI", 15, false, output);
    centrear("NOMBRE", 40, false, output);
    centrear("TIPO CLIENTE", 16, false, output);
    centrear("CANT. CUENTAS", 15, false, output);
    centrear("SALDO TOTAL", 15, false, output);
    centrear("CANT. CUENTAS HAB.", 22, false, output);
    centrear("CANT. CUENTAS DESHAB.", 25, false, output);
    output<<endl;
}

void imprimir_cuenta(const Cuenta & cuenta, ofstream & output) {
    imprimir_linea(4,' ',false, output);
    output<<cuenta.nroCuenta<<setw(14)<<cuenta.saldoInicial;
    imprimir_linea(10,' ',false, output);
    output<<left<<setw(15)<<cuenta.estado<<right<<setw(6)<<cuenta.cantidadDepositos;
    output<<setw(15)<<cuenta.cantidadRetiros<<setw(15)<<cuenta.cantidadDepositos + cuenta.cantidadRetiros;
    output<<setw(20)<<cuenta.saldoFinal<<endl;
}

void imprimir_encabezado(const Cliente & dato, ofstream & output) {
    imprimir_titulos_encabezado(output);
    imprimir_linea(4,' ',false, output);
    output<<left<<setw(11)<<dato.dni;
    output<<setw(40)<<dato.nombre<<right;
    output<<setw(8)<<dato.tipoCliente<<setw(15)<<dato.cantidadCuentas;
    output<<setw(18)<<dato.saldoTotal<<setw(16)<<dato.cantidadCuentasHabilitadas;
    output<<setw(24)<<dato.cantidadCuentasDeshabilitadas<<endl;
}

void imprimir_info_cuentas(const Cliente & dato, ofstream & output) {

    if (dato.cantidadCuentas>0) {
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        centrear("CUENTA", 15, false, output);
        centrear("SALDO INICIAL", 20, false, output);
        centrear("ESTADO", 15, false, output);
        centrear("CANT. DEP.", 15, false, output);
        centrear("CANT. RET,", 15, false, output);
        centrear("CANT. TRAN.", 15, false, output);
        centrear("SALDO FINAL", 20, false, output);
        output<<endl;
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        for (int i = 0; i < dato.cantidadCuentas; i++) {
            imprimir_cuenta(dato.cuentas[i], output);
        }
    }
}

void imprimir_reporte(const char * file_name, const char * titulo, ListaClientes &lista_clientes) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output.precision(2);

    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    centrear(titulo, ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    struct Nodo *recorrido = lista_clientes.inicio;
    while (recorrido != nullptr) {
        imprimir_encabezado(recorrido->dato, output);
        imprimir_info_cuentas(recorrido->dato, output);
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
        recorrido = recorrido->siguiente;
    }
    output.close();
}


void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo: "<< file_name << endl;
        exit(1);
    }
}

char * asignar_candena(char * origen) {
    char *cadena;
    cadena = new char[strlen(origen)+1];
    strcpy(cadena, origen);
    return cadena;
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[50]{};
    input.getline(buffer, 50, del);
    return asignar_candena(buffer);
}

char * extraer_nombre( ifstream & input) {
    //RICHARD HENRRY ALONSO,PRADO,LAURA,
    char *nombre, *apellido_paterno, *apellido_materno, nombre_completo[60]{};
    nombre = leer_cadena(input, ',');
    apellido_paterno = leer_cadena(input, ',');
    apellido_materno = leer_cadena(input, ',');
    strcpy(nombre_completo, apellido_paterno);
    strcat(nombre_completo, "/");
    strcat(nombre_completo, apellido_materno);
    strcat(nombre_completo, "/");
    strcat(nombre_completo, nombre);
    delete [] nombre;
    delete [] apellido_paterno;
    delete [] apellido_materno;
    return asignar_candena(nombre_completo);
}

void asignar_struct_Cliente(Cliente & dato, const struct Cliente & cliente) {
    dato.dni = cliente.dni;
    dato.nombre = asignar_candena(cliente.nombre);
    dato.tipoCliente = cliente.tipoCliente;
    dato.cantidadCuentas = 0;
    dato.cantidadCuentasDeshabilitadas = 0;
    dato.cantidadCuentasHabilitadas=0;
    dato.saldoTotal = 0;
    dato.cuentas = new Cuenta[MAX_CUENTAS]{};
}

void insertar_ordenado(ListaClientes &lista_clientes, const struct Cliente & c) {
    struct Nodo *nuevo_nodo;
    nuevo_nodo = new struct Nodo;
    asignar_struct_Cliente(nuevo_nodo->dato, c);
    nuevo_nodo->siguiente = nullptr;

    struct Nodo *recorrido = lista_clientes.inicio, *anterior=nullptr;

    while (recorrido != nullptr) {
        if (nuevo_nodo->dato.dni < recorrido->dato.dni) break;
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }

    nuevo_nodo->siguiente = recorrido;
    if (anterior != nullptr) anterior->siguiente = nuevo_nodo;
    else lista_clientes.inicio = nuevo_nodo;
}

void inicializar_lista(ListaClientes &lista_clientes) {
    lista_clientes.inicio = nullptr;
}

void modificar_cadena(char *cadena) {
    bool mayus=true;

    for (int i = 0; cadena[i]; i++) {
        if (cadena[i]>='A' and cadena[i]<='Z') {
            if (not mayus) cadena[i]=tolower(cadena[i]);
            mayus = false;
        } else mayus = true;
    }
}

void cargar_clientes(const char * file_name, ListaClientes &lista_clientes) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    inicializar_lista(lista_clientes);

    int dni;
    while (true) {
        //19996544,RICHARD HENRRY ALONSO,PRADO,LAURA,A
        input>>dni;
        if (input.eof()) break;
        input.ignore();
        struct Cliente c{};
        c.nombre = extraer_nombre(input);
        modificar_cadena(c.nombre);
        input>>c.tipoCliente;
        c.dni = dni;
        insertar_ordenado(lista_clientes, c);
    }
    input.close();
}
