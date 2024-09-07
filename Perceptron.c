#include <stdio.h>
#include <stdlib.h>

/*
a reta é dada por x1*w1 + x2*w2 + b = 0 

2, 1, 2, 5, 7, 2, 3, 6, 1, 2, 5, 4, 6, 5 - > x1
2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 7 - > x2
0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1 - > saidas esperadas

a saida é decidida por x0*w0 + x1*w1 + x2*w2

*/

// funcao que compara as saidas que obtivemos com as saidas esperadas
int compararSaidas(int saidas_obtidas[], int saidas_esperadas[]){
    for(int i = 0; i<14; i++){
        if(saidas_esperadas[i] != saidas_obtidas[i]) return 0;
    }
    return 1;
}

/*
funcao que faz o somatório de 1 até n do produto do i-ésimo X com o i-ésimo W
que nesse caso fica x0*w0 + x1*w1 + x2*w2
*/
float somatorio(int x0, int x1, int x2, float w0, float w1, float w2){
    float soma = x0*w0 + x1*w1 + x2*w2;
    return soma;
}

int main(){
    // vetores das entradas
    int x0 = 1;
    int x1[14] = {2, 1, 2, 5, 7, 2, 3, 6, 1, 2, 5, 4, 6, 5};
    int x2[14] = {2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 7};

    float w[3] = {-2, 1, -4}; // vetor de pesos {bias, peso1, peso2}

    int saidas_esperadas[14] = {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1}; // vetor das saídas esperadas
    int saidas_obtidas[14]; // vetor das saidas obtidas

    float alfa = 7; // definindo a constante de aprendizado
    while(compararSaidas(saidas_obtidas, saidas_esperadas) == 0){
        for(int i = 0; i<14; i++){
            float soma_ponderada = somatorio(x0, x1[i], x2[i], w[0], w[1], w[2]);

            //Se x0*w0 + x1*w1 + x2*w2 for maior que zero, sua saída é 1, caso contrário é 0
            if(soma_ponderada > 0){
                saidas_obtidas[i] = 1;
            }
            else{
                saidas_obtidas[i] = 0;
            }

            int erro = saidas_esperadas[i] - saidas_obtidas[i]; // pode ser (-1, 0, 1)

            // remodelando o vetor de pesos de acordo com o erro
            w[0] = w[0] + alfa*erro;
            w[1] = w[1] + alfa*erro*x1[i];
            w[2] = w[2] + alfa*erro*x2[i];
        }

        printf("reta: x*%f + y*%f + %f = 0\n", w[1], w[2], w[0]);
    }
    return 0;
}