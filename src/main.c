#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "jogo.h"
#include "terminal.h"

int main(){
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));

    int linha, coluna;
    while(true){
        int tamanho = menu();
        switch(tamanho){
            case 0:
                linha = 15;
                coluna = 15;
                break;
            
            case 1:
                linha = 25;
                coluna = 40;
                break;

            case 2:
                linha = 40;
                coluna = 70;
                break;
            
            case 3:
                return 0;
        }

        system("cls");

        Tabuleiro campo = criar_tabuleiro(linha, coluna);
        if (campo.celulas == NULL) {
            return 1;
        }

        coloca_bombas(&campo);
        calcula_bombas_vizinhas(&campo);

        int x = 0, y = 0, comando = 0;
        while(campo.estado == JOGANDO){
            imprime_campo(&campo, x, y);

            comando = processa_comando(&campo, &x, &y);
            if(comando == 13){
                revelar_celula(&campo, x, y);
            }
            else if(comando == 32){
                marca_bandeira(&campo, x, y);
            }

            system("cls");
            if(campo.n_reveladas == campo.linhas*campo.colunas - campo.total_bombas){
                campo.estado = VITORIA;
            }
        }

        revela_campo(&campo);
        imprime_campo(&campo, -1, -1);
        _getch();

        if(campo.estado == VITORIA){
            imprime_vitoria();
        }
        else{
            imprime_derrota();
        }
    }

    return 0;
}