#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char nomyapy[81];
    int nota1;
    int nota2;
    float prom;

}Salumno;

void clasificacion();
void lectura(char []);

int main()
{
    Salumno alum;
    printf("Archivo Original: ");
    lectura("alumno.dat");

    clasificacion();

    printf("\nPromocionados: \n");
    lectura("promocionados.dat");

    printf("\nCursados: \n");
    lectura("cursado.dat");

    printf("\nReprobados: \n");
    lectura("reprobados.dat");

    return 0;
}
void lectura(char archivo[])
{
    Salumno alum;
    FILE*fp;
    fp=fopen(archivo,"rb");
    if(fp==NULL)
    {
        printf("Error al abrir el archivo %s.",archivo);
        system("pause");
        exit(1);
    }
    fread(&alum,sizeof(alum),1,fp);
    printf("\n%-8s  %-30s %6s  %6s  %6s\n","DNI","Nombre y Apellido","Nota 1","Nota 2","Nota Promedio");
    while(!feof(fp))
    {
        printf("\n%-8d  %-30s %6d  %6d  %6.2f\n",alum.dni,alum.nomyapy,alum.nota1,alum.nota2,alum.prom);
        fread(&alum,sizeof(alum),1,fp);
    }
    fclose(fp);
}
void clasificacion()
{
    Salumno alum;
    FILE*fp;
    FILE*prome;
    FILE*cursa;
    FILE*reprob;

    fp=fopen("alumno.dat","rb");
    prome=fopen("promocionados.dat","wb");
    cursa=fopen("cursado.dat","wb");
    reprob=fopen("reprobados.dat","wb");
    if(fp==NULL|| prome==NULL|| cursa==NULL|| reprob==NULL)
    {
        printf("Error al abrir algun archivo");
        system("pause");
        exit(1);
    }
    fread(&alum,sizeof(alum),1,fp);
    while(!feof(fp))
    {
        if(alum.nota1>=7&&alum.nota2>=7)
        {
            fwrite(&alum,sizeof(alum),1,prome);
        }
        else if(alum.nota1>=4&&alum.nota2>=4)
        {
            fwrite(&alum,sizeof(alum),1,cursa);
        }
        else
        {
            fwrite(&alum,sizeof(alum),1,reprob);
        }

        fread(&alum,sizeof(alum),1,fp);
    }
    fclose(fp);
    fclose(prome);
    fclose(cursa);
    fclose(reprob);
}
