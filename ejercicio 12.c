/*Se dispone de un archivo con nombre Llamadas.dat que contiene llamadas telefónicas realizadas en una
empresa. Por cada llamada se dispone de la siguiente información:
• Sector (15 caracteres máximo)
• Duración en segundos (entero)
• Tipo de llamada (entero: 1 local, 2 larga distancia, 3 celular)
El archivo se encuentra organizado por Sector. Se solicita:
a. Calcular y mostrar por cada sector, la cantidad de llamadas realizadas de cada tipo.
b. Determinar cuál es el sector que habló la mayor cantidad de tiempo.
c. En un archivo llamado costos.dat hay un único registro que contiene los costos por segundo de los
tres tipos de llamadas (3 float). Se debe generar el archivo gastos.dat que totalice los gastos de
llamadas de cada sector.
d. Realizar una función que muestre los datos almacenados en gastos.dat en forma de listado.
e. Generar un archivo para cada sector con el detalle de llamadas valorizado. El archivo se debe
generar con nombresector.dat y debe contener:
• Duración en segundos (entero)
• Tipo de llamada (entero)
• Costo de la llamada (float) */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TXT 16

typedef struct 
{
    char sector[TXT];
    int duracion;
    int tipoLlamada;

}LLAMADAS;

typedef struct 
{
    float costo1;
    float costo2;
    float costo3;

} COSTOS;

typedef struct 
{
    char sector[TXT];
    float gastos;

} GASTOS;

typedef struct 
{
    int duracion;
    int tipoLlamada;
    float costoLlamada;

} SECTOR;

FILE *abrirArchivo(char nombre[],char tipo[]);
void procesarArchivo();
void mostrarGastos(char nombreArchivo[]);

int main()
{
    procesarArchivo();
    return 0;
}

void procesarArchivo()
{
    FILE *archLlamadas,*archCostos,*archGastos,*ArchSector;
    LLAMADAS auxLlamadas;
    COSTOS auxCostos;
    GASTOS auxGastos;
    SECTOR auxSector;
    int llamada1,llamada2,llamada3,duracion,primerSector=1,mayorDuracion=0;
    char sectorAnterior[TXT];
    char mayorSector[TXT];
    char nombreArchivo[20];
    float costoLlamadaActual,gastoTotalSector;

    archLlamadas=abrirArchivo("Llamadas.dat","rb");
    archCostos=abrirArchivo("Costos.dat","rb");
    archGastos=abrirArchivo("gastos.dat","wb");
    fread(&auxLlamadas,sizeof(auxLlamadas),1,archLlamadas);
    while(!feof(archLlamadas))
    {
        strcpy(sectorAnterior,auxLlamadas.sector);
        llamada1=0;
        llamada2=0;
        llamada3=0;
        duracion=0;
        gastoTotalSector=0;
        
        strcpy(nombreArchivo,auxLlamadas.sector);
        strcat(nombreArchivo,".dat");
        ArchSector=abrirArchivo(nombreArchivo,"wb");
        while(!feof(archLlamadas) && strcpy(sectorAnterior,auxLlamadas.sector)==0)
        {
            costoLlamadaActual=0;
            if(auxLlamadas.tipoLlamada==1)
            {
                llamada1++;
                duracion=duracion + auxLlamadas.duracion;
                costoLlamadaActual= auxLlamadas.duracion * auxCostos.costo1;
            }
            else if(auxLlamadas.tipoLlamada==2)
            {
                llamada2++;
                duracion=duracion + auxLlamadas.duracion;
                costoLlamadaActual = auxLlamadas.duracion *auxCostos.costo2;
            }
            else
            {
                llamada3++;
                duracion=duracion + auxLlamadas.duracion;
                costoLlamadaActual = auxLlamadas.duracion * auxCostos.costo3;
            }
            gastoTotalSector= gastoTotalSector + costoLlamadaActual;

            auxSector.duracion=duracion;
            auxSector.costoLlamada=costoLlamadaActual;
            auxSector.tipoLlamada=auxLlamadas.tipoLlamada;
            fwrite(&auxSector,sizeof(auxSector),1,ArchSector);

            fread(&auxLlamadas,sizeof(auxLlamadas),1,archLlamadas);
        }

        printf("\nCANTIDAD DE LLAMADAS DEL SECTOR: %s",sectorAnterior);
        printf("\nTIPO 1: %d || TIPO 2: %d || TIPO 3: %d",llamada1,llamada2,llamada3);

        if(primerSector==1 || duracion>mayorDuracion)
        {
            mayorDuracion=duracion;
            strcpy(mayorSector,sectorAnterior);
            primerSector==0;
        }

        strcpy(auxGastos.sector,sectorAnterior);
        auxGastos.gastos=gastoTotalSector;
        fwrite(&auxGastos,sizeof(auxGastos),1,archGastos);

        fclose(ArchSector);
        
    }
    printf("El sector %s es el que mas tiempo hablo con %d\n",mayorSector,mayorDuracion);
    fclose(archCostos);
    fclose(archGastos);
    fclose(archLlamadas);
    mostrarGastos("gastos.dat");
}

void mostrarGastos(char nombreArchivo[])
{
    FILE *fp;
    GASTOS aux;
    fp=abrirArchivo(nombreArchivo,"rb");
    printf("\nListado de gastos: \n");
    fread(&aux,sizeof(aux),1,fp);
    while(!feof(fp))
    {
        printf("\n%.2f",aux.gastos);
        fread(&aux,sizeof(aux),1,fp);
    }
    fclose(fp);
}

FILE *abrirArchivo(char nombre[],char tipo[])
{
    FILE *fp;
    fp=fopen(nombre,tipo);
    if(fp==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    return fp;
}