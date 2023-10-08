#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *buffer;
    int t = 0;

    FILE *arquivo = fopen(argv[1], "r");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    buffer = malloc(sizeof(char));

    while(!feof(arquivo)){
        *(buffer + t) = fgetc(arquivo);
        t++;
        buffer = realloc(buffer, sizeof(char) * (t + 1));
    }
    buffer[t - 1] = '\0';
    printf("%s", buffer);
    
    return 0;
}

