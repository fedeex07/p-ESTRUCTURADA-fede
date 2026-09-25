/*Un centro odontológico administra la agenda de turnos para un día determinado. 
Cada turno se representa mediante una estructura con los siguientes datos:

DNI del Paciente (entero).
Nombre del Paciente (cadena de hasta 50 caracteres).
Estado del Turno (entero: 1 para "Pendiente", 2 para "Atendido", 3 para "Cancelado").

Se deben ingresar los datos de los turnos en un vector de estructuras asignado dinámicamente en memoria.
El arreglo debe comenzar con una capacidad inicial de 10 turnos.
Cada vez que el arreglo se llene, su capacidad debe aumentarse dinámicamente de 10 en 10.
Al ingresar el DNI se debe validar que el paciente no tenga ya un turno asignado en el vector. La carga finaliza con DNI = 0.

Finalizada la carga, se ingresará una secuencia de DNI de pacientes que van llegando a la recepción, terminando con DNI = 0.
Si el DNI existe, se debe cambiar el estado del turno a 2: "Atendido".
Si el DNI no existe, se lo contabilizará como "Paciente No Registrado".
Informar:
a) La cantidad total de pacientes que asistieron, pero no tenían turno.
b) El listado completo de la agenda ordenado de forma ascendente por DNI, mostrando DNI, Nombre y estado.
Implementar al menos dos funciones: Una para la búsqueda del DNI en el vector de estructuras, y otra para el ordenamiento.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int dni;
    char nombreP[51];
    int Turno;
} TURNOS;

TURNOS* CargarDatos(TURNOS *,int *,int *);
TURNOS ingreso(TURNOS *,int *);
int busqueda(TURNOS *,int,int *);
void recepcion(TURNOS *,int *);
void listado(TURNOS *,int *);
void burbujeo(TURNOS *,int *);
void leeyValidaInt(int *,int,int,int);
void leeyValidaEstado(int *);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    TURNOS *datos;
    int cantIncial=0;
    int cantVec=0;
    datos=(TURNOS*)malloc(cantIncial*sizeof(TURNOS));
    if(datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos = CargarDatos(datos,&cantIncial,&cantVec);
    recepcion(datos,&cantVec);
    listado(datos,&cantVec);

    return 0;
}

TURNOS ingreso(TURNOS *datos,int *ce)
{
    TURNOS aux;
    printf("Ingrese el dni del paciente: ");
    leeyValidaInt(&aux.dni,10000000,99999999,0);
    if(aux.dni != 0)
    {
        while(busqueda(datos,aux.dni,ce) != -1)
        {
            printf("El dni ya fue ingresado. Reingrese: ");
            leeyValidaInt(&aux.dni,10000000,99999999,0);
        }
        if(aux.dni != 0)
        {
            printf("Ingrese el nombre del paciente: ");
            leeryValidarTexto(aux.nombreP,51);
            printf("Ingrese el estado del turno: ");
            leeyValidaEstado(&aux.Turno);

        }
    }
    return aux;
}

TURNOS* CargarDatos(TURNOS *datos,int *mem,int *ce)
{
    TURNOS aux;
    int i=0;
    aux=ingreso(datos,ce);
    while(aux.dni !=0)
    {
        if(i==*mem)
        {
            *mem+=10;
            datos=(TURNOS*)realloc(datos, *mem*sizeof(TURNOS));
            if(datos==NULL)
            {
                printf("Error al reservar memoria");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos,ce);
    }
    *ce=i;
    return datos;

}

void recepcion(TURNOS *datos,int *ce)
{
    TURNOS aux;
    int pos, noRegistrado=0;
    printf("--Ingreso a recepcion--\n");
    printf("Ingrese el dni del paciente: ");
    leeyValidaInt(&aux.dni,10000000,99999999,0);
    while(aux.dni !=0)
    {
        pos=busqueda(datos,aux.dni,ce);
        if(pos != -1)
        {
            (datos+pos)->Turno=2;
        }else
        {
            noRegistrado++;
        }
        printf("Ingrese el dni del paciente: ");
        leeyValidaInt(&aux.dni,10000000,99999999,0);
    }
    printf("Los pacientes que asistieron sin turno son: %d\n",noRegistrado);
}

void listado(TURNOS *datos,int *ce)
{
    burbujeo(datos,ce);
    printf("--Listado de turnos--\n");
    printf("%8s %-30s %-6s\n", "DNI", "NOMBRE", "ESTADO");
    for(int i=0;i<*ce;i++)
    {
        printf("%8d %-30s %-6d\n",(datos+i)->dni,(datos+i)->nombreP,(datos+i)->Turno);
    }
}

int busqueda(TURNOS *datos,int cod,int *ce)
{
    int pos=-1,i=0;
    while(pos==-1 && i<*ce)
    {
        if((datos+i)->dni == cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void burbujeo(TURNOS *datos,int *ce)
{
    TURNOS aux;
    int j,cota=*ce-1;
    int desordenado=1;
    while(desordenado)
    {
        desordenado=0;
        for(j=0;j<cota;j++)
        {
            if((datos+j)->dni > (datos+j+1)->dni)
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
    while(*dato != 1 && *dato != 2 && *dato != 3)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
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
        printf("El texto ingresado es incorrecta. Reingrese: ");
        leerTexto(texto,largo);
    }
}