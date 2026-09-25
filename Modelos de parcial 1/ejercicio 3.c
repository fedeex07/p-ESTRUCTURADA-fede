/*Ejercicio 1 Un local de electrodomésticos necesita un programa para actualizar el inventario y las ventas mensuales de sus artículos.
Primeramente, se ingresa la información de los productos existentes, cada uno compuesto por:
·       Código (entero)
·       Descripción (cadena de hasta 30 caracteres)
·       Precio Unitario (número real)
·       Unidades Vendidas (acumuladas hasta el mes anterior, entero)
·       Monto Total Recaudado (acumulado hasta el mes anterior, real)
Se sabe que el comercio maneja un máximo de 80 productos. La carga inicial de productos finaliza cuando se ingresa un código 0 .
A continuación, se procesan los comprobantes de venta del mes actual. Por cada venta se ingresa:
•             Código de Producto (entero)
•             Cantidad Vendida (entero)
El ingreso de las ventas del mes finaliza cuando la cantidad vendida es igual a 0. Validar los datos ingresados
Se solicita:
1. Actualización: Por cada venta procesada, buscar el producto por su código y actualizar la cantidad total de unidades vendidas y el importe total recaudado. (Nota: Si el código ingresado no existe, mostrar un mensaje de advertencia).
2. Listado Final: Al terminar el ingreso de ventas, emitir un informe con todos los productos registrados que contenga:
CÓDIGO: XXXXX DESCRIPCIÓN: XXXXXXXXXXXXXXXXXXXXXXXXXX | UNIDADES TOTALES: XXXX | MONTO TOTAL: $XXXXX.XX 

Al finalizar el procesamiento de ventas, se requiere almacenar en memoria un resumen histórico con el monto total abonado por cada una de las ventas procesadas.
Solicite al usuario la cantidad V de ventas que se realizaron.
Reserve dinámicamente un arreglo de números reales (float) para V elementos
Realice la validación correspondiente para verificar si la memoria fue asignada con éxito.
Libere la memoria al finalizar*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TXT 31
#define TAM 80

typedef struct 
{
    int codigo;
    char descripcion[TXT];
    float precioU;
    int UnidadesV;
    float MontoR;

} PRODUCTO;

typedef struct 
{
    int cod;
    int cantV;
} VENTAS;

PRODUCTO CargarDatos(PRODUCTO [],int);
int IngresoProd(PRODUCTO[],int);
void CargarVentas(PRODUCTO[],int);
void listado(PRODUCTO[],int);
int busqueda(PRODUCTO[],int,int);
void leeyValidaInt(int *,int);
void leeyValidaFloat(float *,int);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    PRODUCTO datos[TAM];
    int cantProductos;
    cantProductos=IngresoProd(datos,TAM);
    CargarVentas(datos,cantProductos);
    listado(datos,cantProductos);
}

PRODUCTO CargarDatos(PRODUCTO datos[],int i)
{
    PRODUCTO aux;
    printf("Ingrese el codigo de producto: ");
    leeyValidaInt(&aux.codigo,0);
    if(aux.codigo != 0)
    {
        while(busqueda(datos,aux.codigo,i) != -1)
        {
            printf("El codigo ya fue ingresado. Reingrese: ");
            leeyValidaInt(&aux.codigo,0);
        }
        if(aux.codigo !=0)
        {
            printf("Ingrese la descripcion: ");
            leeryValidarTexto(aux.descripcion,TXT);
            printf("Ingrese el precio unitario: ");
            leeyValidaFloat(&aux.precioU,0);
            printf("Ingrese las unidades vendidas acumuladas hasta el mes anterior: ");
            leeyValidaInt(&aux.UnidadesV,0);
            printf("Ingrese total recaudado acumulado hasta el mes anterior: ");
            leeyValidaFloat(&aux.MontoR,0);
        }

    }
    return aux;
}

int IngresoProd(PRODUCTO datos[],int ce)
{
    PRODUCTO aux;
    int i=0;
    printf("--Ingreso de productos--\n");
    aux=CargarDatos(datos,i);
    while(aux.codigo != 0 && i<ce)
    {
        datos[i]=aux;
        i++;
        aux=CargarDatos(datos,i);
    }
    return i;
}

void CargarVentas(PRODUCTO datos[],int ce)
{
    VENTAS info;
    float *v;
    int pos, cantVentas;
    printf("--Ingreso Ventas--\n");
    printf("Ingrese la cantidad vendida: ");
    leeyValidaInt(&info.cantV,0);
    while(info.cantV != 0)
    {
        printf("Ingrese el codigo de producto: ");
        leeyValidaInt(&info.cod,0);
        pos=busqueda(datos,info.cod,ce);
        if(pos != -1)
        {
            datos[pos].UnidadesV+=info.cantV;
            datos[pos].MontoR+=(float)(datos[pos].precioU*info.cantV);
            printf("Venta procesada con exito.\n");
        } else{
            printf("El codigo no existe.");
        }

        printf("Ingrese la cantidad vendida: ");
        leeyValidaInt(&info.cantV,0);
    }
    printf("Ingrese la cantidad de ventas que se realizaron: ");
    scanf("%d",&cantVentas);
    v=(float*)malloc(cantVentas*sizeof(float));
    if(v==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }

    free(v);
}

void listado(PRODUCTO datos[],int ce)
{
  for(int i=0;i<ce;i++)
  {
    printf("CODIGO: %d DESCRIPCION %s | UNIDADES TOTALES: %d | MONTO TOTAL: %.2f\n",datos[i].codigo,datos[i].descripcion,datos[i].UnidadesV,datos[i].MontoR);
  }
}




int busqueda(PRODUCTO datos[],int cod, int ce)
{
    int pos =-1,i=0;
    while(pos==-1 && i<ce)
    {
        if(datos[i].codigo==cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeyValidaInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato < lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }

}

void leeyValidaFloat(float *dato,int lim)
{
    scanf("%f",dato);
    while(*dato < lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f",dato);
    }
}

void leerTexto(char texto[],int largo)
{
    int i=0;
    fflush(stdin);
    fgets(texto,largo,stdin);
    while(texto[i] != '\0')
    {
        if(texto[i] == '\n')
        {
            texto[i] = '\0';
        }
        i++;
    }
}

void leeryValidarTexto(char texto[],int largo)
{
    leerTexto(texto,largo);
    while(strlen(texto)==0)
    {
        printf("El texto ingresado es incorrecto. Reingrese: ");
        leerTexto(texto,largo);
    }
}