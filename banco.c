/*Ejercicio 1. El banco “Del Plata” tiene el archivo binario cuentas.dat con los siguientes datos por cuenta:
Número de cuenta (entero)
Titular (hasta 40 caracteres)
Tipo (carácter: ‘C’ cuenta corriente, ‘A’ caja de ahorro)
Saldo (float)
Cantidad de movimientos (entero)

Se solicita:
a) Ingresar por teclado un monto fijo de cargo de mantenimiento (mayor a 0) y descontarlo del saldo de todas las cuentas corrientes (‘C’). 
La modificación debe hacerse sobre el propio archivo, mientras se lee.
b) Copiar a otro archivo, descubiertos.dat, el registro completo de las cuentas cuyo saldo haya quedado negativo después del cargo.
c) Informar, mediante una función, la cantidad de registros de descubiertos.dat.
d) Explicar con sus palabras cómo se hace la eliminación lógica de un registro y en qué se diferencia de la física.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 41

typedef struct 
{
    int cuenta;
    char titular[TXT];
    char tipo;
    float saldo;
    int cantMov;

} CUENTAS;

FILE *abrirArchivo(char[],char[]);
void procesarArchivo();
void nuevoArchivo();
void leeyValidaFloat(float *,int);
int contarRegistros(FILE *,int);

int main()
{
    procesarArchivo();
    nuevoArchivo();

    return 0;
}

void procesarArchivo()
{
    FILE *archCuentas;
    CUENTAS auxCuentas;
    float montoAux;
    
    archCuentas=abrirArchivo("cuentas.dat","r+b");
    printf("Ingrese un monto fijo de cargo: ");
    leeyValidaFloat(&montoAux,0);
    fread(&auxCuentas,sizeof(auxCuentas),1,archCuentas);
    while(!feof(archCuentas))
    {
        if(auxCuentas.tipo == 'C')
        {
            auxCuentas.saldo-=montoAux;
            fseek(archCuentas,-(long)sizeof(auxCuentas),SEEK_CUR);
            fwrite(&auxCuentas,sizeof(auxCuentas),1,archCuentas);
            fflush(archCuentas);
        }
        fread(&auxCuentas,sizeof(auxCuentas),1,archCuentas);
    }
    fclose(archCuentas);
}

void nuevoArchivo()
{
    FILE *archCuentas,*archDesc;
    CUENTAS auxCuentas;
    int cantR;
    
    archCuentas=abrirArchivo("cuentas.dat","rb");
    archDesc=abrirArchivo("descubiertos.dat","wb");
    fread(&auxCuentas,sizeof(auxCuentas),1,archCuentas);
    while(!feof(archCuentas))
    {
        if(auxCuentas.saldo<0)
        {
            fwrite(&auxCuentas,sizeof(auxCuentas),1,archDesc);
        }
        fread(&auxCuentas,sizeof(auxCuentas),1,archCuentas);
    }
    cantR=contarRegistros(archDesc,sizeof(auxCuentas));
    printf("La cantidad de cuentas al descubiertos es: %d",cantR);
    
    fclose(archCuentas);
    fclose(archDesc);
}

int contarRegistros(FILE *arch,int tam)
{
    int cant;
    fseek(arch,0,SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
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