#ifndef _TABULEIRO_H_
#define _TABULEIRO_H_
#define TAM 3
#define VAZIO   0
#define CASA_O  1
#define CASA_X  4
#define SEM_VENCEDOR 0

typedef struct {
    int M[TAM][TAM];
} Tabuleiro;
void inicializa(Tabuleiro *tab);
void desenha(const Tabuleiro *tab);
int temVencedor(const Tabuleiro *tab);
int marcaJogada(Tabuleiro *tab, int linha, int coluna, int tipo);
int valorCasa(const Tabuleiro *tab, int linha, int coluna);
int casaVazia(const Tabuleiro *tab, int linha, int coluna);

#endif
