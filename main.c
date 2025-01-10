#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    int opcion;

    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                createFactura(); 
                break;
            case 2:
                readFacturas();
                break;
            case 3:
                printf("Ingrese la cedula para buscar la factura: ");
                int cedula;
                scanf("%d", &cedula);
                if (findByCedula(cedula) == -1) {
                    printf("Factura no encontrada.\n");
                }
                break;
            case 4:
                actualizarFactura();
                break;
            case 5:
                deleteFactura();
                break;
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}
