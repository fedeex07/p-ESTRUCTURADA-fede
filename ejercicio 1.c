/*1. De una persona se conoce los siguientes datos:
• Número de Legajo (int, entre 1 y 10.000)
• Apellido (string, 15 caracteres)
• Nombre (string, 15 caracteres)
• Altura (float, mayor de 0)
• Sexo (char, F o M)
• Día de Nacimiento (int, entre 1 y 31
• Mes de Nacimiento (int, ente 1 y 12)
• Año de Nacimiento (int, ente 1950 y 2019)

Se solicita realizar los siguientes procesos:
a. Con datos ingresados por teclado: Crear una Estructura de Datos con los datos enunciados
anteriormente y llamarla PERSONA.
b. Mostrar los datos de la Estructura de Datos del punto a.
c. Con datos ingresados por teclado: Modificar la Estructura de Datos del punto a., crear una Estructura
de Datos que contenga Nombre y Apellido y otra Estructura de Datos que contenga Día/Mes/Año
utilizarla en una nueva Estructurad de Datos llamada PERSONA2.
d. Mostrar los datos de la Estructura de Datos del punto c.
e. Crear una FUNCION que cargue los datos de la Estructurad de Datos del punto c y que retorne los datos
al programa principal (main).
f. Con datos ingresados por teclado: Modificar la Estructurad de Datos llamada PERSONA2 del punto c.
y agregarle un campo/miembro que contenga los códigos de las Materias Aprobadas (pueden llegar a
ser hasta 36 materias) y llamarla PERSONA3.
g. Crear una FUNCION que realice el punto f.
h. Mostrar los datos de la Lista creada en el punto f.
i. Crear una FUNCION que realice el punto h.*/


#include <stdio.h>
#include <string.h>
#define TAM 16

typedef struct
{
    int legajo;
    char Apellido[TAM];
    char Nombre[TAM];
    float Altura;
    char Sexo;
    int DiaNacimiento;
    int MesNacimiento;
    int AnioNacimiento;
} Persona;

Persona CargarDatos();
leerTexto(char[],int);
leeryValidarTexto(char[],int);
leeryValidarInt(int *,int);
leeryValidarFloat(float *,int);
leeryValidarSexo(char *sexo);

int main()
{

}

Persona Cargardatos()
{
    Persona pers;

    printf("Ingrese el numero de legajo (1-10000): ");
    leeryValidarInt(&pers.legajo,1,10000);
    printf("Ingrese el apellido: ");
    leeryValidarTexto(pers.Apellido,TAM);
    printf("Ingrese el nombre: ");
    leeryValidarTexto(pers.Nombre,TAM);
    printf("Ingrese la altura: ");
    leeryValidarFloat(&pers.Altura,0);
    printf("Ingrese su sexo (F/M): ");
    leeryValidarSexo(&pers.Sexo);
    printf("Ingrese su dia de nacimiento (1-31): ");
    leeryValidarInt(&pers.DiaNacimiento,1,31);
    printf("Ingrese su mes de nacimiento (1-12): ");
    leeryValidarInt(&pers.MesNacimiento,1,12);
    printf("Ingrese su anio de nacimiento (1950-2019): ");
    leeryValidarInt(&pers.AnioNacimiento,1950,2019);

    return pers;

}

leerTexto(char texto[],int largo)
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

leeryValidarTexto(char texto[],int largo)
{
    leerTexto(texto,largo);
    while(strlen(texto) != 16)
    {
        printf("El texto ingresado es incorrecto. Reingrese: ");
        leerTexto(texto,largo);
    }
}

leeryValidarInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato < lim)
    {
        printf("Cantidad incorrecta. Reingrese: ");
        scanf("%d",dato);
    }
}

leeryValidarFloat(float *dato,int lim)
{
    scanf("%f",dato);
    while(*dato < lim)
    {
        printf("Cantidad Incorrecta. Reingrese: ");
        scanf("%f",dato);
    }
}

leeryValidarSexo(char *sexo)
{
    fflush(stdin);
    scanf(" %c",sexo);
    while(*sexo != 'F' && *sexo != 'M' && *sexo != 'f' && *sexo != 'm')
    {
        printf("Sexo invalido. Reingrese (F/M): ");
        scanf(" %c",sexo);
    }
}