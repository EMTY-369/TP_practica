#include "Bibliotecas/Funciones.hpp"



int main() {
    Distrito *arr_distritos;
    Plato *arr_platos;
    Cliente *arr_clientes;
    int n_platos=0, n_clientes=0, n_distritos=0;

    cargar_platos_ofrecidos("ArchivosDeDatos/lab8_PlatosOfrecidos.csv",
                            arr_platos, n_platos);
    cargar_distritos("ArchivosDeDatos/lab8_Distritos.csv",
                     arr_distritos, n_distritos);
    cargar_clientes("ArchivosDeDatos/lab8_Clientes.csv",
                    arr_clientes, n_clientes);
    prueba_carga_platos_ofrecidos("ArchivosDeReporte/prueba_carga_platos_ofrecidos.txt",
                                  arr_platos, n_platos);
    prueba_carga_distritos("ArchivosDeReporte/prueba_carga_distritos.txt",
                           arr_distritos, n_distritos);
    prueba_carga_clientes("ArchivosDeReporte/prueba_carga_clientes.txt",
                           arr_clientes, n_clientes);
    cargar_clientes_pedidos("ArchivosDeDatos/lab8_PedidosRealizados.txt",
                            arr_clientes, n_clientes,
                            arr_distritos, n_distritos,
                            arr_platos, n_platos);
    ordenar_clientes_nombre(arr_clientes, n_clientes);
    ordenar_platos_pedidos(arr_clientes, n_clientes);

    imprimir_reporte("ArchivosDeReporte/Pedidos_Atendidos.txt",
                     arr_clientes, n_clientes, arr_platos, n_platos);

    return 0;
}
