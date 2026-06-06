#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jogo.h"

Tabuleiro criar_tabuleiro(int linhas, int colunas){
    Tabuleiro campo;
    campo.linhas = linhas;
    campo.colunas = colunas;
    campo.total_bombas = linhas*colunas*0.2;
    campo.celulas = NULL;

    campo.celulas = malloc(linhas*colunas * sizeof(Celula));
    if (campo.celulas == NULL) {
        printf("Erro de memória!\n");
        return campo;
    }

    for(int i = 0; i < linhas*colunas; i++){
        campo.celulas[i].tem_bomba = false;
        campo.celulas[i].foi_revelada = false;
        campo.celulas[i].tem_bandeira = false;
        campo.celulas[i].bombas_perto = 0;
    }

    return campo;
}

int indice(const Tabuleiro *campo, int linha, int coluna){
    return linha * campo->colunas + coluna;
}

void coloca_bombas(Tabuleiro *campo){
    int conta_bombas = 0, x = 0, y = 0;
    while(conta_bombas<campo->total_bombas){
        x = rand()%campo->linhas;
        y = rand()%campo->colunas;
        campo->celulas[indice(campo, x, y)].tem_bomba = true;
        conta_bombas++;
    }
}

void calcula_bombas_vizinhas(Tabuleiro *campo){
    int bombas = 0;
    for(int i = 0; i < campo->linhas; i++){
        for(int j = 0; j < campo->colunas; j++){
            bombas = 0;
            //Verifica bombas ao redor da celula [i][j]
            for(int di = -1; di <= 1; di++){
                for(int dj = -1; dj <= 1; dj++){
                    if(di == 0 && dj == 0){
                        continue;
                    }
                    int linha_vizinha = i + di,
                        coluna_vizinha = j + dj;
                    if((linha_vizinha > -1) && (coluna_vizinha > -1) && (linha_vizinha < campo->linhas) && (coluna_vizinha < campo->colunas)){
                        if(campo->celulas[indice(campo, linha_vizinha, coluna_vizinha)].tem_bomba){
                            bombas++;
                        }
                    }
                }
            }
            campo->celulas[indice(campo, i, j)].bombas_perto = bombas;
        }
    }
}
