/*Realizar un programa en “C” que contenga una función llamada registrarMedicion que permita cargar por teclado los datos de un reporte meteorológico:

Número de estación meteorológica (entero).
Temperatura registrada en °C (flotante).
Categoría del clima: 'S' para soleado, 'N' para nublado, 'L' para lluvioso (carácter).
La función no debe retornar ningún valor. Las tres variables deben estar declaradas en el main, ser modificadas dentro de la función y ser mostradas en la pantalla únicamente desde el main.*/

#include <stdio.h>
#include <stdlib.h>

void registrarMedicion(int *,float *,char *);

int main()
{
    int num;
    float temp;
    char clima;
    registrarMedicion(&num,&temp,&clima);
    printf("El numero de estacion es: %d\n",num);
    printf("La temperatura registrada es: %.2f\n",temp);
    printf("La categoria de clima es: %c\n",clima);

    return 0;

}

void registrarMedicion(int *num, float *temp, char *clima)
{
    printf("Ingrese el numero de estacion meteorologica: ");
    scanf("%d",num);
    printf("Ingrese la temperatura registrada: ");
    scanf("%f",temp);
    printf("Ingrese la categoria de clima: ");
    scanf(" %c",clima);
}