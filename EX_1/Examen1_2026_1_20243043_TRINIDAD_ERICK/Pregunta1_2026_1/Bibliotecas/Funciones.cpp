//
// Created by aml on 18/05/2026.
//

#include "Funciones.hpp"

void abrir_lectura(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada"<<file_name << endl;
        exit(1);
    }
}

void abrir_escritura(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout<<"Error al abrir el archivo de salida"<<file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(c);
    output<<endl;
}

void imprimir_titulo( ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output<<setw((ANCHO_REPORTE+29)/2)<<"CLINICA DE URGENCIAD TP_SALUD"<<endl;
    output<<setw((ANCHO_REPORTE+19)/2)<<"ATENCIONES POR SEDE"<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void espacios(int n, ofstream & output) {
    for (int i = 0; i < n; i++) output.put(' ');
}

void imprimir_nombre(ifstream & input, int espacio, char del, ofstream & output) {
    int n=0;
    char c;
    input>>ws;
    while (true) {
        input.get(c);
        if (c==del) break;
        if (c=='_' or c=='/' or c=='-') c=' ';
        if (c>='a' and c<='z') c-='a'-'A';
        output.put(c);
        n++;
    }
    espacios(espacio-n, output);
}

void imprimir_encabezado( ofstream & output) {
    output<<setw(11)<<"FECHA";
    output<<setw(20)<<"PACIENTE";
    output<<setw(38)<<"DURACION";
    output<<setw(20)<<"MEDICO";
    output<<setw(46)<<"ESPECIALIDAD";
    output<<setw(14)<<"PAGO"<<endl;
}

int leer_fecha( ifstream & input) {
    int dd,mm,aa;
    char c;
    input>>dd;
    if (input.eof()) return NO_ENCONTRADO;
    input>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

int leer_tiempo( ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;
    return hora*3600+minuto*60+segundo;
}

void imprimir_fecha(int fecha, ofstream & output) {
    int dd, mm , aa;
    aa = fecha/10000;
    fecha %= 10000;
    mm = fecha/100;
    dd = fecha%100;
    output<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}

void buscar_imprimir_nombre_paciente( ifstream & input, int id, ofstream & output) {
    input.clear();
    input.seekg (0, ios::beg);

    int part1,part2,part3,id_leido;
    char c;
    while (true) {
        input>>part1;
        if (input.eof()) break;
        input>>c>>part2>>c>>part3;
        id_leido = part1*1000000+part2*10000+part3;
        if (id_leido == id) {
            imprimir_nombre(input, 30, ' ',output );
            break;
        }
        input.ignore(50, '\n');
    }
}

void imprimir_tiempo(int tiempo, ofstream & output) {
    int hora, minuto, segundo;
    hora = tiempo/3600;
    tiempo %= 3600;
    minuto = tiempo/60;
    segundo = tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}


void ignorar(char del, ifstream & input) {
    char c;
    input>>ws;
    while (true) {
        input.get(c);
        if (c==del) break;
    }
}

void buscar_imprimir_doc( ifstream &input, double &pago, int duracion, int doc, ofstream & output) {
    input.clear();
    input.seekg (0, ios::beg);

    int cod_espe,doc_leido,encontrado=NO_ENCONTRADO;
    double costo_hora;
    char c;
    while (true) {
        input>>cod_espe;
        if (input.eof()) break;
        ignorar(' ',input);
        while (true) {
            input>>doc_leido;
            if (doc==doc_leido) {
                imprimir_nombre(input,35,' ',output);
                input>>costo_hora;
                pago=costo_hora*duracion/3600.0;
                output<<setw(10)<<cod_espe<<setw(20)<<pago<<endl;
                encontrado=1;
                break;
            }
            ignorar(' ',input);
            input>>costo_hora;
            input.get(c);
            if (c=='\n') break;
        }
        if (encontrado==1) break;
    }
}

void imprimir_resumen_sede(int n, double pago_sede, int total_atenciones, ofstream & output) {
    output<<"TOTAL DE ATENCIONES:  "<<n<<endl;
    output<<"TOTAL DE PAGO SEDE:  S/. "<<pago_sede<<endl;
    output<<"TIEMPO TOTAL ATENCIONES:  ";
    imprimir_tiempo(total_atenciones,output);
    output<<endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void buscar_imprimir_atenciones(int sede, ifstream & input_atenciones, ifstream & input_especialidades, ifstream & input_pacientes,
                                ofstream & output, double &pago_sede) {
    input_atenciones.clear();
    input_atenciones.seekg(0, ios::beg);
    // 895    01:21:00    691-12-9990    03:13:54    4393
    int fecha, sede_leido, hora_inicio, hora_alta, part1,part2, part3, id, doc, i=0, total_atenciones=0;
    double pago;
    char c;
    while (true) {
        fecha=leer_fecha(input_atenciones);
        if (fecha == NO_ENCONTRADO or input_atenciones.eof()) break;
        while (true) {
            input_atenciones>>sede_leido;
            hora_inicio=leer_tiempo(input_atenciones);
            input_atenciones>>part1>>c>>part2>>c>>part3;
            hora_alta=leer_tiempo(input_atenciones);
            input_atenciones>>doc;
            id = part1*1000000+part2*10000+part3;
            if (sede_leido == sede) {
                i++;
                output<<setfill('0')<<setw(2)<<i<<setfill(' ')<<left<<setw(4)<<")"<<right;
                imprimir_fecha(fecha, output);
                output<<setw(13)<<id<<" - ";
                buscar_imprimir_nombre_paciente(input_pacientes, id, output);
                imprimir_tiempo(hora_alta-hora_inicio, output);
                output<<setw(12)<<doc<<" - ";
                buscar_imprimir_doc(input_especialidades,pago,hora_alta-hora_inicio,doc,output);
                pago_sede+=pago;
                total_atenciones+=(hora_alta-hora_inicio);
            }
            input_atenciones.get(c);
            if (c=='\n') break;
        }
    }
    imprimir_resumen_sede(i,pago_sede,total_atenciones,output);
}

void imprimir_resumen_final(int n_sedes, double pago_total, int sede_mayor, double sede_pago_mayor, ofstream & output) {
    output<<"CANTIDAD DE SEDES QUE ATENDIERON: "<<n_sedes<<endl;
    output<<"PAGO TOTAL: S/.  "<<pago_total<<endl;
    output<<"SEDE CON MAYOR PAGO:  "<<sede_mayor<<" - S/. "<<sede_pago_mayor<<endl;
}

void imprimir_reporte(const char *file_sedes, const char *file_pacientes, const char *file_especialidades,
                      const char *file_atenciones, const char *file_salida) {
    ifstream input_sedes,input_pacientes,input_especialidades,input_atenciones;
    abrir_lectura(file_sedes, input_sedes);
    abrir_lectura(file_pacientes, input_pacientes);
    abrir_lectura(file_especialidades, input_especialidades);
    abrir_lectura(file_atenciones, input_atenciones);
    ofstream output;
    abrir_escritura(file_salida, output);

    output<<fixed;
    output.precision(2);
    imprimir_titulo(output);
    int sede, sede_mayor, n_sedes=0;
    double sede_pago_mayor=0, pago_total=0;
    while (true) {
        input_sedes>>sede;
        if (input_sedes.eof()) break;
        n_sedes++;
        output<<"SEDE: "<<sede<<" - ";
        imprimir_nombre(input_sedes, 35, '\n', output);
        output<<endl;
        imprimir_linea(ANCHO_REPORTE,'-',output);
        imprimir_encabezado(output);
        double pago_sede=0;
        buscar_imprimir_atenciones(sede, input_atenciones, input_especialidades, input_pacientes,output,
                                   pago_sede);
        pago_total+=pago_sede;
        if (sede_pago_mayor==0 or sede_pago_mayor<pago_sede) {
            sede_mayor=sede;
            sede_pago_mayor=pago_sede;
        }
    }
    imprimir_resumen_final(n_sedes, pago_total, sede_mayor, sede_pago_mayor, output);
}


