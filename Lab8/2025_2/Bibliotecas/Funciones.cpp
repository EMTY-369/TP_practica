//
// Created by User on 14/06/2026.
//

#include "Funciones.hpp"

void imprimir_duracion(int tiempo, ofstream & output) {
    int hora, minuto, segundo;
    hora = tiempo/3600;
    tiempo = tiempo%3600;
    minuto = tiempo/60;
    segundo = tiempo%60;
    output<<setfill('0')<<setw(2)<<hora<<":"<<setw(2)<<minuto<<":"<<setw(2)<<segundo<<setfill(' ');
}

void imprimir_reporte(const char * file_name, Categoria * arr_categorias, int cant_categorias) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    output<<fixed;
    output<<setprecision(2);
    centrear("REPORTE POR CATEGORIAS", ANCHO_REPORTE, true, output);
    for (int i = 0; i < cant_categorias; i++) {
        output<<"Codigo: "<<arr_categorias[i].codigo<<endl;
        output<<"Nombre: "<<arr_categorias[i].nombre<<endl;
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        output<<"REPRODUCCIONES: "<<endl;
        output<<left<<setw(4*ANCHO_REPORTE/8)<<"CANAL";
        output<<setw(2*ANCHO_REPORTE/8)<<"RATING";
        output<<setw(2*ANCHO_REPORTE/8)<<"DURACION"<<right<<endl;
        for (int j = 0; j < arr_categorias[i].numReproducciones; j++) {
            output<<left<<setw(4*ANCHO_REPORTE/8)<<arr_categorias[i].reproducciones[j].canal;
            output<<setw(2*ANCHO_REPORTE/8)<<arr_categorias[i].reproducciones[j].rating<<right;
            // imprimir_linea(2*ANCHO_REPORTE/16 + 6,' ',false,output);
            imprimir_duracion(arr_categorias[i].reproducciones[j].duracion, output);
            output<<endl;
        }
        imprimir_linea(ANCHO_REPORTE, '-', true, output);
        output<<"RATING PROMEDIO: "<<arr_categorias[i].promedioRating<<endl;
        output<<"DURACION TOTAL: ";
        imprimir_duracion(arr_categorias[i].duracionTotal, output);
        output<<endl;
        imprimir_linea(ANCHO_REPORTE, '=', true, output);
    }
    output.close();
}

void calculo_rating_prom_y_duraciones(Categoria * arr_categorias, int cant_categorias) {
    for (int i = 0; i < cant_categorias; i++) {
        if (arr_categorias[i].numReproducciones!=0) {
            for (int j = 0; j < arr_categorias[i].numReproducciones; j++) {
                arr_categorias[i].promedioRating += arr_categorias[i].reproducciones[j].rating;
                arr_categorias[i].duracionTotal += arr_categorias[i].reproducciones[j].duracion;
            }
            arr_categorias[i].promedioRating /= arr_categorias[i].numReproducciones;
        }
    }
}

int buscar_categoria(char * codigo, Categoria * arr_categorias, int cant_categorias) {
    for (int i = 0; i < cant_categorias; i++) {
        if (strcmp(arr_categorias[i].codigo, codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}

double leer_double( ifstream & input) {
    double dato;
    input>>dato;
    input.ignore();
    return dato;
}

int leer_duracion( ifstream & input) {
    int hora, minuto, segundo;
    char c;
    input>>hora>>c>>minuto>>c>>segundo;

    return hora*3600+minuto*60+segundo;
}

void cargar_streams_reproducidos(const char * file_name, Categoria *&arr_categorias, int cant_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);

    char *canal, codigo[9]{},c;
    int pos_categoria;
    while (true) {
        canal = leer_candena(input, ',');
        if (canal == nullptr or input.eof()) {
            delete [] canal;
            break;
        }
        input>>codigo>>c;
        pos_categoria=buscar_categoria(codigo, arr_categorias, cant_categorias);
        if (pos_categoria == NO_ENCONTRADO) {
            input.ignore(100, '\n');
            continue;
        }
        int n=arr_categorias[pos_categoria].numReproducciones;
        if (n==0) arr_categorias[pos_categoria].reproducciones = new Reproduccion[MAX_REPRODUCCIONES]{};
        arr_categorias[pos_categoria].reproducciones[n].rating=leer_double(input);
        arr_categorias[pos_categoria].reproducciones[n].duracion=leer_duracion(input);
        arr_categorias[pos_categoria].reproducciones[n].canal=canal;
        arr_categorias[pos_categoria].numReproducciones ++;
    }
}

void abrir_archivo_salida(const char * file_name, ofstream & output) {
    output.open(file_name, ios::out);
    if (not output.is_open()) {
        cout << "Error al abrir el archivo salida:" << file_name << endl;
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

void prueba_categorias(const char * file_name, const char *titulo, Categoria * arr_categorias, int cant_categorias, bool report1) {
    ofstream output;
    abrir_archivo_salida(file_name, output);
    centrear(titulo, 80, true, output);
    for (int i = 0; i < cant_categorias; i++) {
        if ((not report1) or i==0) {
            imprimir_linea(80, '=', true, output);
            output<<left<<setw(30)<<"CODIGO"<<setw(50)<<"NOMBRE"<<endl;

        }
        output<<setw(30)<<arr_categorias[i].codigo<<setw(50)<<arr_categorias[i].nombre<<endl;
        if (not report1) {
            imprimir_linea(80, '-', true, output);
            output<<setw(30)<<"CANAL"<<setw(20)<<"RATING"<<setw(30)<<"DURACION"<<endl;
            for (int j = 0; j < arr_categorias[i].numReproducciones; j++) {
                // imprimir_linea(5,' ', false, output);
                output<<setw(30)<<arr_categorias[i].reproducciones[j].canal;
                output<<setw(20)<<arr_categorias[i].reproducciones[j].rating;
                output<<setw(30)<<arr_categorias[i].reproducciones[j].duracion<<endl;
            }

        }
    }
    output<<right;
    output.close();
}

void abrir_archivo_entrada(const char * file_name, ifstream & input) {
    input.open(file_name, ios::in);
    if (not input.is_open()) {
        cout << "Error al abrir el archivo de entrada:" << file_name << endl;
        exit(1);
    }
}

char * leer_candena( ifstream & input, char del) {
    char buffer[150]{}, *cadena;
    input>>ws;
    input.getline(buffer, 150, del);
    if (input.eof()) return nullptr;
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void cargar_categorias(const char * file_name, Categoria *&arr_categorias, int &cant_categorias) {
    ifstream input;
    abrir_archivo_entrada(file_name, input);
    arr_categorias = new Categoria[MAX_CATEGORIAS]{};

    char codigo[9]{};
    while (true) {
        input>>codigo;
        if (input.eof()) break;
        input.ignore();
        arr_categorias[cant_categorias].nombre = leer_candena(input, '\n');
        // cout<<arr_categorias[cant_categorias].nombre<<endl;
        strcpy(arr_categorias[cant_categorias].codigo, codigo);
        cant_categorias++;
    }
    input.close();
}
