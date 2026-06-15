//
// Created by User on 03/05/2026.
//

#include "Funciones.hpp"

void imprimir_titulo(ofstream & output, double tarifa) {
    output << setw((ANCHO_REPORTE+20) /2) << "PLATAFORMA TP_Twitch"<<endl;
    output << setw(4*ANCHO_REPORTE/13) << "" << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifa <<
              " POR CADA MINUTO Y FRACCION" << endl;
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

void imprimir_titulo_tablas1(ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<setw(6 + 2*(ANCHO_REPORTE-6)/COLUMNAS_CANALES)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 4)<<"RATING DE"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 5)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 6)<<"NUMERO TOTAL"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 6)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES)+ 7)<<"TIEMPO TOTAL DE"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 8)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 7)<<"PORCENTAJE POR"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 7)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 12)<<"INGRESOS POR REPRODUCCION"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 13)<<"";
    output<<endl;
    output<<setw(6)<<"No.   ";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 3)<<"CODIGO"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 3)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 8)<<"FECHA DE CREACION"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 9)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 3)<<"CALIDAD"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 8)<<"DE REPRODUCCIONES"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 9)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 7)<<"REPRODUCCIONES"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 7)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 8)<<"RATING DE CALIDAD"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 9)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 6)<<"DE ETIQUETAS"<< setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 6)<<"";
    output<<endl;
}

void imprimir_titulo_tablas2(ofstream & output) {
    imprimir_linea(ANCHO_REPORTE,'-',output);
    output<<setw(6 + 2*(ANCHO_REPORTE-6)/COLUMNAS_CANALES)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 7)<<"CANTIDAD TOTAL"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 7)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 6)<<"TIEMPO TOTAL"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 6)<<"";
    output<<endl;
    output<<setw(6)<<"No.   ";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 4)<<"ETIQUETA"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 4)<<"DURACION"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 8)<<"DE REPRODUCCIONES"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 9)<<"";
    output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 5)<<"REPRODUCIDO"<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 6)<<"";
    output<<endl;
}

void generar_reporte(const char *file_name, int * fecha_canales, char * codigos_char_canales, int * codigos_int_canales,
                     double * ratings_canales, int n_canales, int * codigos_etiquetas, int * tiempo_duracion_etiquetas,
                     int n_etiquetas, int * cant_total_reproducciones_canales, int * cant_total_reproducciones_etiquetas,
                     double * ingresos_por_reproducciones, double tarifa,
                     int * tiempo_total_reproducciones_canales, int * tiempo_total_reproducciones_etiquetas) {
    ofstream output;
    abrir_archivo_escritura(output, file_name);

    imprimir_titulo(output,tarifa);
    output << "CANALES ADSCRITOS A LA PLATAFORMA " << endl;
    imprimir_titulo_tablas1(output);
    output<<fixed;
    for (int i=0; i<n_canales; i++) {
        output<<setw(2)<<i<<")   ";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<""<<codigos_char_canales[i]
              <<codigos_int_canales[i]<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 3)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 5)<<"";
        imprimir_fecha(fecha_canales[i], output);
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 5)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<""<<setprecision(2)<<ratings_canales[i]
              <<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 3)<<cant_total_reproducciones_canales[i]
              <<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
        imprimir_tiempo(tiempo_total_reproducciones_canales[i], output);
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES)- 4)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<"";
        if (ratings_canales[i]<=5 and ratings_canales[i]>4) output<<"+30%";
        if (ratings_canales[i]<=4 and ratings_canales[i]>3) output<<"+20%";
        if (ratings_canales[i]<=3 and ratings_canales[i]>2) output<<"  0%";
        if (ratings_canales[i]<=2 and ratings_canales[i]>=1) output<<"-25%";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 4)<<setprecision(2)<<ingresos_por_reproducciones[i]
              <<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
        output<<endl;
    }
    imprimir_linea(ANCHO_REPORTE,'=',output);
    output << "ETIQUETAS DE LA PLATAFORMA" << endl;
    imprimir_titulo_tablas2(output);
    for (int i = 0; i < n_etiquetas; i++) {
        output<<setw(2)<<i<<")   ";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 3)<<""<<codigos_etiquetas[i]
              <<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 3)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<"";
        imprimir_tiempo(tiempo_duracion_etiquetas[i], output);
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 3)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) + 3)<<cant_total_reproducciones_etiquetas[i]
              <<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 2)<<"";
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
        imprimir_tiempo(tiempo_total_reproducciones_etiquetas[i], output);
        output<<setw((ANCHO_REPORTE-6)/(2*COLUMNAS_CANALES) - 4)<<"";
        output<<endl;
    }
    imprimir_linea(ANCHO_REPORTE,'=',output);
}

