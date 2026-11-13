/*En una ferretería se cuenta con un archivo binario llamado Productos.dat que contiene los productos comercializados. Se definió la siguiente estructura para el archivo:
codigo (entero)
descripcion (hasta 50 caracteres)
categoria (entero: 1 = Herramientas, 2 = Pinturas, 3 = Electricidad)
precio (float)
Debido a cambios en los costos de proveedores, se solicita realizar un programa en C que:
Ajuste masivo de precios: Solicite por teclado un porcentaje de aumento y el número de categoría a la cual aplicarlo. Actualice en el propio archivo Productos.dat
únicamente el precio de los productos que pertenezcan a esa categoría.
Conteo e informe: Informe por pantalla la cantidad total de registros grabados 
en el archivo y cuántos productos pertenecen a la categoría actualizada.
Exportación: Genere un archivo de texto plano denominado productos_actualizados.csv con encabezados
(Codigo;Descripcion;Categoria;Precio) que contenga el catálogo
completo con los precios ya ajustados.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 51

typedef struct 
{
    int codigo;
    char desc[TXT];
    int categoria;
    float precio;

} PRODUCTOS;

void procesarArchivo();
FILE *abrirArchivo(char nombre[],char tipo[]);
void leeyValidaFloat(float *,int,int);
void leeyValidaInt(int *);
void exportar();
int contarRegistros(FILE *,int);

int main()
{
    procesarArchivo();
    exportar();
    return 0;   
}

void procesarArchivo()
{
    FILE *archProductos;
    PRODUCTOS auxProductos;
    float porcenteje,incremento;
    int cantR,cantP,catAux;
    archProductos=abrirArchivo("Productos.dat","r+b");

    printf("Ingrese el porcentaje de aumento(0-100): ");
    leeyValidaFloat(&porcenteje,0,100);
    printf("Ingrese el numero de categoria(1-2-3): ");
    leeyValidaInt(&catAux);
    fread(&auxProductos,sizeof(auxProductos),1,archProductos);
    while(!feof(archProductos))
    {
        if(auxProductos.categoria == catAux)
        {
            incremento = (auxProductos.precio * porcenteje)/100.0;
            auxProductos.precio += incremento;
            cantP++;
            fseek(archProductos,-(long)sizeof(auxProductos),SEEK_CUR);
            fwrite(&auxProductos,sizeof(auxProductos),1,archProductos);
            fflush(archProductos);
        }
        fread(&auxProductos,sizeof(auxProductos),1,archProductos);
    }
    cantR=contarRegistros(archProductos,sizeof(auxProductos));
    fclose(archProductos);

    printf("Los productos de la categoria actualizada son: %d",cantP);
    printf("La cantidad de registros garbados son: %d",cantR);
}

void exportar()
{
    FILE *archProductos, *archExp;
    PRODUCTOS auxProductos;
    archProductos=abrirArchivo("productos.dat","rb");
    archExp=abrirArchivo("productos_actualizados.csv","wt");
    fprintf(archExp,"Codigo;Descripcion;Categoria;Precio");
    fread(&auxProductos,sizeof(auxProductos),1,archProductos);
    while(!feof(archProductos))
    {
        fprintf(archExp,"%d,%s,%d,%.2f\n",auxProductos.codigo,auxProductos.desc,auxProductos.categoria,auxProductos.precio);
        fread(&auxProductos,sizeof(auxProductos),1,archProductos);
    }
    fclose(archExp);
    fclose(archProductos);
}

int contarRegistros(FILE *arch,int tam)
{
    int cant;
    fseek(arch,0,SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
}

void leeyValidaInt(int *dato)
{
    scanf("%d",dato);
    while(*dato != 1 && *dato !=2 && *dato !=3)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
}

void leeyValidaFloat(float *dato,int min,int max)
{
    scanf("%f",dato);
    while(*dato < min || *dato > max)
    {
        printf("Error. Reingrese: ");
        scanf("%f",dato);
    }
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