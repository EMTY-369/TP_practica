#include "Bibliotecas/Funciones.hpp"


int main() {
    Distrito *arr_distritos;
    Plato *arr_platos;
    Cliente *arr_clientes;
    int n_platos=0, n_clientes=0, n_distritos=0;

    cargar_platos_ofrecidos("ArchivosDeDatos/lab8_PlatosOfrecidos.csv",
                            arr_platos, n_platos);
    
    return 0;
}
