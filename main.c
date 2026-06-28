#include <string.h>
#include "indice-invertido.h"
//#include "Historia.txt"

int main(){

    char lista[TEXTO_LEN][TAM_PAL];
    Vocab tokens[TEXTO_LEN];

    preencherVetor(lista);
    preencherStruct(tokens);

    int indice;
    char busca[TAM_PAL];
    int opcao;

    do{
        printf("======== MENU ========\n\n");
        printf("1 - Abrir arquivo\n");
        printf("2 - Mostrar vocabulario\n");
        printf("3 - Buscar palavra\n");
        printf("0 - Sair\n");
        opcao = lerOpcao();
        limparTela();

        switch(opcao){
            case 1:
                carregarArquivo(lista, NOME_ARQUIVO);
                criarVocabulario(lista, tokens);
                insertionSort(tokens);
                pausaTela();
                break;
            case 2:
                mostrarVocabulario(tokens);
                pausaTela();
                break;
            case 3:
                menuBusca(lista, tokens);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida");
                pausaTela();

        }
        limparTela();

    }while(opcao != 0);

    return 0;
}
