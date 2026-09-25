/*Una editorial desea gestionar su sistema de stock de libros. Para ello necesita manejar la siguiente información:
Por cada libro:
Código ISBN (entero de 8 dígitos)
Título (50 caracteres máximo)
Autor (40 caracteres máximo)
Cantidad de unidades en stock (entero)
La carga inicial de productos finaliza cuando se ingresa ISBN = 0.

Gestión de memoria:
a) Debido a que no se conoce la cantidad total de libros, se debe asignar un arreglo dinámico en memoria.
b) El arreglo debe comenzar con una capacidad inicial de 10 elementos.
c) Cada vez que el arreglo se llene, su capacidad debe aumentarse dinámicamente de 10 en 10.

Al finalizar el mes, se ingresan las ventas con los siguientes datos:
Código ISBN del libro
Cantidad vendida
Se pide hacer un programa que permita ingresar los datos de los libros considerando que se finaliza la carga cuando se ingresa el ISBN 0.
Luego, permitir ingresar las ventas considerando que no se van a ingresar más ventas cuando se ingrese el ISBN 0.
Se debe:
a. Actualizar el stock de cada libro con las ventas realizadas en el mes.
b. Al finalizar, mostrar el listado actualizado, informando:
ISBN              TITULO               AUTOR                STOCK ACTUALIZADO
99999999 XXXXXXXXXXXXXXXXXXXX XXXXXXXXXXXXXXXXXXXX        9999*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    int CodISBN;
    char titulo[51];
    char autor[41];
    int stock;
} LIBROS;

typedef struct 
{
    int cod;
    int cantV;
} VENTAS;


LIBROS* CargarDatos(LIBROS *,int *,int *);
LIBROS ingreso(LIBROS *,int *);
void ventas(LIBROS *,int *);
int busqueda(LIBROS *,int,int *);
void listado(LIBROS *,int *);
void leeyValidaInt(int *,int);
void leeyValidaInt2(int *,int,int,int);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    LIBROS *datos;
    int capInicial = 0;
    int cantLibros = 0;
    datos=(LIBROS*)malloc(capInicial*sizeof(LIBROS));
    if(datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos = CargarDatos(datos,&capInicial,&cantLibros);
    ventas(datos,&cantLibros);
    listado(datos,&cantLibros);

    free(datos);
    return 0;
}

LIBROS ingreso(LIBROS *datos,int *ce)
{
    LIBROS aux;
    printf("Ingrese el codigo ISBN: ");
    leeyValidaInt2(&aux.CodISBN,10000000,99999999,0);
    if(aux.CodISBN != 0)
    {
        while(busqueda(datos,aux.CodISBN,ce) != -1)
        {
            printf("El codigo ya fue ingresado. Reintente: ");
            leeyValidaInt2(&aux.CodISBN,10000000,99999999,0);
        }
        printf("Ingrese el titulo del libro: ");
        leeryValidarTexto(aux.titulo,51);
        printf("Ingrese el autor del libro: ");
        leeryValidarTexto(aux.autor,41);
        printf("Ingrese el stock disponible del libro: ");
        leeyValidaInt(&aux.stock,0);
    }
    return aux;
}

LIBROS* CargarDatos(LIBROS *datos,int *mem, int *cantL)
{
    LIBROS aux;
    int i=0;
    printf("--Ingreso Libros--\n");
    aux=ingreso(datos,&i);
    while(aux.CodISBN != 0)
    {
        if(i==*mem)
        {
            *mem+=10;
            datos=(LIBROS*)realloc(datos, *mem*sizeof(LIBROS));
            if(datos==NULL)
            {
                printf("Error al reservar memoria.\n");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos,&i);
    }
    *cantL=i;
    return datos;
}

void ventas(LIBROS *datos,int *ce)
{
    VENTAS info;
    int pos;
    printf("--Actualizacion de stock--\n");
    printf("Ingrese el codigo ISBN: ");
    leeyValidaInt2(&info.cod,10000000,99999999,0);
    while(info.cod != 0)
    {
        pos=busqueda(datos,info.cod,ce);
        if(pos != -1)
        {
            printf("Ingrese la cantidad vendida: ");
            leeyValidaInt(&info.cantV,1);
            if((datos+pos)->stock>=info.cantV)
            {
                (datos+pos)->stock-=info.cantV;
            }else
            {
                printf("La cantidad vendida supera al stock.");
            }
        } else 
        {
            printf("El codigo no existe. ");
        }
        printf("Ingrese el codigo ISBN: ");
        leeyValidaInt2(&info.cod,10000000,99999999,0);
    }
    printf("--Stock actualizado--\n");
}

void listado(LIBROS *datos,int *ce)
{
    printf("%8s %-20s %-20s %17s\n", "ISBN", "TITULO", "AUTOR", "STOCK ACTUALIZADO");
    for(int i=0;i<*ce;i++)
    {
        printf("%8d %-20s %-20s %17d\n",(datos+i)->CodISBN,(datos+i)->titulo,(datos+i)->autor,(datos+i)->stock);
    }
}

int busqueda(LIBROS *datos,int cod,int *ce)
{
    int pos=-1,i=0;
    while(pos==-1 && i<*ce)
    {
        if((datos+i)->CodISBN==cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeyValidaInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato < lim)
    {
        printf("Cantidad incorrecta. Reingrese: ");
        scanf("%d",dato);
    }
}

void leeyValidaInt2(int *dato,int min,int max,int cf)
{
    scanf("%d",dato);
    while((*dato < min || *dato > max) && *dato != cf)
    {
        printf("Cantidad incorrecta. Reingrese: ");
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
    while(strlen(texto) == 0)
    {
        printf("El texto ingresado es incorrecto. Reingrese: ");
        leerTexto(texto,largo);
    }
}
