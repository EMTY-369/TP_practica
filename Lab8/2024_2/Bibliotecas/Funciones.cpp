//
// Created by User on 15/06/2026.
//

#include "Funciones.hpp"

void imprimir_titulo( ofstream & output) {
    centrear("EMPRESA DE REPARTOS A DOMICILIO TP S. A.", ANCHO_REPORTE, true, output);
    centrear("RELACION DE PEDIDOS POR CLIENTE", ANCHO_REPORTE, true, output);
}

void imprimir_encabezado(int i, const Cliente & cliente, ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'=',true,output);
    output<<"CLIENTE No. "<<setfill('0')<<setw(3)<<i+1<<setfill(' ')<<endl;
    output<<left<<setw(14)<<"DNI"<<setw(35)<<"NOMBRE"<<setw(40)<<"DISTRITO"<<"PAGO TOTAL"<<endl;
    output<<setw(14)<<cliente.dni<<setw(35)<<cliente.nombre<<setw(10)<<cliente.distrito.codigo<<setw(30)<<cliente.distrito.nombre;
    output<<setw(10)<<cliente.montoTotal<<right<<endl;
    imprimir_linea(ANCHO_REPORTE,'-',true,output);
    imprimir_linea(14,' ',false,output);
    output<<"PEDIDOS REALIZADOS: "<<endl;
    imprimir_linea(14,' ',false,output);
    output<<left<<setw(6)<<"NO. "<<setw(10)<<"PEDIDO"<<setw(12)<<"CODIGO"<<setw(50)<<"DESCRIPCION";
    output<<setw(15)<<"CATEGORIA"<<setw(10)<<"PRECIO"<<setw(10)<<"CANTIDAD"<<setw(10)<<"SUBTOTAL"<<endl<<right;
}

void imprimir_reporte(const char * file_name, Cliente * arr_clientes, int n_clientes, Plato *arr_platos, int n_platos) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    output<<fixed;
    output<<setprecision(2);

    imprimir_titulo(output);
    for (int i = 0; i < n_clientes; i++) {
        imprimir_encabezado(i, arr_clientes[i], output);
        cout<<i<<endl;
        for (int j = 0; j < arr_clientes[i].cantidadDePedidos; j++) {
            imprimir_linea(14,' ',false,output);
            output<<setw(3)<<j+1<<")  "<<left<<setw(10)<<arr_clientes[i].pedidos[j].codigoPedido;
            output<<setw(12)<<arr_clientes[i].pedidos[j].codigoPlato<<setw(50)<<arr_clientes[i].pedidos[j].descripcion;
            int pos_plato = buscar_plato(arr_platos, arr_clientes[i].pedidos[j].codigoPlato, n_platos);
            output<<setw(15)<<arr_platos[pos_plato].categoria<<right;
            output<<setw(6)<<arr_clientes[i].pedidos[j].precio<<setw(9)<<arr_clientes[i].pedidos[j].cantidad;
            output<<setw(12)<<arr_clientes[i].pedidos[j].subtotal<<endl;
        }
    }
}

void swap_struc_pedidos( PlatoPedido & a, PlatoPedido & b) {
    PlatoPedido aux = a;
    a = b;
    b = aux;
}

void ordenar_platos_pedidos(Cliente * arr_clientes, int n_clientes) {
    for (int i = 0; i < n_clientes; i++) {

        for (int j = 0; j < arr_clientes[i].cantidadDePedidos+1; j++) {
            for (int k = j+1; k < arr_clientes[i].cantidadDePedidos; k++) {
                if (arr_clientes[i].pedidos[j].codigoPedido > arr_clientes[i].pedidos[k].codigoPedido or
                    (arr_clientes[i].pedidos[j].codigoPedido == arr_clientes[i].pedidos[k].codigoPedido and
                    strcmp(arr_clientes[i].pedidos[j].codigoPlato, arr_clientes[i].pedidos[k].codigoPlato) > 0)) {
                    swap_struc_pedidos(arr_clientes[i].pedidos[j], arr_clientes[i].pedidos[k]);
                }
            }
        }

    }
}

void swap_struc( Cliente & a,  Cliente & b) {
    Cliente aux=b;
    b=a;
    a=aux;
}

