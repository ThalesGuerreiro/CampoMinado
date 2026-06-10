#ifndef JOGO_H
#define JOGO_H

typedef struct{
    bool tem_bomba;
    bool foi_revelada;
    bool tem_bandeira;
    int bombas_perto;
}Celula;

typedef enum {
    JOGANDO,
    VITORIA,
    DERROTA
} EstadoJogo;

typedef struct{
    int linhas;
    int colunas;
    int total_bombas;
    Celula *celulas;
    int n_reveladas;
    EstadoJogo estado;
}Tabuleiro;

Tabuleiro criar_tabuleiro(int linhas, int colunas);

int indice(const Tabuleiro *campo, int linha, int coluna);

void coloca_bombas(Tabuleiro *campo);

void calcula_bombas_vizinhas(Tabuleiro *campo);

void revelar_celula(Tabuleiro *campo, int linha, int coluna);

void marca_bandeira(Tabuleiro *campo, int linha, int coluna);

#endif