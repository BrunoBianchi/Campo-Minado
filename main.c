#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Program Made in 2023 By Bruno Bianchi 
*
* Using C
*
*/

char gerarBombas(char **matriz,int tamanho) {
  srand((unsigned)time(NULL));
    for(int i = 0;i<tamanho;i++) {
        int x = rand() % (tamanho - 1);
        int y = rand() % (tamanho - 1);
        if(matriz[x][y] == 'B') {
        while(matriz[x][y] == 'B') {
            x = rand() % (tamanho - 1);
            y = rand() % (tamanho - 1);
            if(matriz[x][y] != 'B') {
                matriz[x][y] = 'B';
                break;
            }
        }
        }else {
            matriz[x][y] = 'B';
        }


    }
}

char **criarMatriz(int tamanho) {
    char **matriz  = (char **) malloc(sizeof(char) * tamanho * tamanho);
    for(int i = 0;i<tamanho;i++) {
        matriz[i] = (char*) malloc(sizeof(char) * tamanho);
    }
      for(int i = 0;i<tamanho;i++) { 
        for(int j = 0; j<tamanho;j++) {
            matriz[i][j] = 'X';
        }
    }
    return matriz;
}

void printMatriz(char**matriz,int tamanhoVetor) {
    for(int i = 0;i<tamanhoVetor;i++) {
        for(int j = 0; j<tamanhoVetor;j++) {
            if(matriz[i][j] == 'O') {
                printf("\033[0;32m%c\033[0m \t",matriz[i][j]);
            }else if(matriz[i][j] == 'B') {
                printf("\033[0;31m%c\033[0m \t",matriz[i][j]);
            }else if(matriz[i][j] == 'X') {
                printf("%c \t",matriz[i][j]);
            }else if(matriz[i][j] == '1') {
                printf("\033[0;34m%c\033[0m \t",matriz[i][j]);
            }else if(matriz[i][j] == '2') {
                printf("\033[0;33m%c\033[0m \t",matriz[i][j]);
            }else if(matriz[i][j] == '0') {
                matriz[i][j] = 'O';
                printf("\033[0;32m%c\033[0m \t",matriz[i][j]);

            }else {
                 printf("\033[0;31m%c\033[0m \t",matriz[i][j]);

            }
        }
        puts("\n");
    }
}

void listarNumeros(char **campo, char **resposta, int tamanho,int rX,int rY,int bX, int bY) {
    for(int i = -1;i<=1;i++) {
        for(int j = -1;j<=1;j++) {
            if(rX + i >=0 && rX +i < tamanho -1 && rY+j>= 0 && rY+j < tamanho -1) {
            if(campo[rX+i][rY+j] !='B') {
                int auxX = rX+i;
                int auxY = rY+j;
                int bombas = 0; 
                for(int z= -1;z<=1;z++) {
                    for(int w=-1;w<=1;w++) {
                        if(auxX +z >=0 && auxX +z < tamanho -1 && auxY+w>= 0 && auxY+w < tamanho -1){
                            
                        if(campo[auxX+z][auxY+w] == 'B') {
                            bombas++;
                        }
                        }

                    }
                }
                resposta[auxX][auxY] = bombas + 48;
            }
            }


        }
    }

}
void Boom(char**resposta,int tamanho) {
            printMatriz(resposta,tamanho);
    printf("BOOOOM\nVoce Perdeu :(");

    getchar();
    exit(0);
}

void checarResposta(char **campo,char**resposta,int x, int y,int tamanho,int *acertos) {
            if(campo[x][y] == 'B') {
                resposta[x][y] = 'B';
                Boom(resposta,tamanho);
            }else {
                acertos ++;
                if(resposta[x][y] == 'X') {
                    resposta[x][y] = 'O';
                }
                int auxX = 0;
                int auxY = 0;
                for(int z = -1; z<= 1;z++) {
                    for(int w = -1; w<= 1;w++) {
                        if(x +z>=0 && x +z< tamanho -1 && y +w>= 0 && y+w < tamanho -1) {
                        if(z!= 0||w!=0) {
                            if(campo[x+z][y+w] == 'B') {
                                auxX = z+x;
                                auxY = w+y;
                                listarNumeros(campo,resposta,tamanho,x,y,auxX,auxY);
                            }else {
                                if(resposta[x][y] == 'X') {
                                resposta[x+z][y+w] = 'O';
                                }
                            }
                        }
                        }

                    }
                }




               
            }
        
    
}

void start(char **campo,char**resposta,int tamanho) {
    printMatriz(resposta,tamanho);
    int perdeu = 0;
    int *acertos = 0;
    int x = 0;
    int y =0;
    while(perdeu ==0) {
        printf("Qual Linha deseja? \n");
        scanf("%d",&x);
        printf("Qual Coluna deseja? \n");
        scanf("%d",&y);
        checarResposta(campo,resposta,x,y,tamanho,acertos);
        printMatriz(resposta,tamanho);
    }
    
}

int main() {
    int tamanhoVetor = 0;
    while(tamanhoVetor<9) {
    printf("Escolha o tamanho do campoo (Minimo de 9): \n");
    scanf("%d",&tamanhoVetor);
    }
    char **campo = criarMatriz(tamanhoVetor);
    char **resposta  = criarMatriz(tamanhoVetor);
    gerarBombas(campo,tamanhoVetor);
    start(campo,resposta,tamanhoVetor);
}