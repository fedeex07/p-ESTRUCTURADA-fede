/*Ejercicio 3. Se dispone del archivo binario ventas.dat, ordenado por sucursal, con los siguientes datos por venta:
Sucursal (entero)
Monto (float)
Número de ticket (entero)

Se solicita:
a) Mediante corte de control por sucursal, informar el promedio de monto por sucursal. 
   El cálculo del promedio debe realizarse en otra función.
b) Informar la sucursal con mayor monto de ventas en total (sumando todos los montos de cada sucursal).*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int sucursal;
    float monto;
    int ticket;

} VENTAS;

void procesarArchivo();
FILE *abrirArchivo(char nombre[],char tipo[]);
float promedio(float,int);

int main()
{
    void procesaArchivo();
    
    return 0;
}

void procesarArchivo()
{
    FILE *archVentas;
    VENTAS auxVentas;
    int sucuAnterior,cantVentas,primeraSuc=1,sucMayor;
    float promedioxSuc,montoTotalXSuc,mayorTotal;
    
    archVentas=abrirArchivo("ventas.dat","rb");
    fread(&auxVentas,sizeof(auxVentas),1,archVentas);
    while(!feof(archVentas))
    {
        sucuAnterior=auxVentas.sucursal;
        cantVentas=0;
        montoTotalXSuc=0;
        promedioxSuc=0;
        while(!feof(archVentas) && sucuAnterior==auxVentas.sucursal)
        {
            montoTotalXSuc=auxVentas.monto;
            cantVentas++;
            fread(&auxVentas,sizeof(auxVentas),1,archVentas);
        }

        promedioxSuc=promedio(montoTotalXSuc,cantVentas);
        printf("Sucursal: %d - Promedio: %.2f\n",sucuAnterior,promedioxSuc);

        if(primeraSuc==1 || montoTotalXSuc > mayorTotal)
        {
            mayorTotal=montoTotalXSuc;
            sucMayor=sucuAnterior;
            primeraSuc=0;
        }
    }
    printf("La sucursal %d tiene mayor monto de ventas total con %.2f\n",sucMayor,mayorTotal);
    fclose(archVentas);
}


float promedio(float montoXSuc,int cantV)
{
    float prom;
    prom=montoXSuc/cantV;
    return prom;

}

FILE *abrirArchivo(char nombre[],char tipo[])
{
    FILE *fp;
    fp=fopen(nombre,tipo);
    if(fp==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    return fp;
}