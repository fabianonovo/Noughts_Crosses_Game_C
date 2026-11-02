#include <stdio.h>

void jogador_1(int redireciona[2]) {
    printf("jogador 1 (X), digite a linha e coluna (0 a 2): ");
    scanf("%d %d", &redireciona[0], &redireciona[1]);
}

void jogador_2(int redireciona[2]) {
    printf("jogador 2 (O), digite a linha e coluna (0 a 2): ");
    scanf("%d %d", &redireciona[0], &redireciona[1]);
}