int buscar_canal(char * codigos_char_canales, int * codigos_int_canales, char codigo_char_canal_leido,
                 int codigo_int_canal_leido, int n_canales) {
    for (int i = 0; i < n_canales; i++) {
        if (codigos_char_canales[i] == codigo_char_canal_leido and
            codigos_int_canales[i] == codigo_int_canal_leido) return i;
    }
    return -1;
}

int buscar_etiqueta(int * codigos_etiquetas, int codigo_etiqueta_leido, int n_etiquetas) {
    for (int i = 0; i < n_etiquetas; i++) {
        if (codigos_etiquetas[i] == codigo_etiqueta_leido) return i;
    }
    return -1;
}

double calcular_ingreso(int tiempo, int reproducciones, double rating, double tarifa) {
    double ingreso;
    if (rating<=5 and rating>4) ingreso=(double)tiempo/60*1.3*tarifa*reproducciones;
    if (rating<=4 and rating>3) ingreso=(double)tiempo/60*1.2*tarifa*reproducciones;
    if (rating<=3 and rating>2) ingreso=(double)tiempo/60*tarifa*reproducciones;
    if (rating<=2 and rating>=1) ingreso=(double)tiempo/60*0.75*tarifa*reproducciones;
    return ingreso;
}

void procesar_reproducciones(const char *file_name, char *codigos_char_canales, int *codigos_int_canales,
                             int * codigos_etiquetas, double * ratings_canales,int * tiempo_duracion_etiquetas,
                             int * cant_total_reproducciones_canales, int * cant_total_reproducciones_etiquetas,
                             double * ingresos_por_reproducciones, int * tiempo_total_reproducciones_canales,
                             int * tiempo_total_reproducciones_etiquetas, int n_canales, int n_etiquetas, double tarifa) {
    ifstream input;
    abrir_archivo_lectura(input, file_name);

    int fecha_registro, codigo_int_canal_leido, codigo_etiqueta_leido, reproducciones;
    char codigo_char_canal_leido;
    int pos_canal, pos_etiqueta;

    while (1) {
        fecha_registro=leer_fecha(input);
        if (fecha_registro == -1 or input.eof()) break;

        input >> ws >> codigo_char_canal_leido >> codigo_int_canal_leido >> codigo_etiqueta_leido >> reproducciones;

        pos_canal = buscar_canal(codigos_char_canales, codigos_int_canales, codigo_char_canal_leido,
                                 codigo_int_canal_leido, n_canales);
        pos_etiqueta = buscar_etiqueta(codigos_etiquetas, codigo_etiqueta_leido, n_etiquetas);

        if (pos_canal != -1) {
            cant_total_reproducciones_canales[pos_canal]+=reproducciones;
            tiempo_total_reproducciones_canales[pos_canal]+=reproducciones*tiempo_duracion_etiquetas[pos_etiqueta];
            ingresos_por_reproducciones[pos_canal]+=calcular_ingreso(tiempo_duracion_etiquetas[pos_etiqueta],
                                                                     reproducciones,ratings_canales[pos_canal], tarifa);
        } else {
            cout << "No se pudo encontrar el codigo del canal" << endl;
        }
        if (pos_etiqueta != -1) {
            cant_total_reproducciones_etiquetas[pos_etiqueta]+=reproducciones;
            tiempo_total_reproducciones_etiquetas[pos_etiqueta]+=reproducciones*tiempo_duracion_etiquetas[pos_etiqueta];
        }else {
            cout << "No se pudo encontrar el codigo de la etiqueta" << endl;
        }
    }

    input.close();
}

void imprimir_tiempo(int tiempo, ofstream &output) {
    int hora, minuto, segundo;

    output <<  setfill('0');
    if (tiempo >= HORA_COMPLETA) {
        hora = tiempo/3600;
        tiempo %= 3600;
        output << setfill('0') << setw(2) << hora << ":";
    }
    minuto = tiempo/60;
    segundo = tiempo%60;

    output << setw(2) << minuto << ":" << setw(2) << segundo << setfill(' ');
}

