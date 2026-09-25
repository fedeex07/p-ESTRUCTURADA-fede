/*Una inmobiliaria gestiona las visitas agendadas a propiedades en alquiler. 
Por cada visita se carga: 
Código de propiedad (formato alfanumérico "AAA-000", tres letras, un guion, tres números), 
Nombre del interesado (cadena) y 
Estado de la visita (carácter: 'P' Pendiente, 'C' Concretada, 'A' Anulada).
Los datos se cargan en un vector de estructuras hasta que se ingresa como código de propiedad "FIN".
Al ingresar un código, se debe validar el formato (las tres letras y el guion en la posición correcta, los tres dígitos finales).
Finalizada la carga, se solicita:
a) Informar la cantidad de visitas en cada estado ('P', 'C', 'A').
b) Listar únicamente las visitas Pendientes, ordenadas alfabéticamente por nombre del interesado (con burbujeo).
c) Implementar una función de búsqueda que, dado un código de propiedad ingresado por teclado, informe el nombre del interesado 
y el estado de esa visita (o un mensaje si no existe)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct 
{
    char codigo[8];
    char nombre[21];
    char Estado;
} VISITAS;

VISITAS ingreso(VISITAS *,int*);
VISITAS *CargarDatos(VISITAS *,int *,int *);
void burbujeo(VISITAS *,int *);
void intercambio(VISITAS *,VISITAS *);
void mensajeVisita(VISITAS *,int *);
void listadoPendiente(VISITAS *,int*);
void informarEstado(VISITAS *,int*);
int busqueda(VISITAS *,char[],int *);
int leeyValidaCod(char[],int);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);
void leeyValidaChar(char *);
void leeyValidaNombre(char[],int);

int main()
{
    VISITAS *datos;
    int capInicial=0;
    int cantVisitas=0;
    datos=(VISITAS*)malloc(capInicial*sizeof(VISITAS));
    if(datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos=CargarDatos(datos,&cantVisitas,&capInicial);
    informarEstado(datos,&cantVisitas);
    listadoPendiente(datos,&cantVisitas);
    mensajeVisita(datos,&cantVisitas);

    free(datos);

    return 0;

}

VISITAS ingreso(VISITAS *datos,int *ce)
{
    VISITAS aux;
    printf("Ingrese el codigo (XXX-000): ");
    leeryValidarTexto(aux.codigo,8);
    while(strcmpi(aux.codigo,"FIN")!=0 && (leeyValidaCod(aux.codigo,8)==0 || busqueda(datos,aux.codigo,ce)!=-1))
    {
        if(leeyValidaCod(aux.codigo,8)==0)
        {
            printf("Error de formato. Reingrese: ");
        }
        else
        {
            printf("El codigo ya fue ingresado. Reingrese: ");
        }
        leeryValidarTexto(aux.codigo,8);
    }
    if(strcmpi(aux.codigo,"FIN")!=0)
    {
        printf("Ingrese el nombre del interesado: ");
        leeyValidaNombre(aux.nombre,21);
        printf("Ingrese el estado de la visita: ");
        leeyValidaChar(&aux.Estado);
    }    

    return aux;
}

VISITAS *CargarDatos(VISITAS *datos,int *ce,int *mem)
{
    VISITAS aux;
    int i=0;
    aux=ingreso(datos,&i);
    while(strcmpi(aux.codigo,"FIN")!=0)
    {
        if(i==*mem)
        {
            *mem+=10;
            datos=(VISITAS*)realloc(datos,*mem*sizeof(VISITAS));
            if(datos==NULL)
            {
                printf("Error al reservar memoria.");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos,&i);
    }
    *ce=i;
    return datos;
}

void mensajeVisita(VISITAS *datos,int *ce)
{
    char cod[8];
    int pos;
    printf("--BUSQUEDA INTERESADO--\n");
    printf("Ingrese el codigo: ");
    leeryValidarTexto(cod,8);
    while(leeyValidaCod(cod,8)==0)
    {
        printf("Error.Reingrese: ");
        leeryValidarTexto(cod,8);
    }
    while(strcmpi(cod,"FIN")!=0)
    {
        pos=busqueda(datos,cod,ce);
        if(pos != -1)
        {
            printf("El nombre del interesado es %s y su visita se encuentra en estado %c\n",(datos+pos)->nombre,(datos+pos)->Estado);
        }
        else
        {
            printf("El codigo no existe: ");
        }

    }
    

}

void informarEstado(VISITAS *datos,int *ce)
{
    int visitasP=0, visitasC=0, visitasA=0;
    for(int i=0;i<*ce;i++)
    {
        if(datos[i].Estado == 'P')
        {
            visitasP++;
        }
        else if(datos[i].Estado == 'C')
        {
            visitasC++;
        }
        else if(datos[i].Estado == 'A')
        {
            visitasA++;
        }

    }
    printf("Las visitas del estado P son: %d\n",visitasP);
    printf("Las visitas del estado C son: %d\n",visitasC);
    printf("Las visitas del estado A son: %d\n",visitasA);
}

void listadoPendiente(VISITAS *datos,int *ce)
{
    burbujeo(datos,ce);
    int acum=0;
    for(int i=0;i<*ce;i++)
    {
        if((datos+i)->Estado=='P')
        {
            printf("Visita pendiente del interesado %s\n",(datos+i)->nombre);
            acum++;
        }
        
    }
    if(acum==0)
    {
        printf("No hay visitas pendientes.");
    }
}

void burbujeo(VISITAS *datos,int *ce)
{
    int j,cota=*ce-1;
    int desordenado=1;
    while(desordenado)
    {
        desordenado=0;
        for(j=0;j<cota;j++)
        {
            if(strcmpi((datos+j)->nombre,(datos+j+1)->nombre)>0)
            {
                intercambio(&datos[j],&datos[j+1]);
                desordenado=j;
            }
        }
        cota=desordenado;
    }
}

void intercambio(VISITAS *a,VISITAS *b)
{
    VISITAS aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

int busqueda(VISITAS *datos,char cod[],int *ce)
{

    int pos=-1,i=0;
    while(pos==-1 && i<*ce)
    {
        if(strcmpi((datos+i)->codigo,cod)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeyValidaChar(char *dato)
{
    fflush(stdin);
    scanf(" %c",dato);
    *dato=toupper(*dato);
    while(*dato != 'P' && *dato != 'C' && *dato != 'A')
    {
        printf("Error. Reingrese: ");
        fflush(stdin);
        scanf(" %c",dato);
        *dato=toupper(*dato);
    }
}

int leeyValidaCod(char dato[],int ce)
{
    int valido=1,i=0;
    while(valido==1 && i<ce-1)
    {
        if(i<=2)
        {
            if(isalpha(dato[i])==0)
            {
                valido=0;
            }
        }
        else if(i==3)
        {
            if(dato[i]!='-')
            {
                valido=0;
            }
        }
        else if(i>3)
        {
            if(isdigit(dato[i])==0)
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
    while(strlen(texto)!=7 && strlen(texto)!=3)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto,largo);
    }
}

void leeyValidaNombre(char texto[],int largo)
{
    leerTexto(texto,largo);
    while(strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto,largo);
    }
}

