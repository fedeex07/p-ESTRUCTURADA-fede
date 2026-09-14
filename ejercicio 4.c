/*Se ingresan código y precio unitario de los productos que vende un negocio. No se sabe la cantidad exacta de
productos, pero sí se sabe que son menos de 50. El código es alfanumérico de 3 caracteres y la carga de los
datos de productos termina con un código igual al “FIN”. Luego se registran las ventas del día y por cada venta
se ingresa el código de producto y cantidad de unidades vendidas terminando con una cantidad igual a 0. Se
solicita:
a. Calcular la recaudación total del día y el producto del cual se vendió menor cantidad de unidades.
b. Mostrar el listado de productos con su precio ordenado en forma alfabética por código de producto. */

#include <stdio.h>
#include <string.h>
#define TAM 50
#define TXT 4

int CargaProductos(float[], char[][TXT], int);
void ventas(char[][TXT], float[], int[], float *, int);
void minimo(char[][TXT],int[], int);
int buscarMinimo(int [], int);
void listado(char[][TXT], float[], int);
void burbujeo(char[][TXT],float[],int);
void leeyValidaInt(int *, int);
int busqueda(char[][TXT],char[],int);
void leerTexto(char[],int);
void leeryValidarTexto(char[],int);

int main()
{
    char cod[TAM][TXT];
    float precios[TAM];
    int cantProd =0;
    int cantUV[TAM] = {0};
    float recaudacion = 0;
    cantProd = CargaProductos(precios,cod,TAM);
    ventas(cod,precios,cantUV,&recaudacion,cantProd);
    printf("La recaudacion total es de: %.2f\n", recaudacion);
    minimo(cod,cantUV,cantProd);
    listado(cod,precios,cantProd);

    return 0;

}

int CargaProductos(float precio[], char cod[][TXT], int ce)
{
    char codAux[TAM];
    int i=0;
    printf("Ingrese codigo de producto (FIN para terminar): ");
    leeryValidarTexto(codAux,TAM);
    while(strcmpi(codAux,"FIN") != 0 && i<ce)
    {
        strcpy(cod[i],codAux);
        printf("Ingrese precio del producto: ");
        scanf("%f", &precio[i]);
        i++;
        printf("Ingrese codigo de producto (FIN para terminar): ");
        leeryValidarTexto(codAux,TAM);
    }
    printf("Seccion cargar productos finalizada\n");
    return i; //retorna la cantidad de productos cargados

}


void ventas(char cod[][TXT], float precio[], int cantUV[], float *recaudacion, int ce)
{
    char codV[TAM];
    int cant;
    int pos;
    printf("Ingrese cantidad de ventasd del producto (0 para finalizar): ");
    leeyValidaInt(&cant, -1);
    while(cant>0)
    {
        printf("Ingrese codigo de producto: ");
        leeryValidarTexto(codV, TAM);
        pos = busqueda(cod,codV,ce);
        if(pos != -1)
        {
            *recaudacion +=precio[pos]*cant;
            cantUV[pos] +=cant;
        } else {
            printf("El codigo no existe.");
        }
        printf("Ingrese candtidad vendida del prodcto (0 para finalizar): ");
        leeyValidaInt(&cant, -1);

    }
    printf("Seccion de ventas finalizada.\n");
}

void minimo(char cod[][TXT],int cantUV[], int ce)
{
    int min = buscarMinimo(cantUV,ce);
    for(int i=0;i<ce;i++)
    {
        if(cantUV[i] == min)
        {
            printf("El producto %s tuvo la menor cantidad vencida con %d", cod[i], cantUV[i]);
        }
    }
}

int buscarMinimo(int cantUV[], int ce)
{
    int min=cantUV[0];
    for(int i=0; i<ce; i++)
    {
        if(cantUV[i]<min)
        {
            min=cantUV[i];
        }
    }
    return min;
}

void listado(char cod[][TXT],float precio[], int ce)
{
    burbujeo(cod,precio,ce);
    for(int i = 0; i<ce; i++)
    {
        printf("%s - %.2f",cod[i],precio[i]);
    }
}


void leeyValidaInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato <= lim)
    {
        printf("Cantidad Incorrecta. Reingrese: ");
        scanf("%d",dato);
    }
}


void burbujeo(char cod[][TXT],float precio[],int ce)
{
    char AUX[TXT];
    float auxP;
    int j, cota = ce-1;
    int desordenado = 1;

    while(desordenado)
    {
        desordenado = 0;
        for(j=0;j<cota;j++)
        {
            if(strcmpi(cod[j],cod[j+1]) > 0)
            {
                strcpy(AUX,cod[j]);
                strcpy(cod[j],cod[j+1]);
                strcpy(cod[j+1],AUX);
                auxP = precio[j];
                precio[j] = precio[j+1];
                precio[j+1] = auxP;
                desordenado = j;

            }
        }
        cota = desordenado;
    }
}


int busqueda(char cod[][TXT], char codV[], int ce)
{
    int pos = -1, flag = 0, i=0;
    while(flag==0 && i<ce)
    {
        if(strcmpi(codV,cod[i]) == 0)
        {
            flag = 1;
            pos = i;
        }
        i++;
    }
    return pos;
}

void leerTexto(char texto[], int largo)
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

void leeryValidarTexto(char texto[], int largo)
{
    leerTexto(texto,largo);
    while(strlen(texto) != 3)
    {
        printf("El texto no puede ser vacio. Reingrese: ");
        leerTexto(texto,largo);
    }

}
