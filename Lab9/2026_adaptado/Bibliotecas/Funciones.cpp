//
// Created by User on 22/06/2026.
//

#include "Funciones.hpp"


void imprimir_reporte(const char * file_name, Medico * medico, int n_med, Atencion * atencion, int n_atenciones) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output.precision(2);

    for (int i = 0; i < n_med; i++) {
        output<<i+1<<") MEDICO: "<<endl;
        output<<"CODIGO:  "<<medico[i].codigo<<endl<<"NOMBRE:  "<<medico[i].nombre<<endl<<"TARIFA:  "<<medico[i].tarifa<<endl;
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        output<<"ESPECIALIDAD: "<<endl<<"CODIGO:  "<<medico[i].especialidadCodigo<<endl<<"NOMBRE:  "<<medico[i].especialidad<<endl;
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
        output<<"ATENCIONES HECHAS:"<<endl;
        output<<left<<setw(4)<<"No."<<setw(16)<<"FECHA"<<setw(26)<<"CODIGO DEL PACIENTE"<<setw(18)<<"DURACION"<<"PAGO"<<endl<<right;
        int n=1;
        double total_ingresos=0;
        for (int j = 0; j < n_atenciones; j++) {
            if (medico[i].codigo == atencion[j].codigoMedico) {
                output<<setfill('0')<<setw(2)<<n<<") "<<setfill(' ');
                output<<setfill('0')<<setw(2)<<atencion[j].fecha.dia<<"/"<<setw(2)<<atencion[j].fecha.mes<<"/"
                      <<setw(2)<<atencion[j].fecha.anio<<setfill(' ');
                imprimir_linea(16 - 6, ' ',false, output);
                output<<atencion[j].paciente.valor1<<"-"<<atencion[j].paciente.valor2<<"-"<<atencion[j].paciente.valor3;
                imprimir_linea(26-4-11, ' ',false, output);
                output<<setfill('0')<<setw(2)<<atencion[j].duracion.horas<<":"<<setw(2)<<atencion[j].duracion.minutos<<":"
                              <<setw(2)<<atencion[j].duracion.segundos<<setfill(' ');
                double pago_atencion = atencion[j].duracion.segundos_HHHHMMSS*medico[i].tarifa/3600.0;
                output<<setw(14)<<pago_atencion<<endl;
                n++;
                total_ingresos += pago_atencion;
            }
        }
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
        output<<"NUMERO DE ATENCIONES:        "<<n-1<<endl;
        output<<"TOTAL DE INGRESOS:           "<<total_ingresos<<endl;
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
    }


}

void swap_struct( Atencion & a,  Atencion & b){
    Atencion temp=a;
    a=b;
    b=temp;
}

void ordenar_atenciones(Atencion *& atencion, int n_atenciones){
    for (int i = 0; i < n_atenciones-1; i++) {
        for (int j = i+1; j < n_atenciones; j++) {
            int cod_i=atencion[i].paciente.valor1*1000000 + atencion[i].paciente.valor2*10000 + atencion[i].paciente.valor3,
                cod_j=atencion[j].paciente.valor1*1000000 + atencion[j].paciente.valor2*10000 + atencion[j].paciente.valor3;
            if (atencion[i].codigoMedico > atencion[j].codigoMedico or
                atencion[i].codigoMedico == atencion[j].codigoMedico and (atencion[i].fecha.fecha_AAAAMMDD < atencion[j].fecha.fecha_AAAAMMDD or
                atencion[i].fecha.fecha_AAAAMMDD == atencion[j].fecha.fecha_AAAAMMDD and cod_i > cod_j)) {
                swap_struct(atencion[i], atencion[j]);
            }
        }
    }
}

void prueba_atenciones(const char * file_name, Atencion * arr_atencion, int n_atenciones) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);

    centrear("PRUEBA DE CARGA DE LAS ATENCIONES", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/4)<<"FECHA ATENCION"<<setw(ANCHO_REPORTE/4)<<"CODIGO MEDICO";
    output<<setw(ANCHO_REPORTE/4)<<"DURACION"<<setw(ANCHO_REPORTE/4)<<"PACIENTE"<<endl<<right;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_atenciones; i++) {
        output<<setfill('0')<<setw(2)<<arr_atencion[i].fecha.dia<<"/"<<setw(2)<<arr_atencion[i].fecha.mes<<"/"
              <<setw(2)<<arr_atencion[i].fecha.anio<<setfill(' ');
        imprimir_linea(ANCHO_REPORTE/4 - 10, ' ',false, output);
        output<<left<<setw(ANCHO_REPORTE/4)<<arr_atencion[i].codigoMedico<<right;
        output<<setfill('0')<<setw(2)<<arr_atencion[i].duracion.horas<<":"<<setw(2)<<arr_atencion[i].duracion.minutos<<":"
              <<setw(2)<<arr_atencion[i].duracion.segundos<<setfill(' ');
        imprimir_linea(ANCHO_REPORTE/4 - 8, ' ',false, output);
        output<<arr_atencion[i].paciente.valor1<<"-"<<arr_atencion[i].paciente.valor2<<"-"<<arr_atencion[i].paciente.valor3<<endl;
    }
    output.close();
}

