#include <stdio.h> 
#include "tabuleiro.h"
#include "pvp.h"
#include "cpu.h"
#include "multiplayer.h"

void gerenciar_partidas(char config[2]) {
    int redireciona[2][2];
    int voltar_menu = 0;

    // ideia para colocar um opção para voltar menu, para não ter que finalizar a partida toda vez
    while (voltar_menu == 0) { 
        Tabuleiro tab;
        inicializa(&tab);
        desenha(&tab);

    //verifica se tem vencedor de forma universal
        int status_jogo = 0;
    
        //esse config é o array do iniciar partida, [0] é a parte de guardar o modo, ele tá como p para player, c para cpu e m para multiplayer, ele tá em char (usa menos bits, e talvez seja mais intuitivo)
        switch (config[0]) {
    case 'p':
        // 1. Turno do Jogador 1 (X)
        jogador_1(redireciona[0]); 
        marcaJogada(&tab, redireciona[0][0], redireciona[0][1], CASA_X);
        desenha(&tab);
        
        // turno do segundo jogador
        jogador_2(redireciona[1]);
        marcaJogada(&tab, redireciona[1][0], redireciona[1][1], CASA_O);
        desenha(&tab);
        break;
        
    case 'c':
        //mesma coisa só que usando a CPU em um dos turnos
        iniciar_cpu(&tab, redireciona[0]);
        marcaJogada(&tab, redireciona[0][0], redireciona[0][1], CASA_O);
        desenha(&tab);
        
        jogador_1(redireciona[1]);
        marcaJogada(&tab, redireciona[1][0], redireciona[1][1], CASA_X);
        desenha(&tab);
        break;
        }
    }
}
