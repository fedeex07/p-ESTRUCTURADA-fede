/*/*Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    float precio;
    char desc[51];

} PRODUCTOS;

FILE *abrirArchivo(char nombre[],char tipo[]);
void procesarArchivo();
int eliminar(int codigo);
void leeyValidaInt(int *dato,int lim);

int main()
{
    procesarArchivo();
    return 0;
}

void procesarArchivo()
{
    FILE *archProductos;
    PRODUCTOS auxProductos;
    int codigo;

    printf("Ingrese el codigo de producto a eliminar(0 para finalizar): ");
    leeyValidaInt(&codigo,0);
    while(codigo != 0)
    {
        if(eliminar(codigo))
        {
            printf("Producto eliminado.\n");
        }
        else
        {
            printf("Producto no encontrado.\n");
        }
        printf("Ingrese el codigo de producto a eliminar(0 para finalizar): ");
        leeyValidaInt(&codigo,0);
    }
    fclose(archProductos);
}

int eliminar(int codigo)
{
    PRODUCTOS aux;
    FILE *fpTemp,*fpOrig;
    int encontrado=0;

    fpOrig=abrirArchivo("productos.dat","rb");
    fpTemp=abrirArchivo("Temporal.dat","wb");

    fread(&aux,sizeof(aux),1,fpOrig);
    while(!feof(fpOrig))
    {
        if(aux.codigo == codigo)
        {
            encontrado=1;
        }
        else
        {
            fwrite(&aux,sizeof(aux),1,fpTemp);
        }
        fread(&aux,sizeof(aux),1,fpOrig);
    }

    if(encontrado==1)
    {
        remove("productos.dat");
        rename("Temporal.dat","productos.dat");
    }
    else
    {
        remove("Temporal.dat");
    }
    return encontrado;
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

void leeyValidaInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato < lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
}