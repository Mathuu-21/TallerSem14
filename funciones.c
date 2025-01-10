#include <stdio.h>
#include "funciones.h"
#include <string.h>
int menu() {
    int opcion;
    do {
        printf("1. Crear factura\n");
        printf("2. Leer facturas\n");
        printf("3. Buscar factura\n");
        printf("4. Actualizar factura\n");
        printf("5. Eliminar factura\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        if (opcion < 1 || opcion > 6) {
            printf("Error: Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion < 1 || opcion > 6);
    return opcion;
}

void safeFactura (struct Factura *factura){
    FILE *F;
    F = fopen("facturas.dat", "ab+");
    if (F == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }else{
    fwrite(factura, sizeof(struct Factura), 1, F);
    printf("Factura guardada con exito\n");
    }
    fclose(F);

}

void updateFactura (struct Factura *factura, int pos){
    FILE *F;
    struct Factura facturaAux;
    F = fopen("facturas.dat", "rb+");
    if (F == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }else{
        fseek(F,pos,0);
        fwrite(factura, sizeof(struct Factura), 1, F);
        printf("Factura actualizada con exito\n");
    }
    fclose(F);
}

int findByCedula (int cedula){
    int pos = -1, f = 0;
    FILE *F;
    struct Factura factura;
    F = fopen("facturas.dat", "rb");
    if (F == NULL){
        printf("Error al abrir el archivo\n");
        return -1;
    }else{
        while (fread(&factura, sizeof(struct Factura), 1, F)){
        if (factura.cedula == cedula){
            f = 1;
            printf("Nombre\t\tCedula\n");
            printf("%s\t\t%d\n", factura.nombre, factura.cedula);
            printf("#\t\tNombre\t\tPrecio\t\tCantidad\n");
            for (int i = 0; i < factura.nProductos; i++) {
                printf("%d\t\t%s\t\t%.2f\t\t%d\n", i + 1, factura.productos[i].nombre, 
                        factura.productos[i].precio,factura.productos[i].cantidad);
            }
            break;
        }
        pos = ftell(F);
        }
    }
    if (f == 0)
    {
        printf("No se encontro la factura\n");
        pos = -1;
    }
    fclose(F);
    return pos;
}

void actualizarFactura() {
    int cedula, pos;
    struct Factura factura;

    printf("Ingrese la cedula del cliente: ");
    scanf("%d", &cedula);

    if (cedula < 0) {
        printf("Error: La cédula no puede ser un número negativo.\n");
        return;
    }

    pos = findByCedula(cedula);

    if (pos != -1) {
        printf("Ingrese el nombre actualizado del cliente: ");
        leerCadena(factura.nombre, 20);

        printf("Ingrese el número actualizado de productos: ");
        scanf("%d", &factura.nProductos);

        if (factura.nProductos < 0) {
            printf("Error: El número de productos no puede ser negativo.\n");
            return;
        }

        for (int i = 0; i < factura.nProductos; i++) {
            printf("Ingrese el nombre del producto %d: ", i + 1);
            scanf("%s", factura.productos[i].nombre);

            printf("Ingrese el precio del producto %d: ", i + 1);
            scanf("%f", &factura.productos[i].precio);

            if (factura.productos[i].precio < 0) {
                printf("Error: El precio no puede ser negativo.\n");
                return;
            }

            printf("Ingrese la cantidad del producto %d: ", i + 1);
            scanf("%d", &factura.productos[i].cantidad);

            if (factura.productos[i].cantidad < 0) {
                printf("Error: La cantidad no puede ser negativa.\n");
                return;
            }
        }

        factura.total = 0;
        for (int i = 0; i < factura.nProductos; i++) {
            factura.total += factura.productos[i].precio * factura.productos[i].cantidad;
        }

        factura.cedula = cedula;

        updateFactura(&factura, pos);
    }
}

void deleteFactura() {
    int cedula, pos;
    FILE *F;
    struct Factura factura;

    printf("Ingrese la cédula del cliente a eliminar: ");
    scanf("%d", &cedula);

    pos = findByCedula(cedula); // Encontrar posición de la factura
    if (pos != -1) {
        F = fopen("facturas.dat", "rb+"); // Abrir en modo lectura-escritura
        if (F == NULL) {
            printf("Error al abrir el archivo\n");
            return;
        }

        fseek(F, pos, SEEK_SET); // Moverse a la posición de la factura encontrada
        fread(&factura, sizeof(struct Factura), 1, F);

        if (factura.activa == 0) {
            printf("La factura ya está eliminada.\n");
        } else {
            factura.activa = 0; // Marcar como eliminada
            fseek(F, pos, SEEK_SET); // Volver a la posición inicial
            fwrite(&factura, sizeof(struct Factura), 1, F);
            printf("Factura eliminada correctamente (marcada como inactiva).\n");
        }

        fclose(F);
    } else {
        printf("No se encontró ninguna factura con la cédula ingresada.\n");
    }
}
   
void leerCadena (char *cadena, int longitud){
    fflush(stdin);
    fgets(cadena, longitud, stdin);
    int len = strlen(cadena)-1;
    cadena[len] = '\0';
    }
    
void createFactura() {
    struct Factura factura;

    printf("Ingrese el nombre del cliente: ");
    leerCadena(factura.nombre, 20);

    do {
        printf("Ingrese la cedula del cliente: ");
        scanf("%d", &factura.cedula);
        if (factura.cedula < 0) {
            printf("Error: La cedula no puede ser negativa. Intente de nuevo.\n");
        }
    } while (factura.cedula < 0);

    do {
        printf("Ingrese el numero de productos: ");
        scanf("%d", &factura.nProductos);
        if (factura.nProductos < 0) {
            printf("Error: El numero de productos no puede ser negativo. Intente de nuevo.\n");
        }
    } while (factura.nProductos < 0);

    for (int i = 0; i < factura.nProductos; i++) {
        printf("Ingrese el nombre del producto %d: ", i + 1);
        scanf("%s", factura.productos[i].nombre);

        do {
            printf("Ingrese el precio del producto %d: ", i + 1);
            scanf("%f", &factura.productos[i].precio);
            if (factura.productos[i].precio < 0) {
                printf("Error: El precio no puede ser negativo. Intente de nuevo.\n");
            }
        } while (factura.productos[i].precio < 0);

        do {
            printf("Ingrese la cantidad del producto %d: ", i + 1);
            scanf("%d", &factura.productos[i].cantidad);
            if (factura.productos[i].cantidad < 0) {
                printf("Error: La cantidad no puede ser negativa. Intente de nuevo.\n");
            }
        } while (factura.productos[i].cantidad < 0);
    }

    factura.total = 0;
    for (int i = 0; i < factura.nProductos; i++) {
        factura.total += factura.productos[i].precio * factura.productos[i].cantidad;
    }
    safeFactura(&factura);
}

void readFacturas() {
    FILE *F;
    struct Factura factura;
    F = fopen("facturas.dat", "rb");

    if (F == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }else{
        while (fread(&factura, sizeof(struct Factura), 1, F))
        
        if (factura.activa == 1) {
            printf("Nombre: %s\n", factura.nombre);
            printf("Cedula: %d\n", factura.cedula);
            printf("#\t\tNombre\t\tPrecio\t\tCantidad\n");
            for (int i = 0; i < factura.nProductos; i++) { 
            printf("%d\t\t%s\t\t%.2f\t\t%d\n", i + 1, factura.productos[i].nombre, 
                        factura.productos[i].precio,factura.productos[i].cantidad);
    }
    printf("Total: %.2f\n", factura.total);
        }
}
fclose(F);
}