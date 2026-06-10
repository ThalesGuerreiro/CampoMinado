#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "jogo.h"

Tabuleiro criar_tabuleiro(int linhas, int colunas){
    Tabuleiro campo;
    campo.linhas = linhas;
    campo.colunas = colunas;
    campo.total_bombas = linhas*colunas*0.1;
    campo.celulas = NULL;
    campo.n_reveladas = 0;
    campo.estado = JOGANDO;

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

void coloca_bombas(Tabuleiro *campo, int x, int y){
    int conta_bombas = 0, l, c, dx, dy, ind;
    while(conta_bombas<campo->total_bombas){
        l = rand()%campo->linhas;
        c = rand()%campo->colunas;
        ind = indice(campo, l, c);
        dx = abs(x - l);
        dy = abs(y - c);
        if(dx <= 1 && dy <= 1){
            continue;
        }
        if(campo->celulas[ind].tem_bomba){
            continue;
        }
        campo->celulas[ind].tem_bomba = true;
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

void revelar_celula(Tabuleiro *campo, int linha, int coluna){
    if(linha < 0 || coluna < 0 || linha >= campo->linhas || coluna >= campo->colunas){
        return;
    }

    int ind = indice(campo, linha, coluna);

    if((campo->celulas[ind].tem_bandeira == false) && (campo->celulas[ind].foi_revelada == false)){

        campo->celulas[ind].foi_revelada = true;
        campo->n_reveladas++;

        if(campo->celulas[ind].tem_bomba == true){
            campo->estado = DERROTA;
            return;
        }

        if(campo->celulas[ind].bombas_perto == 0){
            for(int di = -1; di <= 1; di++){
                for(int dj = -1; dj <= 1; dj++){
                    if(di == 0 && dj == 0){
                        continue;
                    }
                    int linha_vizinha = linha + di,
                        coluna_vizinha = coluna + dj;
                    if((linha_vizinha > -1) && (coluna_vizinha > -1) && (linha_vizinha < campo->linhas) && (coluna_vizinha < campo->colunas)){
                        revelar_celula(campo, linha_vizinha, coluna_vizinha);
                    }
                }
            }
        }
    }
}

void marca_bandeira(Tabuleiro *campo, int linha, int coluna){
    campo->celulas[indice(campo, linha, coluna)].tem_bandeira =
        !campo->celulas[indice(campo, linha, coluna)].tem_bandeira;
}