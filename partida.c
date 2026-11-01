#include <stdio.h>
#include <ctype.h> 
#include "tabuleiro.h"

// função para o jogador escolher se quer 'X' ou 'O'
static char escolher_X_ou_O() { 
    char x_or_o;  
    char player_choose = -1;

    //escolha do player 
    printf("Escolha X ou O para jogar: "); 
    scanf(" %c", &x_or_o);     
    switch (tolower(x_or_o)) {
        case 'x':
            player_choose = '0'; 
            break; 
        case 'o': 
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
    
    printf("\022[2J\033[H");
    printf("\n |        MODO DE JOGO        |\n"
            "1 - PVP (Local)\n"
            "2 - PLAYER VS CPU (IA)\n"
            "3 - PLAYER VS PLAYER (REMOTO)\n"
            "Escolha a opcao desejada: ");
          
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

// inicia a estrutura do jogo
static int gerenciar_partidas(char config[2]) {
    int redireciona[2][2]; 
    int rodada = 0, status_jogo = 0;
    int turno_atual = CASA_X; //x padrão de inicio
    
    Tabuleiro tab;     
    inicializa(&tab);  

    while (rodada < 9 && status_jogo == SEM_VENCEDOR) {
        //quem joga no turno
        if (config[0] == 'p') {
            if (turno_atual == CASA_X) jogador_1(redireciona[0]);
            else jogador_2(redireciona[0]);
        } else if (config[0] == 'c') {
            if (turno_atual == CASA_X) jogador_1(redireciona[0]);
            else iniciar_cpu(&tab, redireciona[0]);       
        }
        //grava, desenha e testa a vitória
        marcaJogada(&tab, redireciona[0][0], redireciona[0][1], turno_atual);
        desenha(&tab);
        status_jogo = temVencedor(&tab);
       
       if (status_jogo != 0){ 
            return status_jogo;
        }
        
        //passa a vez para o próximo
        if (turno_atual == CASA_X) turno_atual = CASA_O;
        else turno_atual = CASA_X;
        
        rodada++;
    }
    return SEM_VENCEDOR; 
}

static void start_game(char config[2]);

static void fim_jogo(char config[2]) {
    int vencedores_rodadas_x_o[2] = {0, 0}; 
    int escolha; 
    do { 
        int status_jogo = gerenciar_partidas(config); 
        
        if (status_jogo == CASA_X) {
            printf("\n| Jogador X venceu!  |\n");
            vencedores_rodadas_x_o[0]++;
        } else if (status_jogo == CASA_O) {
            printf("\n|   Jogador O venceu!  |\n");
            vencedores_rodadas_x_o[1]++;
        } else {
            printf("\n|   Deu velha chefe!   |\n");
        }

        printf("\nPLACAR GERAL: X [%d] x [%d] O\n\n", vencedores_rodadas_x_o[0], vencedores_rodadas_x_o[1]);

        printf("Deseja reiniciar a partida digite (1) deseja voltar ao menu digite (0): ");
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            continue; 
        } else {
            start_game(config); 
            break; 
        }
    } while (escolha == 1);
}
//inicia o tabuleiro 3x3, que logo iniciara a jogada
static void rotear_jogo(char config[2]) {
    if (config[0] == '1') {
        config[0] = 'p'; 
    }else if (config[0] == '2'){
        config[0] = 'c'; 
    }else if (config[0] == '3'){
        config[0] = 'm'; 
    }
}

void start_game(char config[2]) { 
    config[0] = mode();
    rotear_jogo(config);
    config[1] = escolher_X_ou_O();  
    fim_jogo(config);  
}
