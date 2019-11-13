#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>


typedef struct{
    char ** arrayCiudades;
    char arrayGenero[2][1];
    char arrayGustos[4];
}accesoDatos;

char **parserCiudades(const char *fileName)
{

    char **arrayCiudades = NULL;
    FILE *fp;
    fp = fopen(fileName, "r");
    char buff[80];
    for(int linea = 0; fgets(buff, 80, fp); linea++) {
        arrayCiudades = (char**)realloc(arrayCiudades, (linea+1)*sizeof(char*));
        char* temp = (char *)calloc(80,sizeof(char));
        int  letraTemp = 0, letra = 0;

        while(buff[letra++] != ',');

        while ((buff[letra] != ' ' || buff[letra + 1] != ' ') && (buff[letra] != '\n'))
        {
            temp[letraTemp] = buff[letra];
            letraTemp++;
            letra++;
        }
        temp[letraTemp] = '\0';
        arrayCiudades[linea] = temp;
    }

    fclose(fp);
    return arrayCiudades;
}

char **parserPersonas(const char *fileName)
{

    char **arrayPersonas = NULL;
    FILE *fp;
    fp = fopen(fileName, "r");
   char buff[80];
    for(int linea = 0; fgets(buff, 80, fp); linea++) {
        arrayPersonas = (char**)realloc(arrayPersonas, (linea+1)*sizeof(char*));
        char* temp = (char *)calloc(80,sizeof(char));
        strcpy(temp, buff);
        arrayPersonas[linea]= temp;
        //printf("%s", arrayPersonas[linea]);
    }

    fclose(fp);
    return arrayPersonas;
}

void swap(long * a, long * b){
    long c;
    c = *a;
    *a = *b;
    *b = c;
}

long * calcRand(long cantGente){
    srand(time(NULL));
    long * resultado = (long *)calloc(cantGente, sizeof(long));

    for(long i = 0; i < cantGente; i++){
        resultado[i] = i;
    }

    for(long i = cantGente-1; i >= 0; i--){
        unsigned long x = rand();
        x <<= 15;
        x ^= rand();
        x %= cantGente;

        //swap(&(resultado[i]), &(resultado[x]));
    }

    return resultado;
}



int main(){
    accesoDatos datos;
    datos.arrayCiudades =  parserCiudades("codigoLocalidades.txt");
    strcpy(datos.arrayGenero, "MF");
    strcpy(datos.arrayGustos, "FMAN");

    char ** arrayPersonas = parserPersonas("personas.txt");
    long cantGenteP;

    printf("%s", "Puto ingresa la cantidad de gente: ");
    scanf("%ld", &cantGenteP);

    long * listRand= calcRand(99999/*cantGente*/);


    for(long i=0; i < cantGenteP; i++) {
        printf("%s", arrayPersonas[listRand[i]]);
    }
}