int leer_tiempo( ifstream & input) {
    Hora tiempo;
    tiempo.horas=leer_int(input);
    tiempo.minutos=leer_int(input);
    tiempo.segundos=leer_int(input);
    return tiempo.horas*3600 + tiempo.minutos*60 + tiempo.segundos;
}

void cargar_atenciones(const char * file_name, Atencion *& arr_atenciones, int& n_atenciones) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    arr_atenciones = new Atencion[MAX_ATENCIONES];
    int dia, mes, anio, sede, hora_ingreso, hora_salida;
    while (true) {
        input>>dia;
        if (input.eof()) break;
        input.ignore();
        mes = leer_int(input);
        anio = leer_int(input);
        while (true) {
            sede = leer_int(input);
            hora_ingreso = leer_tiempo(input);
            arr_atenciones[n_atenciones].paciente.valor1 = leer_int(input);
            arr_atenciones[n_atenciones].paciente.valor2 = leer_int(input);
            arr_atenciones[n_atenciones].paciente.valor3 = leer_int(input);
            hora_salida = leer_tiempo(input);
            input >> arr_atenciones[n_atenciones].codigoMedico;
            arr_atenciones[n_atenciones].fecha.dia = dia;
            arr_atenciones[n_atenciones].fecha.mes = mes;
            arr_atenciones[n_atenciones].fecha.anio = anio;
            arr_atenciones[n_atenciones].fecha.fecha_AAAAMMDD = dia + mes*100 + anio*10000;
            int duracion = hora_salida - hora_ingreso;
            arr_atenciones[n_atenciones].duracion.segundos_HHHHMMSS = duracion;
            arr_atenciones[n_atenciones].duracion.horas = duracion/3600;
            duracion = duracion%3600;
            arr_atenciones[n_atenciones].duracion.minutos = duracion/60;
            arr_atenciones[n_atenciones].duracion.segundos = duracion%60;
            n_atenciones++;
            if (input.get()=='\n') break;
        }
    }
    input.close();
}


void abrir_archivo_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo escritura "<<endl;
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

void prueba_carga_medicos(const char * file_name , Medico * arr_medicos, int n_med) {
    ofstream output;
    abrir_archivo_escritura(file_name, output);
    output<<fixed;
    output.precision(2);

    centrear("PRUEBA DE CARGA DE LOS MEDICOS", ANCHO_REPORTE, true, output);
    imprimir_linea(ANCHO_REPORTE, '=', true, output);
    output<<left<<setw(ANCHO_REPORTE/5 - 10)<<"CODIGO ESPE."<<setw(ANCHO_REPORTE/5 - 10)<<"CODIGO MEDICO";
    output<<setw(ANCHO_REPORTE/5)<<"ESPECIALIDAD"<<setw(ANCHO_REPORTE/5 + 20)<<"NOMBRE"<<setw(ANCHO_REPORTE/5)<<"TARIFA POR HORA"<<endl<<right;
    imprimir_linea(ANCHO_REPORTE, '-', true, output);
    for (int i = 0; i < n_med; i++) {
        output<<left<<setw(ANCHO_REPORTE/5 - 10)<<arr_medicos[i].especialidadCodigo<<setw(ANCHO_REPORTE/5 - 10)<<arr_medicos[i].codigo;
        output<<setw(ANCHO_REPORTE/5)<<arr_medicos[i].especialidad<<setw(ANCHO_REPORTE/5 + 20)<<arr_medicos[i].nombre<<right;
        output<<setw(10)<<arr_medicos[i].tarifa<<endl;
    }
    output.close();
}

void abrir_archivo_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura" << endl;
        exit(1);
    }
}

char * leer_cadena( ifstream & input, char del) {
    char buffer[150]{}, *cadena;
    input.getline(buffer, 150, del);
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
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

char * asignar_cadena(char * origen) {
    char *cadena;
    cadena = new char[strlen(origen)+1];
    strcpy(cadena, origen);
    return cadena;
}

void modificar_cadena(char * cadena) {
    bool mayus=true;

    for (int i = 0; cadena[i] ; i++) {
        if (cadena[i] >= 'A' and cadena[i] <= 'Z' and (not mayus)) {
            cadena[i] += 'a'-'A';
        }
        mayus = false;
        if (cadena[i]==' ') mayus=true;
    }
}

void cargar_medicos(const char * file_name, Medico *& arr_medicos, int &n_med) {
    ifstream input;
    abrir_archivo_lectura(file_name, input);
    arr_medicos = new Medico[MAX_MEDICOS];
    int co_espe;
    char *especialidad;
    while (true) {
        input>>co_espe;
        if (input.eof()) break;
        input.ignore();
        especialidad = leer_cadena(input, ',');
        while (true) {
            arr_medicos[n_med].codigo = leer_int(input);
            arr_medicos[n_med].nombre = leer_cadena(input, ',');
            modificar_cadena(arr_medicos[n_med].nombre);
            input>>arr_medicos[n_med].tarifa;
            arr_medicos[n_med].especialidadCodigo = co_espe;
            arr_medicos[n_med].especialidad = asignar_cadena(especialidad);
            modificar_cadena(arr_medicos[n_med].especialidad);
            n_med++;
            if (input.get() == '\n') break;
        }
    }
    input.close();
}
