#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void imprimirNumero(double numero, char numeroFormatado[]);

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
    double maiorVenda;
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

    char totalCorrigido[1024];
    imprimirNumero(totalVendas, totalCorrigido);

    printf("Relatório de vendas: \n");
    printf("Total de vendas da empresa: R$%s\n", totalCorrigido);
    printf("Total de vendas por equipe: \n");
//definindo maiores vendas
    double maiorVenda = 0;
    int eqVencedora;
    for(int j = 0; j < numEq; j++){
        char vendasEqCorrigido[1024];
        char comissaoEqCorrigido[1024];

        imprimirNumero((0,05 * equipe[j].vendasEq), comissaoEqCorrigido);
        imprimirNumero(equipe[j].vendasEq, vendasEqCorrigido);

        printf("Equipe %i (Gerente: %s) - Vendas R$ %s - Comissão: R$ %s\n", equipesUnicas[j], equipe[j].nome, vendasEqCorrigido, comissaoEqCorrigido);
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

    printf("Nome\t\t\t\t\tCargo\t\t\t\t\tEquipe\t\t\t\t\tTotal de Vendas\t\t\t\tMaior Venda\t\t\t\t\tComissão\n");
    qsort(dados, i, sizeof(pessoa), compare);
    for(int j = 0; j < i; j++){
        double comissao;
        int maiorNome = 0;
        char numeroCorrigido[1024];
        char comissaoCorrigida[1024];
        char maiorVendaUnCorrigido[1024];

        float maiorVendaUn = -1;
        if(dados[j].valVenda > maiorVendaUn){
            maiorVendaUn = dados[j].valVenda;
        }
        imprimirNumero(maiorVendaUn, maiorVendaUnCorrigido);

        imprimirNumero(dados[j].valVenda, numeroCorrigido);

        if(strcmp(dados[j].cargo, "gerente") == 0){
            break;
        }

        if(strcmp(dados[j].cargo, "junior") == 0){
            comissao = (0.01*dados[j].valVenda);
        }
        if(strcmp(dados[j].cargo, "pleno") == 0){
            comissao = (0.02*dados[j].valVenda);
        }
        if(strcmp(dados[j].cargo, "senior") == 0){
            comissao = (0.03*dados[j].valVenda);
        }

        while(strlen(dados[j].nome) < 24){
            strcat(dados[j].nome, " ");
        }
        while(strlen(dados[j].cargo) < 24){
            strcat(dados[j].cargo, " ");
        }

        imprimirNumero(comissao, comissaoCorrigida);

        printf("%s%s%-24.03iR$%-26sR$%-26sR$%-24s", dados[j].nome,dados[j].cargo,dados[j].idEq,numeroCorrigido, maiorVendaUnCorrigido,comissaoCorrigida);
        printf("\n");
    }

    return 0;
}

int compare(const void *aptr, const void *bptr){
    float a = ((pessoa*)aptr)->valVenda;
    float b = ((pessoa*)bptr)->valVenda;
    return (a < b) - (a > b);
}

void imprimirNumero(double numero, char numeroFormatado[]) {
    sprintf(numeroFormatado, "%.2lf", numero);
    char novoNumero[100] = "";
    

    int i = 0, novoIndex = 0, espacados = 0, posicaoReal = 0;
    
    while (numeroFormatado[i] != '\0') {
        if (numeroFormatado[i] == '.') {
            numeroFormatado[i] = ',';
            break;
        }
        i++;
    }

    while (numeroFormatado[novoIndex] != ',') {
        novoIndex++;
    }
    
    switch (novoIndex%3){
    case 0:
        posicaoReal = 0;
        break;
    
    case 1:
        posicaoReal = 2;
        break;

    case 2:
        posicaoReal = 1;
        break;
    }

    novoIndex = 0;
    while (numeroFormatado[novoIndex] != '\0') {
        if(posicaoReal != 0 && posicaoReal%3 == 0 && novoIndex < i){
            novoNumero[strlen(novoNumero)] = '.';
            posicaoReal = 0;
        }
        novoNumero[strlen(novoNumero)] = numeroFormatado[novoIndex];
        posicaoReal++;
        novoIndex++;
    }

    strcpy(numeroFormatado, novoNumero);

}
