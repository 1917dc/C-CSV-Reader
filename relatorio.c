#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *arquivo = fopen(argv[1], "w");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    int caractere;
    while ((caractere = getchar()) != EOF) {
        fputc(caractere, arquivo);
    }

    fclose(arquivo);
    
    return 0;
}