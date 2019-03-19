#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

void pause(){
    __fpurge(stdin);
    getchar();
}

int main(){
    int matriz[20][20];
    
    //Cria tabela 20x20 randômica
    for (int a = 0; a < 20; a++){
        for (int b = 0; b < 20; b++){
            printf("%d\t", matriz[a][b] = rand()%99);
            //pause();
            if (b == 19) printf("\n");
        }
    }

    int contH = 0, contV = 0, contD = 0, cont = 0, produto[396];
    for (int j = 0; j < 397; j++) produto[j] = 1; //Inicia variéveis

    //Verifica na horizontal
    for (int a = 0; a < 20; a++){
        for (int b = 0; b < 20; b++){
            cont++;
            produto[contH] = produto[contH] * matriz[a][b];
            //printf("%d\t", matriz[a][b]);
            if (cont == 4){
                //printf("\t%d- %d\n",contH,produto[contH]);
                cont = 0;
                contH++;
                b -= 3;
            }
        }
    }
    printf("\n\n%d\n\n",contH);
    printf("%d\n%d\n%d\n\n\n",matriz[0][0],matriz[10][10],matriz[19][19]);
    return 0;
}