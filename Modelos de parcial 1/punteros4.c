/*Un club de atletismo registra los tiempos (en segundos, con decimales) de los corredores en una carrera de 10K. 
Se cargan por teclado los tiempos de un vector fijo de 15 corredores.

Se solicita:
a) Una función llamada buscarPunteroAlMejorTiempo que reciba el vector y su tamaño, y 
retorne un puntero a la posición del menor tiempo registrado (el mejor tiempo es único).

b) Una función llamada promediarPorPuntero que reciba el vector y su tamaño, y calcule el promedio de todos los tiempos 
recorriendo el vector exclusivamente mediante aritmética de punteros (sin usar [i] en ningún lado del recorrido).

c) En el main, mostrar el mejor tiempo (accediendo solo a través del puntero devuelto), 
la posición que ocupa dentro del vector (calculada por resta de punteros, no por un contador de recorrido) y el promedio general.*/

#include <stdio.h>
#include <stdlib.h>
#define TAM 15

void ingreso(float *,int);
float *buscarPunteroAlMejorTiempo(float *,int);
float promediarPorPuntero(float *,int);
void leeyValidafloat(float *,int);

int main()
{
    float corredores[TAM];
    float *pv=corredores,prom;
    float *posmenor;
    ingreso(pv,TAM);
    posmenor=buscarPunteroAlMejorTiempo(pv,TAM);
    printf("El mejor tiempo fue %.2f en la posicion %d\n",*(posmenor),(posmenor-pv)+1);
    prom=promediarPorPuntero(pv,TAM);
    printf("El promedio genereal fue %.2f",prom);

    return 0;
}

void ingreso(float *pv,int ce)
{
    int i;
    for(i=0;i<ce;i++)
    {
        printf("Ingrese el tiempo del corredor: ");
        leeyValidafloat(pv+i,0);
    }
}

float promediarPorPuntero(float *pv,int ce)
{
    float prom;
    float total=0;
    for(int i=0;i<ce;i++)
    {
        total+=*(pv+i);

    }
    prom=(float)(total/ce);
    return prom;
}

float *buscarPunteroAlMejorTiempo(float *pv,int ce)
{
    float min=*pv, *pr=pv;
    for(int i=0;i<ce;i++)
    {
        if(*(pv+i)<min)
        {
            min=*(pv+i);
            pr=pv+i;
        }
    }
    return pr;
}


void leeyValidafloat(float *dato,int lim)
{
    scanf("%f",dato);
    while(*dato<lim)
    {
        printf("Error.Reingrese: ");
        scanf("%f",dato);
    }
}