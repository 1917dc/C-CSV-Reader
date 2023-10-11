#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *nome;
    int idEq;
    float vendas;
}gerente;

typedef struct{
    int id;
    int idEq;
    int idVenda;
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
    gerente *equipe = malloc(sizeof(gerente));
    char comma[] = ",";

//para aramzenar a quantidade de pessoas e separar os dados
    int i = 0;
    int s = 0;
    while((fgets(linha, sizeof(linha), stdin)) != NULL){
        //sorting de dados

        dados = realloc(dados, sizeof(pessoa) * (i + 1));
        char *token = strtok(linha, comma);
        if(token != NULL){
            dados[i].id = atoi(token);
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
            dados[i].idEq = atoi(token);
            if(strcmp(dados[i].cargo, "gerente") == 0){
                equipe = realloc(equipe, sizeof(gerente) + (s + 1));
                equipe[s].nome = realloc(equipe[s].nome,sizeof(gerente) * (s + 1));
                strcpy(equipe[s].nome, dados[i].nome);
                dados[i].idEq = equipe[s].idEq;
                s++;
            }
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].idVenda = atoi(token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].valVenda = atof(token);
        }
        i++;
    }

    //variaveis para separar cada equipe

    double totalVendas = 0;
    int numEq = 0;
    int equipesUnicas[100];

    for(int j = 0; j < i; j++){
        totalVendas+=dados[j].valVenda;
    }
    for(int j = 0; j < i; j++){
        int found = 0;
        for(int k = 0; k < numEq; k++){
            if(equipesUnicas[k] == dados[j].idEq){
                found = 1;
                break;
            }
        }

        if(!found){
            equipesUnicas[numEq] = dados[j].idEq;
            numEq++;
        }
    }
    for(int j = 0; j < numEq; j++){
        printf("%s, %i",equipe[j].nome, equipe[j].idEq);
    }    




    return 0;
}