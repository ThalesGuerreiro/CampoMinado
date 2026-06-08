#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "terminal.h"
#include "jogo.h"

int menu(){
    int opcao = 0;
    while(1){
        system("cls");
        printf("*************************\n");
        printf("*                       *\n");
        printf("*       Campo           *\n");
        printf("*          Minado       *\n");
        printf("*                       *\n");

        switch(opcao){
            case 0:
                printf("*      \x1b[33m>  FACIL\x1b[0m         *\n");
                printf("*         MÉDIO         *\n");
                printf("*        DIFÍCIL        *\n");
                printf("*                       *\n");
                printf("*         SAIR          *\n");
                break;
        
            case 1:
                printf("*         FACIL         *\n");
                printf("*      \x1b[33m>  MÉDIO\x1b[0m         *\n");
                printf("*        DIFÍCIL        *\n");
                printf("*                       *\n");
                printf("*         SAIR          *\n");
                break;
        
            case 2:
                printf("*         FACIL         *\n");
                printf("*         MÉDIO         *\n");
                printf("*      \x1b[33m> DIFÍCIL\x1b[0m        *\n");
                printf("*                       *\n");
                printf("*         SAIR          *\n");
                break;

            case 3:
                printf("*         FACIL         *\n");
                printf("*         MÉDIO         *\n");
                printf("*        DIFÍCIL        *\n");
                printf("*                       *\n");
                printf("*      \x1b[31m>  SAIR\x1b[0m          *\n");
                break;
            
        }
        
        printf("*                       *\n");
        printf("*************************\n");
        int tecla = _getch();
        //Navegando com as setas
        if(tecla == 224){
            tecla = _getch();
            switch(tecla){
                case 72:
                    if(opcao > 0){
                        opcao--;
                    }
                    break;
                    
                case 80:
                    if(opcao < 3){
                        opcao++;
                    }
                    break;
            }
        }
        //selecionou com ENTER
        else if(tecla == 13){
            return opcao;
        }
    }
}

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