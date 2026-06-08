#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "jogo.h"
#include "terminal.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));

    int linha = 10, coluna = 10;
    menu();
    system("cls");

    Tabuleiro campo = criar_tabuleiro(linha, coluna);
    if (campo.celulas == NULL) {
        return 1;
    }

    coloca_bombas(&campo);
    calcula_bombas_vizinhas(&campo);

    while(campo.acabou == false){
        imprime_campo(&campo);
        int x, y;
        scanf("%d %d", &x, &y);
        revelar_celula(&campo, x, y);
        system("cls");
        if(campo.n_reveladas == campo.linhas*campo.colunas - campo.total_bombas){
            campo.acabou = true;
        }
    }

    return 0;
}