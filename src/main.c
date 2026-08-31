#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: Crear un bufer que mande una actualizacion a cada letra que escriba
//TODO: Printear la lista de directorios y archivos de acuerdo al estado del bufer

char* get_working_directory();

int main(){
    char* working_directory = get_working_directory();
    printf("%s", working_directory);

    return 0;
}

// Obtiene el working directory
char* get_working_directory(){
    FILE *fp;
    int status;
    char path[PATH_MAX];
    char* working_directory;

    // popen() devuelve un file pointer cuyo contenido es la salida del comando dado
    fp = popen("pwd", "w");
    
    // Manejo de errores
    //if (fp == NULL) { MANEJO ERRORES }

    // Imprime el contenido de fp para debug
    //while (fgets(path, PATH_MAX, fp) != NULL)
        //printf("%s", path);

    // Asigna la salida del comando a la variable de retorno
    working_directory = fgets(path, PATH_MAX, fp); 

    // Cierra el bufer y manejo de errores 
    // status = pclose(fp);
    // if (status == -1) { ERROR REPORTADO POR pclose() }

    return working_directory;
}
