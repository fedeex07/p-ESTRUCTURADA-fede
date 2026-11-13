/*Se tiene un archivo binario que registra los sueldos de los empleados de una empresa
Con el siguiente diseño de registro
Legajo( int)
Nombre(45)
Antigüedad (en años int)
Sueldo básico (float)
Area( char 'A': administración, 'P': producción, 'C' comercial)
Realizar un programa en C que permita modificar directamente sobre el archivo (llamado sueldos.dat)los sueldos básicos de
los empleados según la siguiente escala de antigüedad
Mayor a 10 años 5%
Mayor a 20 años 6%
Una vez actualizado se debe generar un nuevo archivo, que solo contenga a los empleados del área administrativa
e informar la cantidad de registros de dicho archivo, utilizando las funciones vistas en el curso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 46

typedef struct 
{
    int legajo;
    char nombre[TXT];
    int antiguedad;
    float sueldo;
    char area;

} EMPLEADOS;

void procesarArchivo();
void nuevoArchivo();
FILE *abrirArchivo(char[],char[]);
int contarRegistros(FILE *,int);

int main()
{
    procesarArchivo();
    nuevoArchivo();

    return 0;
}

void procesarArchivo()
{
    FILE *archEmpleados;
    EMPLEADOS auxEmpleados;
    float porcentaje10=5.0,porcentaje20=6.0,incremento;

    archEmpleados=abrirArchivo("sueldos.dat","r+b");
    fread(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
    while(!feof(archEmpleados))
    {
        if(auxEmpleados.antiguedad > 20)
        {
            incremento=(auxEmpleados.sueldo * porcentaje20)/100.0;
            auxEmpleados.sueldo+=incremento;
            fseek(archEmpleados,-(long)sizeof(auxEmpleados),SEEK_CUR);
            fwrite(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
            fflush(archEmpleados);
        }
        else if(auxEmpleados.antiguedad >10 && auxEmpleados.antiguedad <= 20)
        {
            incremento=(auxEmpleados.sueldo * porcentaje10)/100.0;
            auxEmpleados.sueldo += incremento;
            fseek(archEmpleados,-(long)sizeof(auxEmpleados),SEEK_CUR);
            fwrite(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
            fflush(archEmpleados);
        }
        fread(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
  
    }
    fclose(archEmpleados);
}

void nuevoArchivo()
{
    FILE *archEmpleados,*archAdmin;
    EMPLEADOS auxEmpleados;
    int cantR;
    archEmpleados=abrirArchivo("sueldos.dat","rb");
    archAdmin=abrirArchivo("administracion.dat","wb");
    fread(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
    while(!feof(archEmpleados))
    {
        if(auxEmpleados.area == 'A')
        {
            fwrite(&auxEmpleados,sizeof(auxEmpleados),1,archAdmin);
        }
        fread(&auxEmpleados,sizeof(auxEmpleados),1,archEmpleados);
    }
    cantR=contarRegistros(archAdmin,sizeof(auxEmpleados));
    printf("La cantidad de empleados en administracion son %d.\n",cantR);
   
    fclose(archAdmin);
    fclose(archEmpleados);
}

int contarRegistros(FILE *arch,int tam)
{
    int cant;
    fseek(arch,0,SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
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