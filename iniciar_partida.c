#include <stdio.h>
#include "tabuleiro.h"

// função para o jogador escolher se quer 'X' ou 'O'
static char player_x_or_o() { 
    char x_or_o;  
    char player_choose = -1;

    //escolha do player 
    printf("Escolha X ou O para jogar: "); 
    scanf(" %c", &x_or_o);     
    switch (x_or_o) { 
        case 'x':
        case 'X': 
            player_choose = '0'; 
            break; 
        case 'o': 
        case 'O':
            player_choose = '1'; 
            break; 
        default:
            printf("assumindo 'x' por padrão\n");
            player_choose = '0';
            break;
    } 
    
    return player_choose; 
} 

// Função para escolher o modo de jogo
static char mode() { 
    char escolha;
    
    printf("\n |       MODO DE JOGO       |\n");
    printf("1 - PVP (Local)\n");
    printf("2 - PLAYER VS CPU (IA)\n");
    printf("3 - PLAYER VS PLAYER (REMOTO)\n");
    printf("Escolha a opçao desejada: ");
    
    //escolha de jogo
    scanf(" %c", &escolha);
    
    switch (escolha) { 
        case '1': 
            printf("Modo selecionado: Humano vs Humano\n");
            return '1';
        case '2': 
            printf("Modo selecionado: Humano vs Computador\n");
            return '2';
        case '3':
            printf("Modo selecionado: Jogador Remoto\n");
            return '3';
        default:
            printf("Opcao invalida. A assumindo o modo Local.\n");
            return '1'; 
    }
}
//inicia o tabuleiro 3x3, que logo iniciara a jogada
void rotear_jogo(char config[2]) {

    if (config[0] == '1') {
        config[0] = 'p' //player
    } else if (config[0] == '2'){
        config[0] = 'c' //cpu
    } else if (config[0] == '3') {
        config[0] = 'm' //multiplayer
    }
}
// inicia a estrutura do jogo
void start_game(char config[2]) { 
    config[0] = mode();
    config[1] = player_x_or_o();  
}
