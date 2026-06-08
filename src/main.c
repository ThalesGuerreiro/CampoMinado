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

    int x = 0, y = 0, comando = 0;
    while(campo.acabou == false){
        imprime_campo(&campo, x, y);

        comando = processa_comando(&campo, &x, &y);
        if(comando == 13){
            revelar_celula(&campo, x, y);
        }
        else if(comando == 32){
            if(campo.celulas[indice(&campo, x, y)].tem_bandeira == false){
                campo.celulas[indice(&campo, x, y)].tem_bandeira = true;
            }
            else if(campo.celulas[indice(&campo, x, y)].tem_bandeira == true){
                campo.celulas[indice(&campo, x, y)].tem_bandeira = false;
            }
        }

        system("cls");
        if(campo.n_reveladas == campo.linhas*campo.colunas - campo.total_bombas){
            campo.acabou = true;
        }
    }

    return 0;
}