#include <stdio.h>
#include "tabuleiro"
#include "ia_vs_player_mode"
#include "desenhar_tabuleiro"

// Função para o jogador escolher se quer 'X' ou 'O'
int player_x_or_o() { 
    char x_or_o;  
    int player_choose = -1;
    
    printf("Escolha X ou O para jogar: "); 
    scanf(" %c", &x_or_o); // O espaço antes do %c limpa quebras de linha pendentes
    
    switch (x_or_o) { 
        case 'x':
        case 'X': // Aceita maiúscula e minúscula
            player_choose = 0; 
            break; 
        case 'o': 
        case 'O':
            player_choose = 1; 
            break; 
        default:
            printf("Escolha invalida!\n");
            break;
    } 
    
    return player_choose; 
} 

// Função para escolher o modo de jogo
int mode() { 
    int escolha;
    
    printf("\n |       MODO DE JOGO       |\n");
    printf("1 - PVP (Local)\n");
    printf("2 - PLAYER VS CPU (IA)\n");
    printf("3 - PLAYER VS PLAYER (REMOTO)\n");
    printf("Escolha a opçao desejada: ");
    
    //esolha de jogo
    scanf("%d", &escolha);
    
    switch (escolha) { 
        case 1: 
            printf("Modo selecionado: Humano vs Humano\n");
            return 1;
        case 2: 
            printf("Modo selecionado: Humano vs Computador\n");
            return 2;
        case 3:
            printf("Modo selecionado: Jogador Remoto\n");
            return 3;
        default:
            printf("Opcao invalida. A assumindo o modo Local.\n");
            return 1; 
    }
}
//inicia o tabuleiro 3x3, que logo iniciara a jogada
void iniciar_tabuleiro(){
    

    
}
// inicia a estrutura do jogo
int main() { 
    int jogadores = mode();
    int choose = player_x_or_o();  
    int a[2] = {jogadores, choose,};

    return 0;
}
