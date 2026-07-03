//
// Created by User on 1/07/2026.
//

#include "Funciones.hpp"

int leer_int( ifstream & input) {
    int dato;
    input>>dato;
    input.ignore();
    return dato;
}

void leer_hora(Hora &tiempo, ifstream & input) {
    tiempo.horas = leer_int(input);
    tiempo.minutos = leer_int(input);
    tiempo.segundos = leer_int(input);
    tiempo.segundos_HHHHMMSS = tiempo.horas*3600 + tiempo.minutos*60 + tiempo.segundos;
}

void asignar_hora(Hora &tiempo, int origen) {
    tiempo.segundos_HHHHMMSS = origen;
    tiempo.horas = origen/3600;
    origen = origen%3600;
    tiempo.minutos = origen/60;
    tiempo.segundos = origen%60;
}

struct Nodo * buscar_medico(ListaMedicosTAD &lista_medicos, int cod_med) {
    struct Nodo *recorrido = lista_medicos.inicio;

    while (recorrido != nullptr) {
        if (recorrido->dato.codigo == cod_med) return recorrido;
        recorrido = recorrido->siguiente;
    }
    return nullptr;
}

void cargar_atenciones(const char * file_name, ListaMedicosTAD &lista_medicos) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    int dd, cod_med;
    char c;
    Hora hora_entrada, hora_salida;
    Fecha fecha_leida;
    struct Nodo *pos_med;
    while (true) {
        input>>dd;
        if (input.eof()) break;
        input>>c>>fecha_leida.mes>>c>>fecha_leida.anio>>c;
        fecha_leida.dia=dd;
        fecha_leida.fecha_AAAAMMDD = dd + fecha_leida.mes*100 + fecha_leida.anio*10000;
        while (true) {
            struct Atencion atencion_leida{};
            leer_hora(hora_entrada, input);
            input>>atencion_leida.paciente.valor1>>c>>atencion_leida.paciente.valor2>>c>>atencion_leida.paciente.valor3>>c;
            leer_hora(hora_salida, input);
            input>>cod_med;
            pos_med = buscar_medico(lista_medicos, cod_med);
            if (pos_med != nullptr) {
                asignar_hora(atencion_leida.duracion, hora_salida.segundos_HHHHMMSS - hora_entrada.segundos_HHHHMMSS);
                atencion_leida.fecha = fecha_leida;
                pos_med->dato.atenciones[pos_med->dato.num_atenciones] = atencion_leida;
                pos_med->dato.ingresosPorAtencion += pos_med->dato.tarifa*atencion_leida.duracion.segundos_HHHHMMSS/3600.0;
                pos_med->dato.num_atenciones++;
            }
            if (input.get()=='\n') break;
        }
    }
    input.close();
}

void abrir_archivo_salida(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo: "<<file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, bool slash_n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    if (slash_n) output.put('\n');
}

void centrear(const char * texto, int espacio, bool slash_n, ofstream & output) {
    int n=strlen(texto);
    output<<setw((espacio+n)/2)<<texto;
    imprimir_linea(espacio - (espacio+n)/2, ' ', slash_n, output);
}

void imprimir_atenciones(struct Atencion * &atencion, int num_atenciones, ofstream & output) {
    for (int i = 0; i < num_atenciones; i++) {
        imprimir_linea(6,' ', false, output);
        output<<setfill('0')<<setw(2)<<atencion[i].fecha.dia<<"/"<<setw(2)<<atencion[i].fecha.mes<<"/"<<setw(2)<<atencion[i].fecha.anio;
        imprimir_linea(6,' ', false, output);
        output<<setw(2)<<atencion[i].duracion.horas<<":"<<setw(2)<<atencion[i].duracion.minutos<<":"<<setw(2)<<atencion[i].duracion.segundos<<setfill(' ');
        imprimir_linea(8,' ', false, output);
        output<<atencion[i].paciente.valor1<<'-'<<atencion[i].paciente.valor2<<'-'<<atencion[i].paciente.valor3<<endl;
    }
}

