#include <stdio.h>       
#include "tabuleiro.h"
/* TAM é um valor definido no .h (equivale ao tamanho padrão [3][3] matriz
Vazio 0 (0 é invisivel na matriz) casa_0 = 1 casa_x = 4 sem_vencedor = 0
*/ 
/* confere se linha e coluna estao dentro do tabuleiro (0 a 2).
   Serve pra nunca acessar uma posicao que nao existe na matriz */
static int posicaoValida(int linha, int coluna) {
    return linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM;
}
//nessa função eu devlaro o ponteiro chamado tab que recebe o endereço repassado por tem vencedor para fazer os cálculos na matriz e repassar se tem ou não vencedor e quem é, Tabuleiro é o tipo de estrutura em tabuleiro.h 
static int somaLCD(const Tabuleiro *tab) {
    int somalcd[4] = {0,0,0,0}, linha = 0, coluna = 0;
    //soma lcd é um array contendo todas as informações de soma numéricas do fluxo da partida (valores) posição 0 linha coluna 1 diagonal de cima 2 diagonal debaixo 3
    for ( linha = 0; linha < TAM; linha++){
        somalcd[0] = 0; 
        somalcd[1] = 0;
        for ( coluna = 0; coluna < TAM; coluna++){
           
            somalcd[0] += (*tab).M[linha][coluna];
            somalcd[1] += (*tab).M[coluna][linha];
            //linha e colunas são inversos, fiz essa distinção para conseguir somar os 2 usando apenas um for
            if (linha == coluna){
                somalcd[2] += (*tab).M[linha][coluna];
            }
            if ((linha + coluna) == 2){ // relações fundamentais de uma matriz 3x3 de forma que só pege as colunas de baixo para cima sem usar outro for, garante o elemento canto superior direito da coluna 0+2 = 2, canto inferior 2+0=2 e do meio 1+1
                somalcd[3] += (*tab).M[linha][coluna];
            }
        }
        for (int procura_vencedor = 0; procura_vencedor < 4; procura_vencedor++){
            if (somalcd[procura_vencedor] == 3){
                return CASA_O;
            }else if(somalcd[procura_vencedor] == 12){
                return CASA_X; //tanto o CASA_O quanto CASA_X estão definidos um como 3 e outro como 12 na decisão de vitorias em soma
            }
        }
    }
    return SEM_VENCEDOR;
    
}

/* ---------- funcoes publicas (declaradas no tabuleiro.h) ---------- */

//todo elemento da matriz 3x3(tabuleiro) ganha o valor vazio que é definido em tabuleiro.h como vazio = 0 (zera todas posições do tabuleiro, jogo novo ou iniciar o primeiro jogo)
void inicializa(Tabuleiro *tab) {
    for (int linha = 0; linha < TAM; linha++) {        
        for (int coluna = 0; coluna < TAM; coluna++) {   
            (*tab).M[linha][coluna] = VAZIO;
        }
    }
}

int valorCasa(const Tabuleiro *tab, int linha, int coluna) {
    if (!posicaoValida(linha, coluna)) return -1;
    return (*tab).M[linha][coluna];
}

int casaVazia(const Tabuleiro *tab, int linha, int coluna) {
    if (!posicaoValida(linha, coluna)) return 0;
    return (*tab).M[linha][coluna] == VAZIO;
}

int marcaJogada(Tabuleiro *tab, int linha, int coluna, int tipo) {
    /* so aceita O ou X */
    if (tipo != CASA_O && tipo != CASA_X) return 0;

    /* casaVazia ja confere se a posicao existe, entao nao precisa
       repetir essa checagem aqui */
    if (!casaVazia(tab, linha, coluna)) return 0;

    (*tab).M[linha][coluna] = tipo; //tipo vem lá da partida.c só executa se passar pelas duas verificações de cima
    return 1;
}

void desenha(const Tabuleiro *tab) {
    printf("\033[2J\033[H");
    printf("\n");

    for (int linha = 0; linha < TAM; linha++) {
        printf(" ");    /* margem da esquerda */

        for (int coluna = 0; coluna < TAM; coluna++) {
            //verifica o valor da casa e faz a troca meramente visual de 1 para O e 4 para X
            if ((*tab).M[linha][coluna] == 1){
                printf(" O ");
            }else if ((*tab).M[linha][coluna] == 4){
                printf(" X ");
            }else{
                printf("   ");
            }
            /* a barra so vai entre as casas, nao depois da ultima */
            if (coluna < TAM - 1) {
                printf("|");
            }
        }
        printf("\n");
        /* mesma ideia pra linha horizontal: so entre as linhas */
        if (linha < TAM - 1) {
            printf(" ---+---+---\n");
        }
    }
    printf("\n");
}

int temVencedor(const Tabuleiro *tab) {
    return somaLCD(tab);
}
