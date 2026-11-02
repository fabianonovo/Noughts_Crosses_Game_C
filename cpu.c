#include "tabuleiro.h"

//recebe o tabuleiro no momento atual para fazer oq dá
void iniciar_cpu(Tabuleiro *tab, int redireciona[2]) {
    
    //(Tenta ganhar agora)
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            if (casaVazia(tab, linha, coluna)) {
                (*tab).M[linha][coluna] = CASA_O;
                
                if (temVencedor(tab) == CASA_O) {
                    (*tab).M[linha][coluna] = VAZIO; 
                    redireciona[0] = linha;           
                    redireciona[1] = coluna;           
                    return;
                }
                (*tab).M[linha][coluna] = VAZIO;
            }
        }
    }

    //não dá pra ganhar e o cara vai vencer,impede o x de vencer
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            if (casaVazia(tab, linha, coluna)) {
                (*tab).M[linha][coluna] = CASA_X; //simula o oponente jogando aqui
                
                if (temVencedor(tab) == CASA_X) { 
                    (*tab).M[linha][coluna] = VAZIO;       
                    redireciona[0] = linha;         
                    redireciona[1] = coluna;           
                    return;
                }
                (*tab).M[linha][coluna] = VAZIO;
            }
        }
    }

    //ninguém ganha agora ou joga no meio ou na primeira livre)
    if (casaVazia(tab, 1, 1)) {
        redireciona[0] = 1; redireciona[1] = 1;
        return;
    }
    
    //se o meio tá ocupado,pega a primeira que achar 
    for (int linha = 0; linha < TAM; linha++) {
        for (int coluna = 0; coluna < TAM; coluna++) {
            if (casaVazia(tab, linha, coluna)) {
                redireciona[0] = linha; redireciona[1] = coluna;
                return;
            }
        }
    }
}
