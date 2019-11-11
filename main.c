#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



int main() {
    char** arrayCiudades;
    arrayCiudades = calloc(1, sizeof(char*));
    *arrayCiudades = calloc(255, sizeof(char));
    FILE *fp;
    char buff[80];
    fp = fopen("codigoLocalidades.txt", "r");
    int i=0;
    
    while(fgets(buff, 80, fp)) {
        char temp[80] = "";
        int bandera = 0, k = 0, j = 0;
        while((buff[j]!=' '||buff[j+1]!=' ')&&(buff[j]!='\n')){
            if(bandera == 1){
                temp[k]=buff[j];
                k++;
            }
            if(buff[j]==',')
                bandera = 1;
            
            
            temp[k]='\0';
            j++;
        }
            printf("%i %s\n",i,temp);



        
        //arrayCiudades = realloc(arrayCiudades, sizeof(char*));
       // arrayCiudades[i] = calloc(80,sizeof(char));
    

        i++;
    }
    fclose(fp);
    
}