void ordenar_clientes_nombre(Cliente * arr_clientes, int n_clientes) {
    for (int i = 0; i < n_clientes-1; i++) {
        for (int j = i+1; j < n_clientes; j++) {
            if (strcmp(arr_clientes[i].nombre, arr_clientes[j].nombre) == 0) {
                swap_struc(arr_clientes[i], arr_clientes[j]);
            }
        }
    }
}

int buscar_cliente(Cliente * arr_clientes, int dni_leido, int n_clientes) {
    for (int i = 0; i < n_clientes; i++) {
        if (arr_clientes[i].dni == dni_leido) return i;
    }
    return NO_ENCONTRADO;
}

int buscar_plato(Plato *&arr_platos, char * cod_plato_leido, int n_platos) {
    for (int i = 0; i < n_platos; i++) {
        if (strcmp(arr_platos[i].codigo, cod_plato_leido) == 0) return i;
    }
    return NO_ENCONTRADO;
}

int buscar_distrito(char * codigo, Distrito * arr_distritos, int n_distritos) {
    for (int i = 0; i < n_distritos; i++) {
        if (strcmp(arr_distritos[i].codigo, codigo) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void recuperar_nombre_distrito(Cliente &cliente, Distrito *&arr_distritos, int n_distritos) {
    int pos_distrito = buscar_distrito(cliente.distrito.codigo,arr_distritos, n_distritos);
    cliente.distrito.nombre = arr_distritos[pos_distrito].nombre;
}

void cargar_clientes_pedidos(const char * file_name, Cliente *&arr_clientes, int n_clientes, Distrito *&arr_distritos, int n_distritos,
                             Plato *&arr_platos, int n_platos) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    int cod_pedido, dni_leido, cant, pos_cliente, pos_plato;
    char *cod_plato_leido;
    while (true) {
        input>>cod_pedido;
        if (input.eof()) break;
        input>>dni_leido;
        cod_plato_leido = leer_cadena(input, ' ');
        input>>cant;
        pos_cliente = buscar_cliente(arr_clientes, dni_leido, n_clientes);
        pos_plato = buscar_plato(arr_platos, cod_plato_leido, n_platos);
        if (pos_cliente == NO_ENCONTRADO and pos_plato == NO_ENCONTRADO) {
            input.ignore(200, '\n');
            continue;
        }
        int n=arr_clientes[pos_cliente].cantidadDePedidos;
        if (n==0) recuperar_nombre_distrito(arr_clientes[pos_cliente],arr_distritos,n_distritos);
        arr_clientes[pos_cliente].pedidos[n].codigoPedido=cod_pedido;
        arr_clientes[pos_cliente].pedidos[n].cantidad=cant;
        arr_clientes[pos_cliente].pedidos[n].codigoPlato = cod_plato_leido;
        arr_clientes[pos_cliente].pedidos[n].precio = arr_platos[pos_plato].precio;
        arr_clientes[pos_cliente].pedidos[n].subtotal = arr_platos[pos_plato].precio*cant;
        arr_clientes[pos_cliente].pedidos[n].descripcion = arr_platos[pos_plato].descripcion;
        arr_clientes[pos_cliente].montoTotal += arr_clientes[pos_cliente].pedidos[n].subtotal;
        arr_clientes[pos_cliente].cantidadDePedidos++;
    }
    input.clear();
}

void prueba_carga_clientes(const char * file_name, Cliente * arr_clientes, int n_clientes) {
    ofstream output;
    abrir_archivo_salida(file_name, output);

    centrear("PRUEBA DE CARGA DE LOS CLIENTES",ANCHO_REPORTE,true,output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/3)<<"DNI"<<setw(ANCHO_REPORTE/3)<<"NOMBRE"<<setw(ANCHO_REPORTE/3)<<"CODIGO DISTRITO RESIDENCIA"<<right<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_clientes; i++) {
        output<<left<<setw(ANCHO_REPORTE/3)<<arr_clientes[i].dni;
        output<<setw(ANCHO_REPORTE/3)<<arr_clientes[i].nombre;
        output<<setw(ANCHO_REPORTE/3)<<arr_clientes[i].distrito.codigo<<right<<endl;
    }
    output.close();
}

void prueba_carga_distritos(const char * file_name, Distrito * arr_distritos, int n_distritos) {
    ofstream output;
    abrir_archivo_salida(file_name, output);

    centrear("PRUEBA DE CARGA DE LOS DISTRITOS",ANCHO_REPORTE,true,output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/3)<<"CODIGO"<<setw(ANCHO_REPORTE/3)<<"NOMBRE"<<setw(ANCHO_REPORTE/3)<<"UBICACION"<<right<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_distritos; i++) {
        output<<left<<setw(ANCHO_REPORTE/3)<<arr_distritos[i].codigo;
        output<<setw(ANCHO_REPORTE/3)<<arr_distritos[i].nombre;
        output<<setw(ANCHO_REPORTE/3)<<arr_distritos[i].ubicacion<<right<<endl;
    }
    output.close();
}

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

