#pragma once
#include <stdio.h>

#define NOME_ARQUIVO        "Historia.txt"
#define TEXTO_LEN           1000
#define MAX_PAL             50


void carregarArquivo(char vetor[][MAX_PAL], const char *arquivo);
