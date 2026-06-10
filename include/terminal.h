#ifndef TERMINAL_H
#define TERMINAL_H

#include "jogo.h"

void imprime_campo(const Tabuleiro *campo, int x, int y);

int menu();

int processa_comando(const Tabuleiro *campo, int *x, int *y);

void revela_campo(const Tabuleiro *campo);

void imprime_derrota();

void imprime_vitoria();

#endif