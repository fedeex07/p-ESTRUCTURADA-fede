/*Un centro odontológico administra una agenda de 40 turnos para un día determinado. Cada turno se representa mediante una estructura con los siguientes datos:

 DNI del Paciente (entero).

Nombre del Paciente (cadena de hasta 50 caracteres).

Estado del Turno (entero: 1 “Pendiente", 2  "Atendido", 3  "Cancelado").

Se deben ingresar los datos de los 40 turnos , Al ingresar el DNI, se debe validar que el paciente no tenga ya un turno asignado en el vector.

Finalizada la carga, se ingresará una secuencia de DNI de pacientes que van llegando a la recepción, terminando con DNI = 0.

Si el DNI existe, se debe cambiar el estado del turno a 2: "Atendido”.

Si el DNI no existe, se lo contabilizara como “Paciente No Registrados".

Informar:

a) La cantidad total de pacientes que asistieron, pero no tenían turno.
b) El listado completo de la agenda ordenado de forma ascendente por DNI, mostrando DNI, Nombre y el estado.
Implementar al menos tres funciones: Una para la carga, otra para el ordenamiento y otra para la  búsqueda del código en el vector de estructuras,*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 40

typedef struct 
{
    int DNI;
    char NombreCompleto[51];
    int EstadoTurno;
} TURNOS;

TURNOS CargaDatos(TURNOS[],int);
int ingreso(TURNOS[],int);
int busqueda(TURNOS[],int,int);
void recepcion(TURNOS[],int);
void listado(TURNOS[],int);
void burbujeo(TURNOS[],int);
void leeyValidaInt(int *,int,int,int);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);
void leeyValidaEstado(int *);

int main()
{
    TURNOS datos[TAM];
    int cargados;
    cargados=ingreso(datos,TAM);
    recepcion(datos,cargados);
    listado(datos,cargados);

    return 0;
}

TURNOS CargaDatos(TURNOS datos[],int ce)
{
    TURNOS aux;
    printf("Ingrese el dni del paciente: ");
    leeyValidaInt(&aux.DNI,10000000,99999999,0);
    if(aux.DNI != 0)
    {
        while(busqueda(datos,aux.DNI,ce) != -1)
        {
            printf("El DNI ya fue ingresado. Reintente: ");
            leeyValidaInt(&aux.DNI,10000000,99999999,0);
        }
        if(aux.DNI != 0)
        {
            printf("Ingrese el nombre completo del paciente: ");
            leeryValidarTexto(aux.NombreCompleto,51);
            printf("Ingrese el estado del turno: ");
            leeyValidaEstado(&aux.EstadoTurno);
        }
    }
    return aux;
}

int ingreso(TURNOS datos[],int ce)
{
    TURNOS aux;
    int i;
    printf("--Ingreso de turnos--\n");
    aux=CargaDatos(datos,ce);
    while(aux.DNI !=0 && i<ce)
    {
        datos[i]=aux;
        i++;
        aux=CargaDatos(datos,ce);
    }
    return i;
}

void recepcion(TURNOS datos[],int ce)
{
    TURNOS aux;
    int pos, noRegistrado=0;
    printf("--Ingreso a recepcion--\n");
    printf("Ingrese el dni del paciente: ");
    leeyValidaInt(&aux.DNI,10000000,99999999,0);
    while(aux.DNI != 0)
    {
        pos=busqueda(datos,aux.DNI,ce);
        if(pos != -1)
        {
            (datos+pos)->EstadoTurno=2;
        }else{
            noRegistrado++;
        }
        printf("Ingrese el dni del paciente: ");
        leeyValidaInt(&aux.DNI,10000000,99999999,0);
    }
    printf("La cantida de paciente que asistieron sin turno es %d\n",noRegistrado);
}

void listado(TURNOS datos[],int ce)
{
    burbujeo(datos,ce);
    printf("--Listado de turnos==\n");
    printf("%8s %-30s %-6s\n", "DNI", "NOMBRE", "ESTADO");
    for(int i=0;i<ce;i++)
    {
        printf("%8d %-30s %-6d\n",(datos+i)->DNI,(datos+i)->NombreCompleto,(datos+i)->EstadoTurno);
    }
}

void burbujeo(TURNOS datos[],int ce)
{
    TURNOS aux;
    int j,cota=ce-1;
    int desordenado=1;
    while(desordenado)
    {
        desordenado=0;
        for(j=0;j<cota;j++)
        {
            if((datos+j)->DNI > (datos+j+1)->DNI)
            {
                aux=*(datos+j);
                *(datos+j)=*(datos+j+1);
                *(datos+j+1)=aux;
                desordenado=j;
            }
        }
        cota=desordenado;
    }
}


int busqueda(TURNOS datos[],int cod, int ce)
{
    int pos=-1,i=0;
    while(pos==-1 && i<ce)
    {
        if((datos+i)->DNI==cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
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
    while(strlen(texto) == 0)
    {
        printf("El texto ingresado es incorrecta. Reingrese: ");
        leerTexto(texto,largo);
    }
}

void leeyValidaInt(int *dato,int min,int max,int cf)
{
    scanf("%d",dato);
    while((*dato<min || *dato>max) && *dato != cf)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
}

void leeyValidaEstado(int *dato)
{
    scanf("%d",dato);
    while(*dato != 1 && *dato != 2 && *dato !=3)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
}