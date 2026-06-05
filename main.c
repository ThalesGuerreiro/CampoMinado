#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

typedef struct Celula{
    bool tem_bomba;
    bool foi_revelada;
    bool tem_bandeira;
    int bombas_perto;
}cel;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int linha = 10, coluna = 10,
        conta_bombas = 0, x = 0, y = 0;
    cel campo[linha][coluna];

    //limpa o campo
    for(int i=0; i<linha; i++){
        for(int j=0; j<coluna; j++){
            campo[i][j].tem_bomba = false;
            campo[i][j].foi_revelada = false;
            campo[i][j].tem_bandeira = false;
            campo[i][j].bombas_perto = 0;
        }
    }

    //coloca bombas
    while(conta_bombas<linha*coluna*0.2){
        x = rand()%linha;
        y = rand()%coluna;
        campo[x][y].tem_bomba = true;
        conta_bombas++;
    }

    int bombas = 0;
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            bombas = 0;
            //Verifica bombas ao redor da celula [i][j]
            for(int di = -1; di <= 1; di++){
                for(int dj = -1; dj <= 1; dj++){
                    if(di == 0 && dj == 0){
                        continue;
                    }
                    int linha_vizinha = i + di,
                        coluna_vizinha = j + dj;
                    if((linha_vizinha > -1) && (coluna_vizinha > -1) && (linha_vizinha < linha) && (coluna_vizinha < coluna)){
                        if(campo[linha_vizinha][coluna_vizinha].tem_bomba){
                            bombas++;
                        }
                    }
                }
            }
            campo[i][j].bombas_perto = bombas;
        }
    }

    //printa o campo
    for(int i = 0; i < linha; i++){
        for(int j = 0; j < coluna; j++){
            if(campo[i][j].tem_bandeira){
                printf("⚑ ");
            }
            else if(!campo[i][j].foi_revelada){
                printf(". ");
            }
            else if((!campo[i][j].tem_bomba) && (campo[i][j].bombas_perto == 0)){
                printf("  ");
            }
            else if(!campo[i][j].tem_bomba){
                printf("%i ", campo[i][j].bombas_perto);
            }
            else if(campo[i][j].tem_bomba){
                printf("X ");
            }
        }
        printf("\n");
    }

    return 0;
}