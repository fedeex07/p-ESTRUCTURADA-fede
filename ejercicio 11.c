/*Se dispone de un archivo llamado Rating.dat que guarda la información de los puntos obtenidos de rating
en los distintos programas de canales de cable a lo largo del día. Cada registro contiene:
• Número de canal (entero)
• Programa (texto de 35 caracteres máximo)
• Rating (float)
El archivo se encuentra ordenado por canal.
Se solicita informar:
a. Aquellos canales que obtengan menos de 15 puntos en total.
b. El canal más visto.
c. Generar un archivo con el promedio de rating de cada canal que incluya dos campos:
• Número de canal.
• Promedio. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TXT 36

typedef struct 
{
    int numCanal;
    char programa[TXT];
    float rating;

} RATING;

typedef struct 
{
    int numCanal;
    float promedio;

} PROMEDIO;

void procesarArchivo();
FILE *abrirArchivo(char nombre[],char tipo[]);

int main()
{
    procesarArchivo();
    return 0;
}

void procesarArchivo()
{
    FILE *archRating,*archPromedio;
    RATING auxRating;
    PROMEDIO auxPromedio;
    int canalAnterior,canalMasVisto=0,PrimerCanal=1,programa;
    float sumaRating,mayorRating=0;

    archPromedio=abrirArchivo("Promedio.dat","wb");
    archRating=abrirArchivo("Rating.dat","rb");
    fread(&auxRating,sizeof(auxRating),1,archRating);
    while(!feof(archRating))
    {
        canalAnterior=auxRating.numCanal;
        sumaRating=0;
        programa=0;
        while(!feof(archRating) && canalAnterior==auxRating.numCanal)
        {
            sumaRating=sumaRating + auxRating.rating;
            programa++;
            fread(&auxRating,sizeof(auxRating),1,archRating);
        }

        if(sumaRating < 15)
        {
            printf("El canal %d tiene menos de 15 de rating.\n",canalAnterior);
        }
        if(PrimerCanal==1 || sumaRating>mayorRating)
        {
            mayorRating=sumaRating;
            canalMasVisto=canalAnterior;
            PrimerCanal=0;
        }

        auxPromedio.numCanal=canalAnterior;
        auxPromedio.promedio=sumaRating/programa;
        fwrite(&auxRating,sizeof(auxRating),1,archRating);
    }
    fclose(archPromedio);
    fclose(archRating);

    if(PrimerCanal==0)
    {
        printf("El canal %d es el canal mas visto",canalMasVisto);
    }
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
