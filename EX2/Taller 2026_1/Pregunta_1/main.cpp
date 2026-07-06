


#include "Bibliotecas/Funciones.hpp"


int main() {
    TipoCliente *arr_tipos_clientes;
    Cliente *arr_clientes;
    int n_tipos_clientes=0, n_clientes=0;

    cargar_tipos_cliente("ArchivosDeDatos/TiposCliente.txt",
                         arr_tipos_clientes, n_tipos_clientes);
    prueba_carga_tipos_cliente("ArchivosDeReporte/prueba_carga_tipoCliente.txt",
                               arr_tipos_clientes, n_tipos_clientes);
    cargar_clientes("ArchivosDeDatos/clientes.csv",
                    arr_clientes, n_clientes, arr_tipos_clientes, n_tipos_clientes);
    imprimir_reporte("ArchivosDeReporte/InicialClientes.txt", arr_clientes, n_clientes);
    cargar_cuentas("ArchivosDeDatos/cuentas.csv", arr_clientes, n_clientes);
    imprimir_reporte("ArchivosDeReporte/InicialClientesyCuentas.txt", arr_clientes, n_clientes);
    cargar_transacciones("ArchivosDeDatos/Transacciones.csv",arr_clientes, n_clientes);
    imprimir_reporte("ArchivosDeReporte/ReporteCompletoClientesyCuentas.txt", arr_clientes, n_clientes);
    ordenar_clientes(arr_clientes, n_clientes);
    imprimir_reporte("ArchivosDeReporte/ReporteClientesyCuentasOrdenado.txt", arr_clientes, n_clientes);
    return 0;
}
