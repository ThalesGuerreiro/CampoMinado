#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "jogo.h"
#include "terminal.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);

    int linha = 10, coluna = 10;

    Tabuleiro campo = criar_tabuleiro(linha, coluna);
    if (campo.celulas == NULL) {
        return 1;
    }

    coloca_bombas(&campo);
    calcula_bombas_vizinhas(&campo);
    imprime_campo(&campo);

    return 0;
}