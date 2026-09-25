/*El ministerio de transporte requiere un programa que permita validar si una patente es válida. 
Realizar un programa en C que permita verificar si la patente es válida o no hasta que se ingrese la patente "FIN". 
Formatos posibles: AAA999 ó AA999AA*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 8

int validaP7(char[],int);
int validaP6(char[],int);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    int valido=0;
    char patente[TAM];
    printf("Ingrese la patente: ");
    leeryValidarTexto(patente,TAM);
    while(strcmpi(patente,"FIN")!=0)
    {
        if(strlen(patente)==6)
        {
            valido = validaP6(patente,6);
        }
        else if(strlen(patente)==7)
        {
            valido = validaP7(patente,7);
        }
        if(valido == 1)
        {
            printf("Patente valida.\n");
        }
        else
        {
            printf("Patente invalida.\n");
        }
        printf("Ingrese la patente: ");
        leeryValidarTexto(patente,TAM);
    }
}

int validaP7(char patente[],int ce)
{
    int valido=1,i=0;
    while(valido==1 && i<ce)
    {
        if(i<=1)
        {
            if(isalpha(patente[i])==0)
            {
                valido=0;
            }
        }
        else if(i>=2 && i<=4)
        {
            if(isdigit(patente[i])==0)
            {
                valido=0;
            }
        }
        else if(i>4)
        {
            if(isalpha(patente[i])==0)
            {
                valido=0;
            }
        }
        i++;
    }
    return valido;
}

int validaP6(char patente[],int ce)
{
    int valido=1,i=0;
    while(valido==0 && i<ce)
    {
        if(i<=2)
        {
            if(isalpha(patente[i])==0)
            {
                valido=0;
            }
        }
        else if(i>2)
        {
            if(isdigit(patente[i])==0)
            {
                valido=0;
            }
        }
        i++;
    }
    return valido;
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
    while((strlen(texto) !=6 && strlen(texto) != 7) && strlen(texto) !=3)
    {
        printf("Error.Reingrese: ");
        leerTexto(texto,largo);
    }
}