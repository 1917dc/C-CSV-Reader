#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *id;
    char *idEq;
    char *idVenda;
    char *nome;
    char *cargo;
    double valVenda;
}pessoa;

int main(){
    char linha[1024];
    char *lido = malloc(sizeof(char));
    int t = 0;

//alocar memoria para depois realocar
    pessoa *dados = malloc(sizeof(pessoa));
    char comma[] = ",";

//para aramzenar a quantidade de pessoas e separar os dados
    int i = 0;
    while((fgets(linha, sizeof(linha), stdin)) != NULL){
        //sorting de dados

        dados = realloc(dados, sizeof(pessoa) * (i + 1));
        char *token = strtok(linha, comma);
        if(token != NULL){
            dados[i].id = realloc(dados[i].id, sizeof(token));
            strcpy(dados[i].id, token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].nome = realloc(dados[i].nome, sizeof(token));
            strcpy(dados[i].nome, token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].cargo = realloc(dados[i].cargo, sizeof(token));
            strcpy(dados[i].cargo, token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].idEq = realloc(dados[i].idEq, sizeof(token));
            strcpy(dados[i].idEq, token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].idVenda = realloc(dados[i].idVenda, sizeof(token));
            strcpy(dados[i].idVenda, token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].valVenda = atof(token);
        }
        i++;
    }
    return 0;
}