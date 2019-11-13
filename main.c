#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// Structura que almacena datos utilez para poder acceder a ellos de forma mas organizada.
typedef struct{
    // Array que contiene todas la ciudades en orden, teniendo en cuenta su codigo postal.
    char ** arrayCiudades;
    // Array que contiene la relacion de indice y genero.
    char arrayGenero[2];
    // Array que contiene la relacion de indice y gustos de genero.
    char arrayGustos[4];
}accesoDatos;

// Funcion que se dedica a leer el archivo que contiene las ciudades y genera la anteriormente mencionada arrayCiudades.
char **parserCiudades(const char *fileName){
    char **arrayCiudades = NULL;
    FILE *fp;
    fp = fopen(fileName, "r");
    char buff[80];
    // Ciclo que recorre todos las lineas del archivo que contiene a las ciudades relacionadas con su codigo postal.
    for(int linea = 0; fgets(buff, 80, fp); linea++) {
        // Al ver que hay otra linea que contiene informacion de una ciudad, se pide memoria para poder almacenarla.
        arrayCiudades = (char**)realloc(arrayCiudades, (linea+1)*sizeof(char*));
        // La string es almacenada como una array de chars, aca se reserva la memoria.
        char* temp = (char *)calloc(80,sizeof(char));
        int  letraTemp = 0, letra = 0;

        // En esta porcion de codigo, se "parsea" el archivo para almacenar solo el nombre de la ciudad, ya que su codigo postal es el indice que la
        // ubica en la array.
        // Recorremos hasta encontrar una coma, que divide el codigo del nombre.
        while(buff[letra++] != ',');
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
char **parserPersonas(const char *fileName){
    // Se relalliza un algoritmo parecido a la funcion anterior, pensamos en hacer una sola que cambie en la forma de parsear.
    // Pero decidimos hacer dos separadas para no aunmentar la complejidad del codigo.
    char **arrayPersonas = NULL;
    FILE *fp;
    fp = fopen(fileName, "r");
    char buff[80];
    // Ciclo que recorre todas las lineas del archivo.
    for(int linea = 0; fgets(buff, 80, fp); linea++) {
        arrayPersonas = (char**)realloc(arrayPersonas, (linea+1)*sizeof(char*));
        char* temp = (char *)calloc(80,sizeof(char));
        // Copiamos en temp, el contenido de buff sin parsear. Ya que decidimos que es mas eficiente realizar ese proceso solo con las personas,
        // seleccionadas de forma random.
        strcpy(temp, buff);
        arrayPersonas[linea]= temp;
    }
    fclose(fp);
    return arrayPersonas;
}

// Funcion semi-auxiliar, que realiza un intercambio del contenido de dos variables.
void swap(long * a, long * b){
    // Utilizamos variables en modo long ya que esta funcion es utilizada en otra funcion que obtiene de manera aleatoria los indices de las personas
    // en la arrayPersona
    long c;
    c = *a;
    *a = *b;
    *b = c;
}

// Funcion que devulve una array de numeros unicos, generados de manera random, para poder elgir de manera aleatoria las personas a conformar el archivo final.
long * calcRand(long cantGente){
    // Introduciomos la generacion de numeros aleatorios.
    srand(time(NULL));
    // Se reserva memoria para la variable resultado que sera una array de longs.
    long * resultado = (long *)calloc(cantGente, sizeof(long));
    // Se rellena una array de largo de la cantidad de gente pedidad de forma acendiente.
    for(long i = 0; i < cantGente; i++){
        resultado[i] = i;
    }
    // Cilio que randomiza los resultados, intercambiando los contenidos de cada posicion de la array.
    for(long i = cantGente-1; i >= 0; i--){
        unsigned long x = rand();
        x <<= 15;
        x ^= rand();
        x %= cantGente;
        swap(&(resultado[i]), &(resultado[x]));
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

    for(long i=0; i < cantGenteP; i++){
        printf("%s", arrayPersonas[listRand[i]]);
    }
}
