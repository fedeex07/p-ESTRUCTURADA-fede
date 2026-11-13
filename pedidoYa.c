/*En la empresa “Pedido Ya Mismo” tienen el archivo Repartos.dat con los siguientes datos: 
• Zona (entero) 
• Descripción (de hasta 50 caracteres) 
• Peso (float) en kilos 
por pedido Sabemos que el archivo está ordenado por zona y necesitamos conocer los siguientes datos: 
a. Las zonas que tengan menos de 15 kg en total. 
b. La zona que haya acumulado el mayor peso total de envíos. 
c. Generar un nuevo archivo binario llamado PesoTotal.dat que contenga un registro por cada zona incluyendo la zona y el peso total por zona.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 51

typedef struct 
{
    int zona;
    char desc[TXT];
    float peso;

}REPARTOS;


typedef struct 
{
    int zona;
    float pesoTotal;

} PESOTOTAL;

void procesarArchivo();
FILE *abrirArchivo(char nombre[],char tipo[]);

int main()
{
    procesarArchivo();
    return 0;
}

void procesarArchivo()
{
    FILE *archRepartos, *archPesoT;
    REPARTOS auxRepartos;
    PESOTOTAL auxPesoTotal;
    int zonaAnterior,zonaMayorPeso=0,primeraZona=1;
    float pesoAcumuladoZona,mayorPeso=0;

    archRepartos=abrirArchivo("Repartos.dat","rb");
    archPesoT=abrirArchivo("PesoTotal.dat","wb");
    fread(&auxRepartos,sizeof(auxRepartos),1,archRepartos);
    while(!feof(archRepartos))
    {
        zonaAnterior=auxRepartos.zona;
        pesoAcumuladoZona=0;
        while(!feof(archRepartos) && zonaAnterior==auxRepartos.zona)
        {
            pesoAcumuladoZona=pesoAcumuladoZona + auxRepartos.zona;
            fread(&auxRepartos,sizeof(auxRepartos),1,archRepartos);

        }
        if(pesoAcumuladoZona < 15)
        {
            printf("La zona %d tiene menos de 15 kg (%.2f)",zonaAnterior,pesoAcumuladoZona);
        }
        if(primeraZona==1 || pesoAcumuladoZona > mayorPeso)
        {
            pesoAcumuladoZona=mayorPeso;
            zonaMayorPeso=zonaAnterior;
            primeraZona=0;    
        }

        auxPesoTotal.zona=zonaAnterior;
        auxPesoTotal.pesoTotal=pesoAcumuladoZona;
        fwrite(&auxPesoTotal,sizeof(auxPesoTotal),1,archPesoT);
    }
    fclose(archPesoT);
    fclose(archRepartos);

    printf("La zona %d fue la que acumulo mas peso con %.2f.\n",zonaMayorPeso,mayorPeso);
    
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