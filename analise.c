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
    float vendas;
    float maiorVenda;
    int id;
    int equipe;
    char *cargo;
    char *nome;
    float comissao;
}vendedor;

typedef struct{
    int id;
    int idEq;
    int idVenda;
    char *nome;
    char *cargo;
    double valVenda;
    double maiorVenda;
    int vendasUn;
    double vendaTotal;
}pessoa;

int compare(const void *, const void * );
int comparaGerente(const void *, const void * );


int main(){
    char linha[1024];
    char *lido = malloc(sizeof(char));
    int t = 0;

//alocar memoria para depois realocar
    pessoa *dados = malloc(sizeof(pessoa));
    gerente *equipe = malloc(sizeof(gerente)*100);
    vendedor *unico = malloc(sizeof(vendedor));
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
            dados[i].nome = malloc(sizeof(token) + 1);
            strcpy(dados[i].nome, token);
        }
        token = strtok(NULL, comma);
        if(token != NULL){
            dados[i].cargo = malloc(sizeof(token) + 1);
            strcpy(dados[i].cargo, token);
            if(strcmp(dados[i].cargo, "gerente") == 0){
                dados[i].valVenda = 0;
                dados[i].maiorVenda = 0;
            }
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

    float totalVendas = 0;
    int numEq = 0;
    int equipesUnicas[100];

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
                equipe[j].nome = malloc(sizeof(strlen(dados[k].nome)) + 1);
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


//vendas unicas
    int indiceVendedor = 0;
    for(int j = 0; j < i; j++){
        dados[j].vendasUn = 0;
        int flag = -1;

        for(int k = 0; k < indiceVendedor; k++){
            if(dados[j].id == unico[k].id || strcmp(dados[j].cargo, "gerente") == 0){
                flag = 1;
                unico[k].vendas += dados[j].valVenda;
                if(unico[k].maiorVenda < dados[j].valVenda){
                    unico[k].maiorVenda = dados[j].valVenda;
                }
                if(strcmp(unico[k].cargo, "junior") == 0){
                    unico[k].comissao = (unico[k].vendas * 0.01);
                }
                if(strcmp(unico[k].cargo, "pleno") == 0){
                    unico[k].comissao = (unico[k].vendas * 0.02);
                }
                if(strcmp(unico[k].cargo, "senior") == 0){
                    unico[k].comissao = (unico[k].vendas * 0.03);
                }
            } 
        } 

        if(flag == -1){
            unico = realloc(unico,sizeof(vendedor) * (indiceVendedor + 1));
            unico[indiceVendedor].nome = realloc(unico[indiceVendedor].nome, sizeof(strlen(dados[j].nome) +1));
            strcpy(unico[indiceVendedor].nome, dados[j].nome);
            unico[indiceVendedor].vendas = dados[j].valVenda;
            unico[indiceVendedor].id = dados[j].id;
            unico[indiceVendedor].cargo = realloc(unico[indiceVendedor].cargo, sizeof(strlen(dados[j].cargo) +1));
            strcpy(unico[indiceVendedor].cargo, dados[j].cargo);
            unico[indiceVendedor].equipe = dados[j].idEq;
            unico[indiceVendedor].maiorVenda = dados[j].valVenda;
            if(strcmp(unico[indiceVendedor].cargo, "junior") == 0){
                unico[indiceVendedor].comissao = (dados[j].valVenda * 0.01);
            }
            if(strcmp(unico[indiceVendedor].cargo, "pleno") == 0){
                unico[indiceVendedor].comissao = (dados[j].valVenda * 0.02);
            }
            if(strcmp(unico[indiceVendedor].cargo, "senior") == 0){
                unico[indiceVendedor].comissao = (dados[j].valVenda * 0.03);
            }
            indiceVendedor++;
        }
    }



/*
        //calcular total de vendas
    for(int j = 0; j < i; j++){
        totalVendas+=dados[j].valVenda;
    }
*/   
    for(int j = 0; j < indiceVendedor; j++){
        totalVendas += unico[j].vendas;
    }

    char totalCorrigido[1024];
    imprimirNumero(totalVendas, totalCorrigido);

    printf("Relatório de vendas: \n");
    printf("Total de vendas da empresa: R$%s\n", totalCorrigido);
    printf("Total de vendas por equipe: \n");
//definindo maiores vendas
    double maiorVenda = -1, vendasTotais[100];
    int eqVencedora, eqRep[numEq];
    for(int j = 0; j < numEq; j++){
        vendasTotais[j] = equipe[j].vendasEq;
        eqRep[equipe[j].idEq] = -1;
    }
    char gerenteVencedor[100];
    qsort(vendasTotais, numEq, sizeof(double), comparaGerente);
    for(int j = 0; j < numEq; j++){
        for(int k = 0; k < numEq; k++){
            if(vendasTotais[j] == equipe[k].vendasEq && eqRep[equipe[k].idEq] == -1){
                eqRep[equipe[k].idEq] = 0;
                char vendasEqCorrigido[1024];
                char comissaoEqCorrigido[1024];
                imprimirNumero((0,05 * vendasTotais[j]), comissaoEqCorrigido);
                imprimirNumero(vendasTotais[j], vendasEqCorrigido);
                if(j == 0){
                    strcpy(gerenteVencedor, equipe[k].nome);
                }
                printf("Equipe %i (Gerente: %s) - Vendas R$ %s - Comissão: R$ %s\n", equipe[k].idEq, equipe[k].nome, vendasEqCorrigido, comissaoEqCorrigido);
            }
        }
    }
    
    printf("Gerente da equipe vencedora: %s\n", gerenteVencedor);

    double maiorVendaVend = 0;
    char *melhorVend = malloc(sizeof(char));
    for(int j = 0; j < i; j++){
        if(dados[j].vendaTotal > maiorVendaVend){
            maiorVendaVend = dados[j].vendaTotal;
            melhorVend = realloc(melhorVend, sizeof(strlen(dados[j].nome)));
            strcpy(melhorVend, dados[j].nome);
        }
    }

    printf("Melhor vendedor: %s\n", melhorVend);

    printf("Nome\t\t\t\t\tCargo\t\t\t\t\tEquipe\t\t\t\t\tTotal de Vendas\t\t\t\tMaior Venda\t\t\t\t\tComissão\n");
    qsort(unico, indiceVendedor, sizeof(vendedor), compare);
    for(int j = 0; j < indiceVendedor; j++){
        double comissao;
        int maiorNome = 0;
        char numeroCorrigido[1024];
        char comissaoCorrigida[1024];
        char maiorVendaUnCorrigido[1024];

        imprimirNumero(unico[j].maiorVenda, maiorVendaUnCorrigido);

        imprimirNumero(unico[j].vendas, numeroCorrigido);


        if(strcmp(unico[j].cargo, "junior") == 0){
            comissao = (0.01*unico[j].vendas);
        }
        if(strcmp(unico[j].cargo, "pleno") == 0){
            comissao = (0.02*unico[j].vendas);
        }
        if(strcmp(unico[j].cargo, "senior") == 0){
            comissao = (0.03*unico[j].vendas);
        }

        while(strlen(unico[j].nome) < 24){
            strcat(unico[j].nome, " ");
        }
        while(strlen(unico[j].cargo) < 24){
            strcat(unico[j].cargo, " ");
        }

        imprimirNumero(unico[j].comissao, comissaoCorrigida);

        printf("%s%s%-24.03iR$%-26sR$%-26sR$%-24s", unico[j].nome,unico[j].cargo,unico[j].equipe,numeroCorrigido, maiorVendaUnCorrigido,comissaoCorrigida);
        printf("\n");
    }

    return 0;
}

int compare(const void *aptr, const void *bptr){
    float a = ((vendedor*)aptr)->vendas;
    float b = ((vendedor*)bptr)->vendas;
    return (a < b) - (a > b);
}
int comparaGerente(const void *aptr, const void *bptr){
    double double_a = *((double *)aptr);
    double double_b = *((double *)bptr);

    if (double_a < double_b)
        return 1;
    else if (double_a > double_b)
        return -1;
    else
        return 0;
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
