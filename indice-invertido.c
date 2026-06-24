#include <stdio.h>
#include <ctype.h>

#include "indice-invertido.h"

void carregarArquivo(char vetor[][MAX_PAL], const char *arquivo){

    FILE *pArquivo = fopen(arquivo, "r");

    if(pArquivo==NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char palavra[MAX_PAL];
    int i = 0, letras = 0;
    int ch;

    while((ch = fgetc(pArquivo)) != EOF && i < TEXTO_LEN){
        if(isalpha(ch)){
            if (letras < MAX_PAL - 1){
                vetor[i][letras++] = ch;
            }
        }
        else if(letras > 0){
            vetor[i][letras] = '\0';
            i++;
            letras = 0;
        }
        if(letras > 0 && i < TEXTO_LEN){
            vetor[i][letras] = '\0';
        }
    }



    /*while(i< TEXTO_LEN && fscanf(pArquivo, "%49[a-zA-Z]", palavra) == 1){
        strcpy(vetor[i], palavra);
        i++;

        char proximo = fgetc(pArquivo);
        while(proximo != EOF && !(proximo >= 'a' && proximo <= 'z') && !(proximo >= 'A' && proximo <= 'Z')){
            proximo = fgetc(pArquivo);
        }
        if (proximo != EOF) {
            ungetc(proximo, pArquivo);
        }
    }*/
    fclose(pArquivo);
}
