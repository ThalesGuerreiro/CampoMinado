#include <stdio.h>
#include "terminal.h"
#include "jogo.h"

void imprime_campo(const Tabuleiro *campo){
    for(int i = 0; i < campo->linhas; i++){
        for(int j = 0; j < campo->colunas; j++){
            Celula atual = campo->celulas[indice(campo, i, j)];

            if(atual.tem_bandeira){
                printf("⚑ ");
            }
            else if(!atual.foi_revelada){
                printf(". ");
            }
            else if((!atual.tem_bomba) && (atual.bombas_perto == 0)){
                printf("  ");
            }
            else if(!atual.tem_bomba){
                printf("%i ", atual.bombas_perto);
            }
            else if(atual.tem_bomba){
                printf("X ");
            }
        }
        printf("\n");
    }
}