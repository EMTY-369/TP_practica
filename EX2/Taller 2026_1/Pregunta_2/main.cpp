



#include "Bibliotecas/Funciones.hpp"


int main() {
    ListaClientes lista_clientes, lista_saldos_positivos, lista_saldos_negativos;

    cargar_clientes("ArchivosDeDatos/clientes.csv", lista_clientes);
    imprimir_reporte("ArchivosDeReporte/InicialClientes.txt", "LISTADO INICIAL DE CLIENTES",
                     lista_clientes);
    cargar_cuentas("ArchivosDeDatos/cuentas.csv", lista_clientes);
    imprimir_reporte("ArchivosDeReporte/InicialClientesCuentas.txt", "LISTADO INICIAL DE CLIENTES Y CUENTAS",
                     lista_clientes);
    cargar_transacciones("ArchivosDeDatos/Transacciones.csv", lista_clientes);
    imprimir_reporte("ArchivosDeReporte/ReporteCompletoClientes.txt", "LISTADO COMPLETO DE CLIENTES",
                     lista_clientes);
    crear_listas(lista_clientes, lista_saldos_positivos, lista_saldos_negativos);
    imprimir_reporte("ArchivosDeReporte/ReporteClientesSaldoPositivo.txt", "LISTADO DE CLIENTES CON SALDO POSITIVO",
                     lista_saldos_positivos);
    imprimir_reporte("ArchivosDeReporte/ReporteClientesSaldoNegativo.txt", "LISTADO DE CLIENTES CON SALDO NEGATIVO",
                     lista_saldos_negativos);

    return 0;
}
