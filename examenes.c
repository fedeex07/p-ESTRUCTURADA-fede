/*Ejercicio 2. Se dispone del archivo binario examenes.dat, ordenado por curso, con los siguientes datos por examen rendido:

Curso (entero)
Legajo del alumno (entero)
Nota (float, de 0 a 10)

Se solicita:
a) Para cada curso, informar la cantidad de exámenes rendidos y el promedio de notas. El cálculo del promedio debe hacerse en otra función.
b) Informar el curso con el mejor promedio.
c) Generar un archivo binario resumen.dat con un registro por curso, que contenga el número de curso y su promedio.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int curso;
    int legajo;
    float nota;

} EXAMENES;

typedef struct 
{
    int curso;
    float promedio;

} RESUMEN;


FILE *abrirArchivo(char[],char[]);
void procesarArchivo();
float promedio(float,int);

int main()
{
    procesarArchivo();
    
    return 0;
}

void procesarArchivo()
{
    FILE *archExamenes,*archResumen;
    EXAMENES auxExamenes;
    RESUMEN auxResumen;
    int cursoAnterior,cantExam,mejorCurso,primerCurso=1;
    float promedioNotas,mejorPromedio,notasTotales;

    archExamenes=abrirArchivo("examenes.dat","rb");
    archResumen=abrirArchivo("resumen.dat","wb");
    fread(&auxExamenes,sizeof(auxExamenes),1,archExamenes);
    while(!feof(archExamenes))
    {
        cursoAnterior=auxExamenes.curso;
        cantExam=0;
        notasTotales=0;
        while(!feof(archExamenes) && cursoAnterior==auxExamenes.curso)
        {
            notasTotales+=auxExamenes.nota;
            cantExam++;
            fread(&auxExamenes,sizeof(auxExamenes),1,archExamenes);
        }
        promedioNotas=promedio(notasTotales,cantExam);
        printf("Curso %d - Cantidad de examenes: %d - Promedio de notas: %.2f.\n",cursoAnterior,cantExam,promedioNotas);

        auxResumen.curso=cursoAnterior;
        auxResumen.promedio=promedioNotas;
        fwrite(&auxResumen,sizeof(auxResumen),1,archResumen);

        if(primerCurso==1 || promedioNotas > mejorPromedio)
        {
            mejorPromedio=promedioNotas;
            mejorCurso=cursoAnterior;
            primerCurso=0;
        }
    }
    printf("El curso %d tiene mejor promedio con %.2f.\n",mejorCurso,mejorPromedio);
    fclose(archExamenes);
    fclose(archResumen);
}

float promedio(float notas,int cantExam)
{
    float prom;
    prom=notas/cantExam;
    return prom;
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
