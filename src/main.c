#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: Crear un bufer que mande una actualizacion a cada letra que escriba
//TODO: Printear la lista de directorios y archivos de acuerdo al estado del bufer

char* get_working_directory();
char* get_directory_contents(char* working_directory);

int main(){
    char* working_directory = get_working_directory();
    char* working_directory_contents = get_directory_contents(working_directory);
    printf("\n");
    printf("%s\n\n", working_directory);
    printf("%s", working_directory_contents);

    return 0;
}

// Obtiene el working directory
char* get_working_directory(){
    FILE *fp;
    int status;
    char path[PATH_MAX];

    // popen() devuelve un file pointer cuyo contenido es la salida del comando dado
    fp = popen("pwd", "r");
    if (fp == NULL){
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Obtiene la salida de pwd
    if (fgets(path, PATH_MAX, fp) == NULL) {
        fprintf(stderr, "Error leyendo pwd\n");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    //TODO: Cierra el bufer y manejo de errores 
    pclose(fp);
    // status = pclose(fp);
    // if (status == -1) { ERROR REPORTADO POR pclose() }
    
    // Sustituye el salto de linea por caracter nulo
    path[strcspn(path, "\n")] = '\0'; 

    return strdup(path);
}

char* get_directory_contents(char* working_directory){
    FILE* fp;
    //int status;
    char command[PATH_MAX];
    char line[PATH_MAX];
    char working_directory_contents[PATH_MAX] = {0};

    snprintf(command, sizeof(command), "ls -1p %s", working_directory);
    
    fp = popen(command, "r");
    if (fp == NULL){
        perror("popen");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fp) != NULL){
        strcat(working_directory_contents, line);
    }

    pclose(fp);
    //TODO: Cierra el bufer y manejo de errores 

    return strdup(working_directory_contents);
}
