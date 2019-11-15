#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// Estructura utilizada para almacenar datos, para poder acceder a ellos de forma mas organizada.
typedef struct
{
    // Array que contiene todas la ciudades en orden, teniendo en cuenta su codigo postal.
    char **arrayCiudades;
    // Array que contiene la relacion de indice y genero.
    char arrayGenero[2];
    // Array que contiene la relacion de indice y gustos de genero.
    char arrayGustos[4];
} accesoDatos;

// Estructura utilizada para retornar mas valores de la funcion parserPersonas.
typedef struct
{
    char **personas;
    long cantGente;
} infoPersonas;

// Funcion que se dedica a leer el archivo que contiene las ciudades y genera la anteriormente mencionada arrayCiudades.
char **parserCiudades(const char *fileName)
{
    char **arrayCiudades = NULL;
    FILE *fp;
    fp = fopen(fileName, "r");
    char buff[80];
    // Ciclo que recorre todos las lineas del archivo que contiene a las ciudades relacionadas con su codigo postal.
    for (int linea = 0; fgets(buff, 80, fp); linea++)
    {
        // Al ver que hay otra linea que contiene informacion de una ciudad, se pide memoria para poder almacenarla.
        arrayCiudades = (char **)realloc(arrayCiudades, (linea + 1) * sizeof(char *));
        // La string es almacenada como una array de chars, aca se reserva la memoria.
        char *temp = (char *)calloc(80, sizeof(char));
        int letraTemp = 0, letra = 0;

        // En esta porcion de codigo, se "parsea" el archivo para almacenar solo el nombre de la ciudad, ya que su codigo postal es el indice que la
        // ubica en la array.
        // Recorremos hasta encontrar una coma, que divide el codigo del nombre.
        while (buff[letra++] != ',')
            ;
        // Comenzamos a almacenar caracter a caracter en la ubicacion a la que apunta temp.
        while ((buff[letra] != ' ' || buff[letra + 1] != ' ') && (buff[letra] != '\n'))
        {
            temp[letraTemp] = buff[letra];
            letraTemp++;
            letra++;
        }
        // Finalizamos la nueva array con un caracter terminador.
        temp[letraTemp] = '\0';
        // Y hacemos que el puntero correspondiente apunte a temp.
        arrayCiudades[linea] = temp;
    }
    // Se cierra el archivo y se retorna la arrayCiudades.
    fclose(fp);
    return arrayCiudades;
}

// Funcion que se encarga de cargar el archivo que contiene las personas a una array, de arrays que contienen cada linea.
infoPersonas *parserPersonas(const char *fileName)
{
    // Se relalliza un algoritmo parecido a la funcion anterior, pensamos en hacer una sola que cambie en la forma de parsear.
    // Pero decidimos hacer dos separadas para no aunmentar la complejidad del codigo.
    infoPersonas *listaPersonas = (infoPersonas *)calloc(1, sizeof(infoPersonas));
    char **arrayPersonas = NULL;
    FILE *fp;
    fp = fopen(fileName, "r");
    char buff[80];
    int linea = 0;
    // Ciclo que recorre todas las lineas del archivo.
    while (fgets(buff, 80, fp))
    {
        arrayPersonas = (char **)realloc(arrayPersonas, (linea + 1) * sizeof(char *));
        char *temp = (char *)calloc(80, sizeof(char));
        // Copiamos en temp, el contenido de buff sin parsear. Ya que decidimos que es mas eficiente realizar ese proceso solo con las personas,
        // seleccionadas de forma random.
        strcpy(temp, buff);
        arrayPersonas[linea] = temp;
        linea++;
    }
    fclose(fp);
    listaPersonas->personas = arrayPersonas;
    listaPersonas->cantGente = linea;
    return listaPersonas;
}

// Funcion semi-auxiliar, que realiza un intercambio del contenido de dos variables.
void swap(long *a, long *b)
{
    // Utilizamos variables en modo long ya que esta funcion es utilizada en otra funcion que obtiene de manera aleatoria los indices de las personas
    // en la arrayPersona
    long c;
    c = *a;
    *a = *b;
    *b = c;
}

// Funcion que devulve una array de numeros unicos, generados de manera random, para poder elgir de manera aleatoria las personas a conformar el archivo final.
long *calcRand(long cantGente)
{
    // Introduciomos la generacion de numeros aleatorios.
    srand(time(NULL));
    // Se reserva arrayPersonasmemoria para la variable resultado que sera una array de longs.
    long *resultado = (long *)calloc(cantGente, sizeof(long));
    // Se rellena una array de largo de la cantidad de gente pedidad de forma acendiente.
    for (long i = 0; i < cantGente; i++)
    {
        resultado[i] = i;
    }
    // Cilio que randomiza los resultados, intercambiando los contenidos de cada posicion de la array.
    for (long i = cantGente - 1; i >= 0; i--)
    {
        unsigned long x = rand();
        x <<= 15;
        x ^= rand();
        x %= cantGente;
        swap(&(resultado[i]), &(resultado[x]));
    }
    return resultado;
}

