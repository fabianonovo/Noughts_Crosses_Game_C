#include <stdio.h>       
#include "tabuleiro.h"  

/* ---------- funcoes auxiliares (static: so usadas neste arquivo) ---------- */

/* transforma o valor da casa no caractere que aparece na tela:
   1 vira 'O', 4 vira 'X' e o resto (casa vazia) vira espaco */
static char simbolo(int valor) {
    if (valor == CASA_O) return 'O';
    if (valor == CASA_X) return 'X';
    return ' ';
}

/* confere se linha e coluna estao dentro do tabuleiro (0 a 2).
   Serve pra nunca acessar uma posicao que nao existe na matriz */
static int posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}

/* soma os tres valores de uma linha (a linha fica fixa e a coluna varia) */
static int somaLinha(const Tabuleiro *tab, int linha) {
    int soma = 0;
    for (int j = 0; j < TAM; j++) {
        soma += tab->M[linha][j];
    }
    return soma;
}

/* mesma coisa, mas agora a coluna fica fixa e a linha varia */
static int somaColuna(const Tabuleiro *tab, int coluna) {
    int soma = 0;
    for (int i = 0; i < TAM; i++) {
        soma += tab->M[i][coluna];
    }
    return soma;
}

/* diagonal de canto superior esquerdo ate canto inferior direito: [0][0], [1][1], [2][2] */
static int somaDiagonalPrincipal(const Tabuleiro *tab) {
    int soma = 0;
    for (int i = 0; i < TAM; i++) {
        soma += tab->M[i][i];
    }
    return soma;
}

/* diagonal de canto superior direito ate canto inferior esquerdo: [0][2], [1][1], [2][0].
   A linha sobe (0, 1, 2) enquanto a coluna desce (2, 1, 0),
   por isso o TAM - 1 - i */
static int somaDiagonalSecundaria(const Tabuleiro *tab) {
    int soma = 0;
    for (int i = 0; i < TAM; i++) {
        soma += tab->M[i][TAM - 1 - i];
    }
    return soma;
}

/* recebe a soma de uma sequencia de 3 casas e diz quem completou ela.
   1+1+1 = 3 so pode ser O, e 4+4+4 = 12 so pode ser X.
   Nenhuma outra combinacao de 0, 1 e 4 chega nesses valores. */
static int vencedorDaSoma(int soma) {
    if (soma == 3 * CASA_O) return CASA_O;
    if (soma == 3 * CASA_X) return CASA_X;
    return SEM_VENCEDOR;
}

/* ---------- funcoes publicas (declaradas no tabuleiro.h) ---------- */

/* deixa o tabuleiro todo vazio. Tem que ser chamada logo depois de
   declarar a variavel, porque senao a matriz fica com lixo de memoria */
void inicializa(Tabuleiro *tab) {
    for (int i = 0; i < TAM; i++) {        /* i = linha */
        for (int j = 0; j < TAM; j++) {    /* j = coluna */
            tab->M[i][j] = VAZIO;
        }
    }
}

/* limpa a tela e mostra o tabuleiro atual.
   So le a matriz, nao altera nada (por isso o const) */
void desenha(const Tabuleiro *tab) {
    /* limpa a tela e volta o cursor pro canto, pra redesenhar do zero
       a cada jogada */
    printf("\033[2J\033[H");
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf(" ");    /* margem da esquerda */

        for (int j = 0; j < TAM; j++) {
            printf(" %c ", simbolo(tab->M[i][j]));

            /* a barra so vai entre as casas, nao depois da ultima */
            if (j < TAM - 1) {
                printf("|");
            }
        }
        printf("\n");

        /* mesma ideia pra linha horizontal: so entre as linhas */
        if (i < TAM - 1) {
            printf(" ---+---+---\n");
        }
    }
    printf("\n");
}

/* devolve CASA_O ou CASA_X se alguem ja fez tres em linha, ou
   SEM_VENCEDOR se ainda ninguem ganhou. Empate nao e checado aqui,
   isso fica com quem controla a partida (contando as jogadas) */
int temVencedor(const Tabuleiro *tab) {
    int v;

    /* o mesmo laco olha a linha i e a coluna i. Se achar um vencedor
       ja devolve na hora, sem precisar olhar o resto */
    for (int i = 0; i < TAM; i++) {
        v = vencedorDaSoma(somaLinha(tab, i));
        if (v != SEM_VENCEDOR) return v;

        v = vencedorDaSoma(somaColuna(tab, i));
        if (v != SEM_VENCEDOR) return v;
    }

    /* as duas diagonais ficam fora do laco */
    v = vencedorDaSoma(somaDiagonalPrincipal(tab));
    if (v != SEM_VENCEDOR) return v;

    /* ultima verificacao: devolve o que ela achar, vencedor ou nao */
    return vencedorDaSoma(somaDiagonalSecundaria(tab));
}

/* grava a jogada na matriz. Devolve 1 se marcou e 0 se recusou
   (tipo errado, posicao que nao existe ou casa ja ocupada), pra quem
   chamou saber se precisa pedir outra jogada ao jogador */
int marcaJogada(Tabuleiro *tab, int linha, int coluna, int tipo) {
    /* so aceita O ou X */
    if (tipo != CASA_O && tipo != CASA_X) return 0;

    /* casaVazia ja confere se a posicao existe, entao nao precisa
       repetir essa checagem aqui */
    if (!casaVazia(tab, linha, coluna)) return 0;

    tab->M[linha][coluna] = tipo;
    return 1;
}

/* devolve o que tem na casa (VAZIO, CASA_O ou CASA_X). Existe pra outros
   modulos, como a IA, olharem o tabuleiro sem mexer na matriz direto.
   Devolve -1 se a posicao nao existir */
int valorCasa(const Tabuleiro *tab, int linha, int coluna) {
    if (!posicaoValida(linha, coluna)) return -1;
    return tab->M[linha][coluna];
}

/* devolve 1 se a posicao existe e esta livre, 0 caso contrario */
int casaVazia(const Tabuleiro *tab, int linha, int coluna) {
    /* confere os limites primeiro pra nunca acessar fora da matriz */
    if (!posicaoValida(linha, coluna)) return 0;
    return tab->M[linha][coluna] == VAZIO;
}