void prueba_carga(const char * file_name, const ListaMedicosTAD &lista_medicos, bool atenciones) {
    ofstream output;
    abrir_archivo_salida(file_name, output);

    struct Nodo *recorrido = lista_medicos.inicio;
    centrear("PRUEBA DE CARGA DE LOS MEDICOS", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/4 - 20)<<"CODIGO"<<setw(ANCHO_REPORTE/4 + 20)<<"NOMBRE";
    output<<setw(ANCHO_REPORTE/4)<<"ESPECIALIDAD"<<"TARIFA POR HORA"<<endl<<right;
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    while (recorrido != nullptr) {
        output<<left<<setw(ANCHO_REPORTE/4 - 20)<<recorrido->dato.codigo;
        output<<setw(ANCHO_REPORTE/4 + 20)<<recorrido->dato.nombre;
        output<<setw(ANCHO_REPORTE/4)<<recorrido->dato.especialidad<<right;
        output<<setw(10)<<recorrido->dato.tarifa<<endl;
        if (atenciones) {
            imprimir_linea(ANCHO_REPORTE, '-', true, output);
            imprimir_atenciones(recorrido->dato.atenciones, recorrido->dato.num_atenciones, output);
            imprimir_linea(ANCHO_REPORTE, '=', true, output);
        }
        recorrido = recorrido->siguiente;
    }
    output.close();
}

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo: " <<file_name << endl;
        exit(1);
    }
}

void inicializar_lista(ListaMedicosTAD &lista_medicos) {
    lista_medicos.cant_medicos = 0;
    lista_medicos.inicio = nullptr;
}

char * leer_cadena( ifstream & input, char del) {
    char *cadena, buffer[70];
    input.getline(buffer, 70, del);
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

char * asignar_cadena(char * buffer) {
    char *cadena;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void modificar_cadena(char *cadena) {
    bool Mayus = true;
    for (int i = 0; cadena[i] ; i++) {
        if (cadena[i]>='A' and cadena[i]<='Z' and (not Mayus)) cadena[i] = tolower(cadena[i]);
        Mayus = false;
        if (cadena[i] == ' ') Mayus = true;
    }
}

void asignar_struct_med( struct Medico & dato, struct Medico & medico) {
    dato.codigo = medico.codigo;
    dato.nombre = asignar_cadena(medico.nombre);
    modificar_cadena(dato.nombre);
    dato.especialidad = asignar_cadena(medico.especialidad);
    dato.tarifa = medico.tarifa;
    dato.atenciones = new Atencion[MAX_ATENCIONES]{};
    dato.ingresosPorAtencion = 0;
    dato.num_atenciones = 0;
}

void insertar_ordenado(struct ListaMedicosTAD &lista_medicos, struct Medico & medico) {
    struct Nodo *nuevo_nodo;
    nuevo_nodo = new Nodo;
    asignar_struct_med(nuevo_nodo->dato, medico);
    nuevo_nodo->siguiente = nullptr;

    struct Nodo *recorrido = lista_medicos.inicio;
    struct Nodo *anterior = nullptr;

    while (recorrido != nullptr) {
        if (nuevo_nodo->dato.codigo < recorrido->dato.codigo) break;
        anterior = recorrido;
        recorrido = recorrido->siguiente;
    }

    nuevo_nodo->siguiente = recorrido;
    if (anterior != nullptr) anterior->siguiente = nuevo_nodo;
    else lista_medicos.inicio = nuevo_nodo;
    lista_medicos.cant_medicos++;
}

void cargar_medicos(const char * file_name, ListaMedicosTAD &lista_medicos) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    inicializar_lista(lista_medicos);

    int cod_med;
    while (true) {
        input>>cod_med;
        if (input.eof()) break;
        input.ignore();
        struct Medico med_leido{};
        med_leido.nombre = leer_cadena(input, ',');
        med_leido.tarifa = leer_double(input);
        med_leido.especialidad = leer_cadena(input, '\n');
        med_leido.codigo = cod_med;
        insertar_ordenado(lista_medicos, med_leido);
    }
    input.close();
}
