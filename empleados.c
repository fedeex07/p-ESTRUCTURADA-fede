/*Ejercicio 1. Se dispone del archivo binario empleados.dat con los siguientes datos por empleado:
Legajo (entero)
Nombre (50 caracteres)
Antigüedad (entero, en años)
Sueldo (float)
Turno (carácter: ‘M’ mañana, ‘T’ tarde, ’N’ noche)

Se solicita:
a) Actualizar el sueldo de los empleados del turno noche, aplicando un aumento del porcentaje ingresado por teclado. 
La actualización debe realizarse sobre el propio archivo, mientras se lee.
b) Calcular e informar, mediante funciones, la cantidad total de registros del archivo.
c) Copiar a otro archivo, veteranos.dat, el registro completo de todos los empleados con 20 años de antigüedad o más.
d) Explicar con sus propias palabras cómo es el proceso de eliminación física de un registro en un archivo binario.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 51

typedef struct 
{
    int legajo;
    char nombre[TXT];
    int antiguedad;
    float sueldo;
    char turno;

} EMPLEADOS;

FILE *abrirArchivo(char nombre[],char tipo[]);
void procesarArchivo();
void veterano(FILE *);
void leeyValidaFloat(float *,int,int);
int contarRegistros(FILE *,int);

int main()
{
    procesarArchivo();
    return 0;
}

void procesarArchivo()
{
    FILE *archEmpleados;
    EMPLEADOS auxEmpleados;
    float porcentaje,incremento;
    int cantEmp;
    archEmpleados=abrirArchivo("empleados.dat","r+b");
    printf("Ingrese el porcentaje de aumento a realizar(0-100): ");
    leeyValidaFloat(&porcentaje,0,100);
    fread(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
    while(!feof(archEmpleados))
    {
        if(auxEmpleados.turno == 'N')
        {
            incremento = (auxEmpleados.sueldo * porcentaje)/100.0;
            auxEmpleados.sueldo+=incremento;
            fseek(archEmpleados,-(long)sizeof(auxEmpleados),SEEK_CUR);
            fwrite(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
            fflush(archEmpleados);
        }
        fread(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
    }
    veterano(archEmpleados);
    cantEmp=contarRegistros(archEmpleados,sizeof(auxEmpleados));
    printf("La cantidad total de registros es de %d",cantEmp);
    fclose(archEmpleados);
}

void veterano(FILE *arch)
{
    EMPLEADOS auxEmpleados;
    FILE *archV;
    archV=abrirArchivo("veteranos.dat","wb");
    rewind(arch);
    fread(&auxEmpleados,sizeof(auxEmpleados),1,arch);
    while(!feof(arch))
    {
        if(auxEmpleados.antiguedad>=20)
        {
            fwrite(&auxEmpleados,sizeof(auxEmpleados),1,archV);
        }
        fread(&auxEmpleados,sizeof(auxEmpleados),1,arch);
    }
    fclose(archV);
}

int contarRegistros(FILE *arch,int tam)
{
    int cant;
    fseek(arch,0,SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
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