void escritorDeArchivo(long cantGenteP, infoPersonas *listaPersonas, const char *fileName, accesoDatos *datos)
{

    FILE *fp;
    // Abrimios un archivo en modo escritura, sino existe se creara.
    fp = fopen(fileName, "w");
    // Calculamos de forma aleatoria las personas.
    long *listRand = calcRand(listaPersonas->cantGente);
    // Recorremos la lista de indeces de personas aleatorias, mientras seran escritas en el archivo.
    for (long i = 0; i < cantGenteP; i++)
    {
        char **partes;
        partes = (char **)calloc(6, sizeof(char *));
        char *parte;
        parte = strtok(listaPersonas->personas[listRand[i]], ",");
        for (int indice = 0; parte != NULL; indice++)
        {
            partes[indice] = parte;
            parte = strtok(NULL, ",");
        }
        fputs(partes[0], fp);
        fputc(',', fp);
        fputs(partes[1], fp);
        fputc(',', fp);
        char *ptr;
        long index = strtol(partes[2], &ptr, 10);
        fputs(datos->arrayCiudades[--index], fp);
        fputc(',', fp);
        fputs(partes[3], fp);
        fputc(',', fp);
        index = partes[4][0] - '0';
        fputc(datos->arrayGenero[--index], fp);
        fputc(',', fp);
        index = partes[5][0] - '0';
        fputc(datos->arrayGustos[--index], fp);
        fputc('\n', fp);
    }
    fclose(fp);
}

/* //? FORMA COMPLETA SIN SIMPLIFICARCORRECTA
void escritorDeArchivo(long cantGenteP, infoPersonas *listaPersonas, const char *fileName, accesoDatos *datos)
{

    FILE *fp;
    // Abrimios un archivo en modo escritura, sino existe se creara.
    fp = fopen(fileName, "w");
    // Calculamos de forma aleatoria las personas.
    long *listRand = calcRand(listaPersonas->cantGente);
    // Recorremos la lista de indeces de personas aleatorias, mientras seran escritas en el archivo.
    for (long i = 0; i < cantGenteP; i++)
    {
        int cantComas = 0, indiceCodPostal = 0, banderaCodigo = 0;
        char *codigoPostal;
        codigoPostal = (char *)calloc(1, sizeof(char));

        for (int j = 0; listaPersonas->personas[listRand[i]][j] != '\n'; j++)
        {
            if (listaPersonas->personas[listRand[i]][j] == ',')
                cantComas++;
            if (cantComas < 2 || (cantComas == 3 && banderaCodigo != 0))
            {
                fputc(listaPersonas->personas[listRand[i]][j], fp);
            }
            if (cantComas == 2)
            {
                codigoPostal = (char *)realloc(codigoPostal, (indiceCodPostal + 1) * sizeof(char));
                codigoPostal[indiceCodPostal] = listaPersonas->personas[listRand[i]][j + 1];
                indiceCodPostal++;
            }

            if (cantComas == 3 && banderaCodigo == 0)
            {
                codigoPostal[indiceCodPostal - 1] = '\0';
                fputc(',', fp);
                char *ptr;
                long codigo = strtol(codigoPostal, &ptr, 10);
                codigo -= 1;
                fputs(datos->arrayCiudades[codigo], fp);
                banderaCodigo = 1;
                fputc(',', fp);
            }
            if (cantComas == 4)
            {
                if (listaPersonas->personas[listRand[i]][j] == ',')
                {
                    fputc(',', fp);
                }
                else
                {
                    int index = listaPersonas->personas[listRand[i]][j] - '0';
                    index -= 1;
                    fputc(datos->arrayGenero[index], fp);
                }
            }
            if (cantComas == 5)
            {
                if (listaPersonas->personas[listRand[i]][j] == ',')
                {
                    fputc(',', fp);
                }
                else
                {
                    int index = listaPersonas->personas[listRand[i]][j] - '0';
                    index -= 1;
                    fputc(datos->arrayGustos[index], fp);
                }
            }
        }
        fputc('\n', fp);
        // printf("%s", listaPersonas->personas[listRand[i]]);
    }

    fclose(fp);
}*/

int main()
{

    accesoDatos datos;
    datos.arrayCiudades = parserCiudades("codigoLocalidades.txt");
    strcpy(datos.arrayGenero, "MF");
    strcpy(datos.arrayGustos, "FMAN");

    infoPersonas *listaPersonas = parserPersonas("personas.txt");

    long cantGenteP;

    printf("%s", "Ingresa la cantidad de personas a parsear: ");
    scanf("%ld", &cantGenteP);
    escritorDeArchivo(cantGenteP, listaPersonas, "salida.txt", &datos);
    return 0;
}
