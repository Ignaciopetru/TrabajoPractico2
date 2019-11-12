#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char **parserCiudades(const char *fileName)
{
    char **arrayCiudades;
    arrayCiudades = (char **)calloc(1, sizeof(char *));
    *arrayCiudades = (char *)calloc(255, sizeof(char));
    FILE *fp;
    char buff[80];
    fp = fopen(fileName, "r");
    int i = 0;

    while(fgets(buff, 80, fp)) {
       
       
        char temp[80] = "";
        int bandera = 0, k = 0, j = 0;
        while ((buff[j] != ' ' || buff[j + 1] != ' ') && (buff[j] != '\n'))
        {
            if (bandera == 1)
            {
                temp[k] = buff[j];
                k++;
            }
            if (buff[j] == ',')
                bandera = 1;

            temp[k] = '\0';
            j++;
        }
        strcpy(*arrayCiudades+i, temp);
        arrayCiudades = (char**)realloc(arrayCiudades, (sizeof(char*) * i + 1));
        arrayCiudades[i] = (char *)calloc(100,sizeof(char));

        i++;
        printf("%i %s\n", i,*arrayCiudades+i);
    }
    fclose(fp);
    //return arrayCiudades;
}

int main()
{
    //printf("%s", *parserCiudades("codigoLocalidades.txt")[0]);
    parserCiudades("codigoLocalidades.txt");
}