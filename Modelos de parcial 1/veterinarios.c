/*Una clínica veterinaria requiere un programa en C para gestionar su inventario. 
El sistema debe reservar memoria dinámica inicialmente para 40 artículos. 
De cada producto se registra la siguiente información:
Código: Formato alfanumérico "XXX/000" (tres letras, una barra y tres números).
Nombre completo: Cadena de caracteres.
Tipo: Carácter validado ('A' Alimentos, 'V' Vacunas, 'C' Cuidados).
Inventario: Cantidad en stock (número real).
Luego de preparar el sistema, se comenzarán a registrar las compras de reposición. 
Por cada compra se ingresará el Código del artículo y la Cantidad comprada (validar que sea un real mayor a 0). 
El ingreso de compras finalizará al introducir el código "FFF/000".
Durante este proceso de compras, se debe contemplar lo siguiente:
Si el código ya existe en el arreglo, se debe actualizar su inventario sumando la cantidad comprada.
Si el código no existe, se debe dar de alta como un artículo nuevo, solicitando al usuario el nombre y el tipo, 
y redimensionando la memoria del arreglo para agregarlo.
Al finalizar el programa, se debe informar por pantalla:
La cantidad total acumulada en el inventario por cada Tipo de artículo.
La cantidad exacta de artículos nuevos que fueron añadidos al catálogo original*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct 
{
    char codigo[8];
    char NombreCompleto[21];
    char tipo;
    int stock;
} PRODUCTO;

typedef struct 
{
    char cod[8];
    int cantComprada;
} COMPRAS;

PRODUCTO ingreso(PRODUCTO *,int*);
PRODUCTO* CargarDatos(PRODUCTO *,int*,int*);
PRODUCTO* IngresoVentas(PRODUCTO *,int*,int*);
int busqueda(PRODUCTO *,char[],int*);
void informe(PRODUCTO *,int*);
int leeyValidaCod(char[],int);
void leeyValidaInt(int *,int);
void leeyValidaChar(char *);
void leerTexto(char[],int);
void leeyValidaTexto(char[],int);

int main()
{
    PRODUCTO*datos;
    COMPRAS info;
    int cantInicial=40;
    int cantProd=0;
    datos=(PRODUCTO*)malloc(cantInicial*sizeof(PRODUCTO));
    if(datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos=CargarDatos(datos,&cantInicial,&cantProd);
    datos=IngresoVentas(datos,&cantProd,&cantInicial);
    informe(datos,&cantProd);
    return 0;

} 

PRODUCTO ingreso(PRODUCTO *datos,int *ce)
{
    PRODUCTO aux;
    printf("Ingrese el codigo alfanumerico: ");
    leeryValidarTexto(aux.codigo,8);
    while(leeyValidaCod(aux.codigo,8)==0 || busqueda(datos,aux.codigo,ce)!=-1)
    {
        printf("Error. Reingrese: ");
        leeryValidarTexto(aux.codigo,8);
    }
    printf("Ingrese el nombre completo: ");
    leeryValidarTexto(aux.NombreCompleto,21);
    printf("Ingrese el tipo (A-V-C): ");
    leeyValidaChar(&aux.tipo);
    printf("Ingrese la cantidad de stock: ");
    leeyValidaInt(&aux.stock,0);
    
    return aux;

}

PRODUCTO* CargarDatos(PRODUCTO *datos,int *mem,int *cant)
{
    int i;
    printf("--Carga de productos--\n");
    for(i=0;i<*mem;i++)
    {
        *(datos+i)=ingreso(datos,&i);
    }
    *cant=i;
    return datos;
}

PRODUCTO* IngresoVentas(PRODUCTO *datos,int *ce,int *mem)
{
    COMPRAS info;
    int pos;
    printf("--Actualizacion de inventario--\n");
    printf("Ingrese el codigo de producto: ");
    leeryValidarTexto(info.cod,8);
    while(leeyValidaCod(info.cod,8)==0 && strcmpi(info.cod,"FFF/000")!=0)
    {
        pos=busqueda(datos,info.cod,ce);
        if(pos != -1)
        {
            (datos+pos)->stock+=info.cantComprada;
        }else{
            printf("Producto nuevo detectado.\n");
            if( *ce == *mem)
            {
                *mem += 10;
                datos = (PRODUCTO*)realloc(datos,*mem*sizeof(PRODUCTO));
                if(datos==NULL)
                {
                    printf("Error al resevar memoria.");
                    exit(1);
                }
            }
            strcpy((datos+*ce)->codigo,info.cod);
            printf("Ingrese el nombre del producto: ");
            leeryValidarTexto((datos+*ce)->NombreCompleto,21);
            printf("Ingrese el tipo de producto (A-V-C): ");
            leeyValidaChar(&(datos+*ce)->tipo);
            (datos+*ce)->stock = info.cantComprada;
            (*ce)++;
        }
        printf("Ingrese el codigo de producto: ");
        leeryValidarTexto(info.cod,8);
        while(leeyValidaCod(info.cod,8)==0)
        {
            printf("Error. Reingrese: ");
            leeyValidaTexto(info.cod,8);
        }
    }
    return datos;
}

void informe(PRODUCTO *datos,int *ce)
{
    int stockA=0, stockB=0, stockC=0;
    int nuevo= *ce-40;
    for(int i=0;i<*ce;i++)
    {
        if(datos[i].tipo == 'A')
        {
            stockA+=datos[i].stock;
        }
        else if (datos[i].tipo == 'B')
        {
            stockB+=datos[i].stock;
        }
        else if(datos[i].tipo == 'C')
        {
            stockC+=datos[i].stock;
        }
        
    }
    printf("La cantidad de stock del tipo A es: %d\n",stockA);
    printf("La cantidad de stocl del tipo B es: %d\n",stockB);
    printf("La cantidad de stock del tipo C es: %d\n",stockC);
    printf("La cantidad de productos nuevos son: %d",nuevo);
}


int busqueda(PRODUCTO *datos,char cod[],int *ce)
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
        } else if (i==3)
        {
            if(dato[i]!='/')
            {
                valido=0;
            }
        } else if (i>3)
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

void leeyValidaInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d",dato);
    }
}

void leeyValidaChar(char *dato)
{
    fflush(stdin);
    scanf("%c",dato);
    *dato=toupper(*dato); //
    while(*dato != 'A' && *dato != 'V' && *dato != 'C')
    {
        printf("Error. Reingrese: ");
        fflush(stdin);
        scanf("%c",dato);
        *dato=toupper(*dato);
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
    while(strlen(texto)!=largo-1)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto,largo);
    }
}




