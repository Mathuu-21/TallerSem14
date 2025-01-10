struct Producto
{
    char nombre[50];
    float precio;
    int cantidad;
};

struct Factura
{
    char nombre[20];
    int cedula;
    int nProductos;
    struct Producto productos[5];
    float total;
    int eliminada;
    int activa;
};
int menu();
void safeFactura (struct Factura *factura);
int findByCedula (int cedula);
void updateFactura (struct Factura *factura, int pos);
void findFactura ();
void deleteFactura ();
void leerCadena (char *cadena, int longitud);
void createFactura ();
void readFacturas ();
void actualizarFactura ();
