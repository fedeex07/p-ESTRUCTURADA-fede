/*La librería "Ateneo Universitario" almacena la lista de libros en el archivo binario Libros.dat utilizando la siguiente estructura:
codigo (entero)
titulo (hasta 50 caracteres)
precio (float)
Para incentivar las ventas o ajustar márgenes, la librería requiere un programa en C que realice lo siguiente:
Ajuste condicional de precios: Solicite un valor límite de precio y un porcentaje de ajuste. Si el libro tiene un precio inferior al limite
ingresado, se le aplicará un incremento. Si supera o iguala dicho valor, el precio no se modificará. La actualización debe realizarse sobre el archivo Libros.dat.
Informar la cantidad total de libros registrados utilizando cálculo directo sobre la longitud total del archivo binario con las funciones vistas en el curso
Exportación en formato CSV: Generar el archivo libros_actualizados.csv con los títulos de las columnas (Codigo,Titulo,Precio) separado por comas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 51

typedef struct 
{
    int codigo;
    char titulo[TXT];
    float precio;

} LIBROS;

FILE *abrirArchivo(char nombre[],char tipo[]);
void leeyValidaFloat(float *,int,int);
void leeyValidaFloat2(float *,int);
void procesarArchivo();
void exportar();
int contarRegistros(FILE *arch,int tam);

int main()
{
    procesarArchivo();
    exportar();
    return 0;
}

void procesarArchivo()
{
    FILE *archLibros;
    LIBROS auxLibros;
    float porcentaje,incremento,precioAux;
    int cantR;

    archLibros=abrirArchivo("Libros.dat","r+b");

    printf("Ingresar un limite de precio: ");
    leeyValidaFloat2(&precioAux,0);
    printf("Ingrese un porcentaje de ajuste(0-100): ");
    leeyValidaFloat(&porcentaje,0,100);
    fread(&auxLibros,sizeof(auxLibros),1,archLibros);
    while(!feof(archLibros))
    {
        if(auxLibros.precio < precioAux)
        {
            incremento=(auxLibros.precio * porcentaje)/100.0;
            auxLibros.precio += incremento;
            fseek(archLibros,-(long)sizeof(auxLibros),SEEK_CUR);
            fwrite(&auxLibros,sizeof(auxLibros),1,archLibros);
            fflush(archLibros);
        }
        fread(&auxLibros,sizeof(auxLibros),1,archLibros);
    }
    cantR=contarRegistros(archLibros,sizeof(auxLibros));
    fclose(archLibros);

    printf("La cantidad de registros fue de %d",cantR);
}

void exportar()
{
    FILE *archLibros,*archExp;
    LIBROS auxLibros;
    archLibros=abrirArchivo("Libros.dat","rb");
    archExp=abrirArchivo("libros_actualizados.csv","wt");
    fprintf(archExp,"Codigo,Titulo,Precio\n");
    fread(&auxLibros,sizeof(auxLibros),1,archLibros);
    while(!feof(archLibros))
    {
        fprintf(archExp,"%d,%s,%.2f\n",auxLibros.codigo,auxLibros.titulo,auxLibros.precio);
        fread(&auxLibros,sizeof(auxLibros),1,archLibros);
    }
    fclose(archLibros);
    fclose(archExp);
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

void leeyValidaFloat(float *dato,int min,int max)
{
    scanf("%f",dato);
    while(*dato < min && *dato > max)
    {
        printf("Error. Reingrese: ");
        scanf("%f",dato);
    }
}

void leeyValidaFloat2(float *dato,int lim)
{
    scanf("%f",dato);
    while(*dato < lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f",dato);
    }
}

int contarRegistros(FILE *arch,int tam)
{
    int cant;
    fseek(arch,0,SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
}