void centrear(const char * texto, int espacio, bool slash_n, ofstream & output) {
    int n = strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2,' ', slash_n, output);
}

void prueba_carga_platos_ofrecidos(const char * file_name, Plato * arr_platos, int n_platos) {
    ofstream output;
    abrir_archivo_salida(file_name, output);

    centrear("PRUEBA DE CARGA DE LOS PLATOS OFRECIDOS",ANCHO_REPORTE,true,output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/4 - 10)<<"CODIGO"<<setw(ANCHO_REPORTE/4 + 10)<<"NOMBRE";
    output<<setw(ANCHO_REPORTE/4)<<"PRECIO"<<setw(ANCHO_REPORTE/4)<<"CATEGORIA"<<right<<endl;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_platos; i++) {
        output<<left<<setw(ANCHO_REPORTE/4 - 10)<<arr_platos[i].codigo;
        output<<setw(ANCHO_REPORTE/4 + 10)<<arr_platos[i].descripcion;
        output<<setw(ANCHO_REPORTE/4)<<arr_platos[i].precio;
        output<<setw(ANCHO_REPORTE/4)<<arr_platos[i].categoria<<right<<endl;
    }
    output.close();
}

void cargar_clientes(const char * file_name, Cliente *&arr_clientes, int &n_clientes) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    arr_clientes = new Cliente[MAX_CLIENTES]{};
    int dni;
    while (true) {
        input>>dni;
        if (input.eof()) break;
        input.ignore();
        arr_clientes[n_clientes].nombre = leer_cadena(input, ',');
        arr_clientes[n_clientes].distrito.codigo = leer_cadena(input, '\n');
        arr_clientes[n_clientes].dni = dni;
        n_clientes++;
    }
    input.close();
}

void cargar_distritos(const char * file_name, Distrito *&distrito, int &n_distritos) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    distrito = new Distrito[MAX_DISTRITOS]{};

    char *codigo;
    while (true) {
        codigo = leer_cadena(input, ',');
        if (codigo == nullptr or input.eof()) {
            delete [] codigo;
            break;
        }
        distrito[n_distritos].nombre = leer_cadena(input, ',');
        distrito[n_distritos].ubicacion = leer_cadena(input, '\n');
        distrito[n_distritos].codigo = codigo;
        n_distritos++;
    }
    input.close();
}

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada: "<<file_name << endl;
        exit(1);
    }
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[MAX_CADENA]{}, *cadena;
    input>>ws;
    input.getline(buffer, MAX_CADENA, del);
    if (input.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.ignore();
    return dato;
}

void cargar_platos_ofrecidos(const char * file_name, Plato *&arr_platos, int &n_platos) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    arr_platos = new Plato[MAX_PLATOS]{};

    char *codigo;
    while (true) {
        codigo = leer_cadena(input, ',');
        if (codigo == nullptr or input.eof()) {
            delete [] codigo;
            break;
        }
        arr_platos[n_platos].descripcion = leer_cadena(input, ',');
        arr_platos[n_platos].precio = leer_double(input);
        arr_platos[n_platos].categoria = leer_cadena(input, '\n');
        arr_platos[n_platos].codigo = codigo;
        n_platos++;
    }
    input.close();
}
