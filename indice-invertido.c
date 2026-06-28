#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "indice-invertido.h"

void limparTela(){

    system("cls");
}

void pausaTela(){

    while(getchar() != '\n');
    printf("Aperte ENTER para retornar...\n");
    getchar();
}

void preencherVetor(char vetor[][TAM_PAL]){
    int i;
    for(i = 0; i < TEXTO_LEN; i++){
        strcpy(vetor[i], "-1");
    }
}
void preencherStruct(Vocab vetor[]){
    for(int i = 0; i < TEXTO_LEN; i++){
        strcpy(vetor[i].token, "-1");
        for(int j = 0; j < 80; j++){
            vetor[i].pos[j] = -1;
        }
    }
}

void carregarArquivo(char vetor[][TAM_PAL], const char *arquivo){

    FILE *pArquivo = fopen(arquivo, "r");

    if(pArquivo==NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char palavra[TAM_PAL];
    int pos = 0;
    int i = 0;
    int c;

    while((c = fgetc(pArquivo)) != EOF){
        if(isalnum(c)){
            palavra[pos++] = tolower(c);
        }
        else if(pos>0){
            palavra[pos] = '\0';
            strcpy(vetor[i], palavra);
            i++;
            pos = 0;
        }
    }
    printf("Arquivo carregado...\n\n");
    fclose(pArquivo);
}

void criarVocabulario(char vetor[][TAM_PAL], Vocab tokens[]){

    int n = 0;
    int i = 0;

    while(strcmp(vetor[i], "-1") != 0){

        int achou = -1;

        for(int j = 0; j < n; j++){
            if(strcmp(tokens[j].token, vetor[i]) == 0){
                achou = j;
                break;
            }
        }

        if(achou != -1){
            int k = 0;
            while(tokens[achou].pos[k] != -1){
                k++;
            }
            tokens[achou].pos[k] = i;
        }
        else {
            strcpy(tokens[n].token, vetor[i]);
            tokens[n].pos[0] = i;
            n++;
        }

        i++;
    }
    printf("Vocabulario criado...\n\n");
}

void insertionSort(Vocab lista[]){

    int i, j;
    Vocab chave;

    for(i=1; strcmp(lista[i].token, "-1") !=0 ; i++){
        chave = lista[i];
        j = i-1;

        while(j>=0 && strcmp(lista[j].token, chave.token) > 0){
            lista[j+1] = lista [j];
            j--;
        }
        lista[j+1] = chave;
    }
    printf("O vocabulario esta ordenado...\n\n");
}

void mostrarVocabulario(Vocab tokens[]){

    if(strcmp(tokens[0].token, "-1") == 0){
        printf("O vocabulario esta vazio\n\n");
        return;
    }

    for(int i = 0; strcmp(tokens[i].token, "-1") != 0; i++){
        printf("%s......", tokens[i].token);
        for(int j = 0; tokens[i].pos[j] != -1; j++){
            printf("[%d] ", tokens[i].pos[j]);
        }
        printf("\n\n");
    }

}

int lerOpcao(){
    int opcao;
    if(scanf("%d", &opcao) != 1){
        while(getchar() != '\n');
        return -999;
    }
    return opcao;
}

void menuBusca(char vetor[][TAM_PAL], Vocab tokens[]){
    if(strcmp(tokens[0].token, "-1") == 0){
        printf("O vocabulario esta vazio\n\n");
        pausaTela();
        return;
    }

    int opcao;
    char busca[TAM_PAL];
    do{
        printf("======== BUSCAR ========\n\n");
        printf("1 - Busca sequencial\n");
        printf("2 - Busca binaria\n");
        printf("0 - Voltar\n");
        opcao = lerOpcao();
        limparTela();

        switch(opcao){
            case 1:
                printf("Qual palavra deseja buscar?\n");
                scanf("%49s", busca);
                limparTela();
                exibirOcorrencias(vetor, tokens, (buscaSequencial(tokens, busca)));
                pausaTela();
                break;
            case 2:
                printf("Qual palavra deseja buscar?\n");
                scanf("%49s", busca);
                limparTela();
                exibirOcorrencias(vetor, tokens, (buscaBinaria(tokens, busca, (tamanhoVetor(tokens)))));
                pausaTela();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida");
                pausaTela();
        }
        limparTela();
    }while(opcao != 0);

}


int buscaSequencial(Vocab lista[], char palavra[]){

    int i, achou = 0;

    for(int k = 0; palavra[k] != '\0'; k++){
        palavra[k] = tolower(palavra[k]);
    }

    for(i = 0; (strcmp(lista[i].token, "-1") != 0); i++){
        if(strcmp(lista[i].token, palavra) == 0){
            achou = 1;
            break;
        }
    }
    if(achou){
        return i;
    }
    else{
        return -1;
    }
}

int buscaBinaria(Vocab tokens[], char palavra[], int tamanho){

    int esq = 0;
    int dir = tamanho - 1;
    int i;
    int encontrou = 0;

    for(int k = 0; palavra[k] != '\0'; k++){
        palavra[k] = tolower(palavra[k]);
    }

    while(esq <= dir && !encontrou){
        i = esq + (dir - esq) / 2;

        if(strcmp(tokens[i].token, palavra) == 0)
            encontrou = 1;
        else if(strcmp(tokens[i].token, palavra) > 0)
            dir = i - 1;
        else{
            esq = i + 1;
        };
    }

    if(encontrou){
        return i;
    }
    else
        return -1;
}

void imprimirContexto(char lista[][TAM_PAL], int posicao){

    if(posicao == -1){
        printf("Palavra nao localizada");
        return;
    }
    int inicio = posicao - 3;
    int fim = posicao + 3;

    if(inicio < 0){
        inicio = 0;
    }

    for(int k = inicio; k <= fim; k++){
        if(strcmp(lista[k], "-1") == 0){
            break;
        }
        printf("%s ", lista[k]);
    }
    printf("\n");
}
int contarOcorrencias(Vocab tokens[], int indice){
    int i;
    for(i = 0; tokens[indice].pos[i] != -1; i++);
    return i;
}

int tamanhoVetor(Vocab tokens[]){
    int i;
    for(i = 0; strcmp(tokens[i].token, "-1") != 0; i++);
    return i;

}

void exibirOcorrencias(char lista[][TAM_PAL], Vocab tokens[], int indice){

    if(indice == -1){
        printf("A palavra digitada nao esta no vocabulario\n");
        return;
    }

    int k = 0;
    int continuar = 1;
    int ocorr = contarOcorrencias(tokens, indice);

    while(tokens[indice].pos[k] != -1 && continuar){
        printf("Foram encontradas %d ocorrencias para\n<%s>\n\n", ocorr, tokens[indice].token);
        printf("Ocorrencia %d de %d\n\n", k + 1, ocorr);
        imprimirContexto(lista, tokens[indice].pos[k]);
        printf("\n");
        k++;

        if(tokens[indice].pos[k] != -1){
            printf("1 - PROXIMO\n");
            printf("0 - VOLTAR\n\n");
            int entrada;
            if(scanf("%d", &entrada) != 1){
                while(getchar() != '\n');
                continuar = 0;
            }
            else{
                continuar = entrada;
            }
        }
        else{
            printf("Essa foi a ultima ocorrencia\n\n");
        }
        if(tokens[indice].pos[k] != -1 && continuar){
            limparTela();
        }
    }
}
