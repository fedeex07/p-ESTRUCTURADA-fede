/*Una empresa de alquiler de autos tiene una flota de 30 autos de alta gama, identificados por su número de
patente, cargado en la memoria principal en un vector de 30 posiciones. Al comenzar el procesamiento de
los alquileres, se ingresa la fecha y la cotización del dólar de ese día. A continuación, se ingresan los siguientes
datos correspondiente a cada alquiler realizado en el día:
• Patente del auto (alfanumérico, de 6 caracteres)
• Cantidad de días de alquiler (entero, mayor que 0)
• Precio diario del alquiles en dólares (real, mayor que 0)
Para finalizar la carga del día, se ingresa una patente de auto igual a “FINDIA”
Determinar e informar:
a. El porcentaje de autos alquilados durante el día.
b. Realizar el informe con el formato siguiente:*/

#include <stdio.h>
#include <string.h>
#define TAM 30

int CargarAlquiler(char[][7],int *,float *,int);
void procesamientoAlquiler(int *,int *,int *,float *);
int busqueda(char[][7],char[],int);
void leertexto(char[],int);
void leeryValidarTexto(char[],int);
void leeryValidarInt(int *,int);
void leeryValidarInt2(int *,int,int);
void leeryValidarFloat(float *,int);

int main()
{
    int dia,mes,anio,cantAlq;
    int dias[TAM];
    float precio[TAM],dolar,porcentaje;
    char autos[TAM][7] = {
         "AA111A","AA222B","AA333C","AA444D","AA555E",
    "AA666F","AA777G","AA888H","AA999I","AB111J",
    "AB222K","AB333L","AB444M","AB555N","AB666O",
    "AB777P","AB888Q","AB999R","AC111S","AC222T",
    "AC333U","AC444V","AC555W","AC666X","AC777Y",
    "AC888Z","AC999A","AD111B","AD222C","AD333D"
    };
    
    procesamientoAlquiler(&dia,&mes,&anio,&dolar);
    cantAlq = CargarAlquiler(autos,dias,precio,TAM);
    porcentaje =  ((float)cantAlq/TAM)*100;
    printf("El porcentaje de vehiculos alquilados es %.2f\n",porcentaje);

    return 0;
}

int CargarAlquiler(char patente[][7],int *dia,float *precio,int ce)
{
    int i=0;
    int pos;   
    char patenteAUX[TAM];
    printf("--Alquileres del dia--\n");
    printf("Ingrese la patente del auto (FINDIA para terminar): ");
    leeryValidarTexto(patenteAUX,7);
    while(strcmpi(patenteAUX,"FINDIA") != 0 && i<ce)
    {
        pos = busqueda(patente,patenteAUX,ce);
        if(pos != -1)
        {
            printf("Ingrese cantidad de dias para alquilar: ");
            leeryValidarInt(&dia[pos],1);
            printf("Ingrese precio en dolares: ");
            leeryValidarFloat(&precio[pos],1);
            i++;
            printf("Ingrese la patente del auto: ");

        } else {
            printf("Patente no encontrada. Reingrese: ");
            
        }
        leeryValidarTexto(patenteAUX,7);
    }
    return i;

}

void procesamientoAlquiler(int *dia, int *mes, int *anio,float *dolar)
{
    printf("--Procesamiento de alquileres--\n");
    printf("Ingrese el dia(1-31): ");
    leeryValidarInt2(dia,1,31);
    printf("Ingrese el mes(1-12): ");
    leeryValidarInt2(mes,1,12);
    printf("Ingrese el anio(2000-2026): ");
    leeryValidarInt2(anio,2000,2026);
    printf("Ingrese cotizacion del dolar del dia: ");
    leeryValidarFloat(dolar,0);

}

int busqueda(char patente[][7],char patenteAUX[],int ce)
{
    int pos = -1, flag = 0, i=0;
    while(flag == 0 && i<ce)
    {
        if(strcmpi(patente[i],patenteAUX) == 0)
        {
            flag = 1;
            pos = i;
        }
        i++;
    }
    return pos;
}


void leertexto(char texto[],int largo)
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
    leertexto(texto,largo);
    while(strlen(texto) !=6)
    {
        printf("El texto ingresado es incorrecto. Reingrese: ");
        leertexto(texto,largo);
    }
}

void leeryValidarInt(int *dato,int lim)
{
    scanf("%d",dato);
    while(*dato <lim)
    {
        printf("Cantidad incorrecta. Reingrese: ");
        scanf("%d",dato);
    }
}

void leeryValidarInt2(int *dato, int min, int max)
{
    scanf("%d",dato);
    while(*dato<min || *dato>max)
    {
        printf("Error. Ingrese nuevamente: ");
        scanf("%d",dato);
    }
}

void leeryValidarFloat(float *dato, int lim)
{
    scanf("%f",dato);
    while(*dato < lim)
    {
        printf("Cantidad incorrecta. Reingrese: ");
        scanf("%f",dato);
    }
}
