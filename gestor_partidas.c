#include <stdio.h>
#include "tabuleiro.h"
#include "pvp.h"
#include "cpu.h"
#include "multiplayer.h"

//função para fazer o tabalho sujo de gerenciar todos os tipos de jogadores sem encher o main de lixo redundante

void gerenciar_partidas(char config[2]) {
    int redireciona[2][2];
    int escolha, voltar_menu = 0;
    
    // [0] guarda vitórias do x, [1] vitórias do O
    int vencedores_rodadas_x_o[2] = {0, 0}; 

    // ideia para colocar um opção para voltar menu, para não ter que finalizar a partida toda vez
    while (voltar_menu == 0) { 
        Tabuleiro tab;
        inicializa(&tab);
        desenha(&tab);
        
        int rodada = 0;
        int status_jogo = 0; // se tá rodando em 0 significa que rodando. 1 (O) ou 4 (X) significa que alguém ganhou
        
        //estou vendo como vou implementar algo como isso:

        /*puts("Pressione ESC e de Enter se quiser abortar (ou continue jogando).");*/
        
        // Loop que garante que a partida rode até 9 vezes ou até alguém vencer
        while (rodada < 9 && status_jogo == 0) {
            
            //esse config é o array do iniciar partida, [0] é a parte de guardar o modo, ele tá como p para player, c para cpu e m para multiplayer, ele tá em char (usa menos bits, e talvez seja mais intuitivo)
            switch (config[0]) {
                case 'p':
                    //turno do jogador 1 (X)
                    jogador_1(redireciona[0]); 
                    marcaJogada(&tab, redireciona[0][0], redireciona[0][1], CASA_X);
                    desenha(&tab);
                    rodada++;

                    //atualiza status
                    status_jogo = temVencedor(&tab);
                    
                    // se x ganhar ou velha para tudo
                    if (status_jogo != 0 || rodada == 9) break;

                    // turno do segundo jogador
                    jogador_2(redireciona[1]);
                    marcaJogada(&tab, redireciona[1][0], redireciona[1][1], CASA_O);
                    desenha(&tab);
                    rodada++;
                    status_jogo = temVencedor(&tab);
                    break;
                    
                case 'c':
                    //mesma coisa só que usando a CPU em um dos turnos
                    iniciar_cpu(&tab, redireciona[0]);
                    marcaJogada(&tab, redireciona[0][0], redireciona[0][1], CASA_O);
                    desenha(&tab);
                    rodada++;
                    status_jogo = temVencedor(&tab);
                    
                    if (status_jogo != 0 || rodada == 9) break;

                    jogador_1(redireciona[1]);
                    marcaJogada(&tab, redireciona[1][0], redireciona[1][1], CASA_X);
                    desenha(&tab);
                    rodada++;
                    status_jogo = temVencedor(&tab);
                    break;
            }
        }

        // verifica se tem vencedor de forma universal
        // conectar a soma do tabuleiro para entregar um vencedor
        // x ganhou adiciona ao placar de x que é [0] do array de vencedore
        if (status_jogo == CASA_X) {
            printf("\n| Jogador X venceu!  |\n");
            vencedores_rodadas_x_o[0]++;
        // se o x perder adiciona 1 para bola
        } else if (status_jogo == CASA_O) {
            printf("\n|   Jogador O venceu!  |\n");
            vencedores_rodadas_x_o[1]++;
        // não acho que quem ganhar ou quem perder, nem quem ganhar nem perder, vai ganhar ou perder. vai todo mundo perder
        } else {
            printf("\n|   Deu velha chefe!   |\n");
        }

        printf("\nPLACAR GERAL: X [%d] x [%d] O\n\n", vencedores_rodadas_x_o[0], vencedores_rodadas_x_o[1]);

        printf("Deseja reiniciar a partida digite (1) deseja voltar ao menu digite (0): ");
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            // essa foi uma ideia que reinicia partida
            //automaticamente cria e inicializa o tabuleiro do zero
            continue; 
        } else {
            voltar_menu = 1;
        }
    }
}
