#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int idEq;
    int id;
    double vendasEq;
    char *nome;
}gerente;

typedef struct{
    int id;
    int idEq;
    int idVenda;
    char *nome;
    char *cargo;
    double valVenda;
}pessoa;

int compare(const void *, const void * );

int main(){
    char linha[1024];
    char *lido = malloc(sizeof(char));
    int t = 0;

//alocar memoria para depois realocar
    pessoa *dados = malloc(sizeof(pessoa));
    gerente *equipe = malloc(sizeof(gerente)*100);
    char comma[] = ",";

//para aramzenar a quantidade de pessoas e separar os dados
    int i = 0;
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

//calcular total de vendas
    for(int j = 0; j < i; j++){
        totalVendas+=dados[j].valVenda;
    }

    // identifica o numero de equipes e armazena caso tenha uma equipe nova
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
        for(int k = 0; k < i; k++){
            if((strcmp(dados[k].cargo, "gerente") == 0) && (j+1) == dados[k].idEq){
                equipe[j].nome = realloc(equipe[j].nome, sizeof(strlen(dados[k].nome)));
                strcpy(equipe[j].nome, dados[k].nome);
                equipe[j].idEq = dados[k].idEq;
                equipe[j].id = dados[k].id;
            }
        }
    }

    for(int j = 0; j < i; j++){
        for(int k = 0; k < numEq; k++){
            if(dados[j].idEq == equipe[k].idEq){
                equipe[k].vendasEq += dados[j].valVenda;
            }
        }
    }

    printf("Relatório de vendas: \n");
    printf("Total de vendas da empresa: %f\n", totalVendas);
    printf("Total de vendas por equipe: \n");
//definindo maiores vendas
    double maiorVenda = 0;
    int eqVencedora;
    for(int j = 0; j < numEq; j++){
        printf("Equipe %i (Gerente: %s) - Vendas R$ %.2f - Comissão: R$ %.2f\n", equipesUnicas[j], equipe[j].nome, equipe[j].vendasEq, (equipe[j].vendasEq * 0.05));
        if(equipe[j].vendasEq > maiorVenda){
            maiorVenda = equipe[j].vendasEq;
            eqVencedora = equipesUnicas[j];
        }
    }
    for(int j = 0; j < numEq; j++){
        if(eqVencedora == equipe[j].idEq){
            printf("Gerente da equipe vencedora: %s\n", equipe[j].nome);
        }
    }
    double maiorVendaVend = 0;
    char *melhorVend = malloc(sizeof(char));
    for(int j = 0; j < i; j++){
        if(dados[j].valVenda > maiorVendaVend){
            maiorVendaVend = dados[j].valVenda;
            melhorVend = realloc(melhorVend, sizeof(strlen(dados[j].nome)));
            strcpy(melhorVend, dados[j].nome);
        }
    }
    printf("Melhor vendedor: %s\n", melhorVend);

    //variavel temporária
    double temp;

    printf("Nome\t\t\tCargo\t\tEquipe\t\tTotal de Vendas\t\tComissão\n");
    qsort(dados, i, sizeof(pessoa), compare);
    for(int j = 0; j < i; j++){
        double comissao;
        int cont = 0;

        if(strcmp(dados[j].cargo, "junior") == 0){
            comissao = (0.01*dados[j].valVenda);
        }
        if(strcmp(dados[j].cargo, "pleno") == 0){
            comissao = (0.02*dados[j].valVenda);
        }
        if(strcmp(dados[j].cargo, "senior") == 0){
            comissao = (0.03*dados[j].valVenda);
        }

        printf("%s\t\t\t%s\t\t%i\t%.2f\t\t%.2f", dados[j].nome,dados[j].cargo,dados[j].idEq,dados[j].valVenda, comissao);
        printf("\n");

    }

    return 0;
}

int compare(const void *aptr, const void *bptr){
    float a = ((pessoa*)aptr)->valVenda;
    float b = ((pessoa*)bptr)->valVenda;
    return (a < b) - (a > b);
}