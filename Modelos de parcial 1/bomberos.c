/*Una estación de bomberos está a cargo de apagar los fuegos en la ciudad de Morón. Se tiene la estructura CasasPrendidasFuego, 
donde se carga la localidad (una cadena de 50 caracteres como maximo), 
la dirección (una cadena de 50 caracteres como maximo y debe incluir 4 digitos al final de la cadena) y la prioridad (un entero de 1 a 10). 

Los llamados de urgencia van llegando por numero de llamado y se desconoce cuantos llamados pueden ser. 

Dado a que los llamados llegan todos uno tras otro, es imposible preparar una misión organizada llamado tras llamado

El equipo de bomberos te solicita que, tras terminar la carga de casas prendidas fuego (terminando con la dirección MORON) 

1.- Muestres las casas prendidas fuego más importantes según su orden de prioridad, así el equipo de bomberos puede dirigirse lo antes posible

2.- Si existen casas repetidas en una misma localidad, entonces realizar un ordenamiento por la cantidad de casas que existan por cada municipio y mostrar el listado*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TXT 51

typedef struct 
{
    char localidad[TXT];
    char direccion[TXT];
    int prioridad;

} CasasPrendidaFuego;

CasasPrendidaFuego ingreso(CasasPrendidaFuego*);
CasasPrendidaFuego *CargarDatos(CasasPrendidaFuego*,int*,int*);
void repetidas(CasasPrendidaFuego*,int*);
int casasPrioridad(CasasPrendidaFuego*,int*);
void burbujeo(CasasPrendidaFuego*,int*);
void intercambio(CasasPrendidaFuego*,CasasPrendidaFuego*);
void leeyValidaInt(int *,int,int);
int leeyValidaDire(char[]);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    CasasPrendidaFuego *datos;
    int capInicial=1,cantCasas=0;
    datos=(CasasPrendidaFuego*)malloc(capInicial*sizeof(CasasPrendidaFuego));
    if(datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos=CargarDatos(datos,&capInicial,&cantCasas);

    return 0;
}

CasasPrendidaFuego ingreso(CasasPrendidaFuego *datos)
{
    CasasPrendidaFuego aux;
    printf("Ingrese la direccion: ");
    leeryValidarTexto(aux.direccion,TXT);
    while(strcmpi(aux.direccion,"MORON")!= 0 && leeyValidaDire(aux.direccion)==0)
    {
        printf("Direccion incorrecta. Reingrese: ");
        leeryValidarTexto(aux.direccion,TXT);
    }
    if(strcmpi(aux.direccion,"MORON") != 0)
    {
        printf("Ingrese la localidad: ");
        leeryValidarTexto(aux.localidad,TXT);
        printf("Ingrese la prioridad (1-10): ");
        leeyValidaInt(&aux.prioridad,1,10);
    }

    return aux;
}

CasasPrendidaFuego *CargarDatos(CasasPrendidaFuego *datos,int *mem,int *ce)
{
    CasasPrendidaFuego aux;
    int i=0;
    aux=ingreso(datos);
    while(strcmpi(aux.direccion,"MORON")!=0)
    {
        if(i==*mem)
        {
            *mem+=1;
            datos=(CasasPrendidaFuego*)realloc(datos, *mem*sizeof(CasasPrendidaFuego));
            if(datos==NULL)
            {
                printf("Error al reservar memoria.");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos);
    }
    *ce=i;
    return datos;
}

void burbujeo(CasasPrendidaFuego *datos,int *ce)
{
    int j,cota=*ce-1;
    int desordenado=1;
    while(desordenado)
    {
        desordenado=0;
        for(j=0;j<cota;j++)
        {
            if((datos+j)->prioridad > (datos+j+1)->prioridad)
            {
                intercambio(&datos[j],&datos[j+1]);
                desordenado=j;
            }
        }
        cota=desordenado;
    }
}

void intercambio(CasasPrendidaFuego *a, CasasPrendidaFuego *b)
{
    CasasPrendidaFuego aux;
    aux=*a;
    *a=*b;
    *b=aux;

}




void leeyValidaInt(int *dato,int min,int max)
{
    scanf("%d",dato);
    while(*dato<min || *dato>max)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
}

int leeyValidaDire(char texto[])
{
    int valido=1;
    int largo=strlen(texto);
    int i=largo-4;
    if(largo<4)
    {
        valido=0;
    }
    while(valido==1 && i<largo)
    {
        if(isdigit(texto[i])==0)
        {
            valido=0;
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
    while(strlen(texto)==0)
    {
        printf("El texto ingresado es incorrecto. Reingrese: ");
        leerTexto(texto,largo);
    }
}