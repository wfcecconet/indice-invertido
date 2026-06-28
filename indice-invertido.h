#pragma once
#include <stdio.h>

#define NOME_ARQUIVO        "BadRomance.txt"
#define TEXTO_LEN           1000
#define TAM_PAL             50

typedef struct {
    char token[TAM_PAL];
    int pos[80];
}Vocab;

void limparTela();
void pausaTela();

void preencherVetor(char vetor[][TAM_PAL]);
void preencherStruct(Vocab vetor[]);

void carregarArquivo(char vetor[][TAM_PAL], const char *arquivo);
void criarVocabulario(char vetor[][TAM_PAL], Vocab tokens[]);

void insertionSort(Vocab lista[]);

void mostrarVocabulario(Vocab tokens[]);

int lerOpcao();
void menuBusca(char vetor[][TAM_PAL], Vocab tokens[]);
int buscaSequencial(Vocab lista[], char palavra[]);
int buscaBinaria(Vocab tokens[], char palavra[], int tamanho);

void imprimirContexto(char lista[][TAM_PAL], int posicao);
int contarOcorrencias(Vocab tokens[], int indice);
int tamanhoVetor(Vocab tokens[]);
void exibirOcorrencias(char lista[][TAM_PAL], Vocab tokens[], int indice);
