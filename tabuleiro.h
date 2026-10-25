#ifndef _TABULEIRO_H_
#define _TABULEIRO_H_

/* Tamanho do tabuleiro (3 linhas x 3 colunas) */
#define TAM 3

/* Valores que cada casa da matriz pode ter */
#define VAZIO   0
#define CASA_O  1
#define CASA_X  4

/* Valor devolvido por temVencedor() quando ninguem ganhou ainda */
#define SEM_VENCEDOR 0

/* Estrutura do tabuleiro: so tem a matriz M */
typedef struct {
    int M[TAM][TAM];
} Tabuleiro;

/* Coloca todas as casas como VAZIO */
void inicializa(Tabuleiro *tab);

/* Limpa a tela e desenha o tabuleiro atual (so le, nao altera) */
void desenha(const Tabuleiro *tab);

/* Devolve CASA_O ou CASA_X se alguem venceu, ou SEM_VENCEDOR */
int temVencedor(const Tabuleiro *tab);

/* Marca a jogada (tipo = CASA_O ou CASA_X) em linha/coluna (0 a 2).
   Devolve 1 se marcou, 0 se a posicao for invalida ou ja estiver ocupada */
int marcaJogada(Tabuleiro *tab, int linha, int coluna, int tipo);

/* Devolve o valor guardado na casa (VAZIO, CASA_O ou CASA_X),
   ou -1 se a posicao nao existir */
int valorCasa(const Tabuleiro *tab, int linha, int coluna);

/* Devolve 1 se a posicao existe e esta vazia, 0 caso contrario */
int casaVazia(const Tabuleiro *tab, int linha, int coluna);

#endif