void probar_etiquetas(const char *file_name, int *codigos_etiquetas, int *tiempo_duracion_etiquetas, int n_etiquetas) {
    ofstream output;
    abrir_archivo_escritura(output, file_name);

    output << setw((ANCHO_REPORTE+32)/2) << "PRUEBA DE CARGA DE LAS ETIQUETAS" << endl;
    imprimir_linea(ANCHO_REPORTE,'=', output);
    output << setw(ANCHO_REPORTE/2) << "CODIGOS";
    output << setw(ANCHO_REPORTE/2) << "TIEMPO DE DURACION"<<endl;

    for (int i = 0; i < n_etiquetas; i++) {
        output << setw(ANCHO_REPORTE/2) << codigos_etiquetas[i];
        output << setw(ANCHO_REPORTE/2 - 5) << " ";
        imprimir_tiempo(tiempo_duracion_etiquetas[i], output);
        output << endl;
    }
    output.close();
}

int leer_duracion(ifstream & input) {
    int minuto, segundo;
    char c;
    input>>minuto>>c>>segundo;
    return minuto*60+segundo;
}

void cargar_etiquetas(const char *file_name, int *codigos_etiquetas, int *tiempo_duracion_etiquetas, int &n_etiquetas) {
    ifstream input;
    abrir_archivo_lectura(input, file_name);

    int codigo;

    while (1) {
        input >> codigo;
        if (input.eof()) break;
        input >> ws;
        input.ignore(50, ' ');
        tiempo_duracion_etiquetas[n_etiquetas] = leer_duracion(input);
        codigos_etiquetas[n_etiquetas] = codigo;
        input.ignore(50, '\n');
        n_etiquetas++;
    }
    input.close();
}

void abrir_archivo_escritura(ofstream &output, const char *file_name) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo de escritura: " << file_name << endl;
        exit(1);
    }
}

void imprimir_linea(int n, char c, ofstream &output) {
    for (int i = 0; i < n; i++) output.put(c);
    output.put('\n');
}

void imprimir_fecha(int fecha, ofstream &output) {
    int aa,mm,dd;
    aa = fecha / 10000;
    fecha %= 10000;
    mm = fecha / 100;
    dd = fecha % 100;

    output << setfill('0') << setw(2) << dd << "/" << setw(2) << mm << "/" << setw(4) << aa;
    output << setfill(' ');
}

void probar_canales(const char *file_name, int *fecha_canales, int *codigos_int_canales, char *codigos_char_canales,
                    double *ratings_canales, int n_canales) {
    ofstream output;
    abrir_archivo_escritura(output, file_name);

    output << setw((ANCHO_REPORTE+30)/2) << "PRUEBA DE CARGA DE LOS CANALES" << endl;
    imprimir_linea(ANCHO_REPORTE,'=', output);
    output << setw(ANCHO_REPORTE/3) << "FECHA";
    output << setw(ANCHO_REPORTE/3) << "CODIGO";
    output << setw(ANCHO_REPORTE/3) << "RATING"<<endl;

    for (int i = 0; i < n_canales; i++) {
        output << setw(ANCHO_REPORTE/3 - 10) << " ";
        imprimir_fecha(fecha_canales[i], output);
        output << setw(ANCHO_REPORTE/3 - 5) << " " << codigos_char_canales[i] << codigos_int_canales[i];
        output << setw(ANCHO_REPORTE/3) << ratings_canales[i] << endl;
    }
    output.close();
}

int leer_fecha(ifstream &input) {
    int aa,mm,dd;
    char c;
    input>>dd;
    if (input.eof()) return -1;
    input>>c>>mm>>c>>aa;
    return aa*10000+mm*100+dd;
}

void abrir_archivo_lectura(ifstream &input, const char *file_name) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo lectura: "<<file_name<< endl;
        exit(1);
    }
}

void cargar_canales(const char *file_name, int *fecha_canales, int *codigos_int_canales, char *codigos_char_canales,
                    double *ratings_canales, int &n_canales) {
    ifstream input;
    abrir_archivo_lectura(input, file_name);
    int date;

    while (1) {
        date = leer_fecha(input);
        if (date == -1 or input.eof()) break;
        input >> ws >> codigos_char_canales[n_canales] >> codigos_int_canales[n_canales];
        input >> ws;
        input.ignore(50, ' ');
        input >> ratings_canales[n_canales];
        input.ignore(150, '\n');
        fecha_canales[n_canales] = date;
        n_canales++;
    }
    input.close();
}