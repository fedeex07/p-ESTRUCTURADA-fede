/*Un palíndromo es una palabra o frase cuyas letras se leen de la misma manera de izquierda a derecha que de derecha a izquierda (por ejemplo: ANA, NEUQUEN, RECONOCER, OSO

Se solicita realizar un programa en C que permita el ingreso continuo de palabras por teclado. El ingreso finaliza cuando el usuario escribe la palabra "FIN" (en mayúsculas).

Desarrollar una función esPalindromo que retorne 1 si la palabra es palíndromo o 0 si no lo es.
La función debe ser independiente de mayúsculas y minúsculas (tratar 'A' y 'a' como iguales)
Para cada ingreso (excepto "FIN"), mostrar si la palabra es o no un palíndromo*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int esPalindromo(char[]);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    char palabra[51];
    printf("Ingrese la palabra: ");
    leeryValidarTexto(palabra,51);
    while(strcmpi(palabra,"FIN")!=0)
    {
        if(esPalindromo(palabra)==1)
        {
            printf("La palabra %s es balindromo.\n",palabra);
        }
        else
        {
            printf("La palabra %s no es balindromo.\n",palabra);
        }
        printf("Ingrese la palabra: ");
        leeryValidarTexto(palabra,51);
    }
    return 0;
}

int esPalindromo(char palabra[])
{
    int valido=1;
    int prin=0;
    int final = strlen(palabra)-1;
    while(prin<final)
    {
        if(toupper(palabra[prin]) != toupper(palabra[final]))
        {
            valido=0;
        }
        prin++;
        final--;
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
    while(strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto,largo);
    }
}
