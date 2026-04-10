#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hand.h"
#include "player.h"
#include "board.h"
#include "evaluate.h"
#include "algos.h"
#include "textColor.h"
#include "game.h"
#include "game.h"
#include "UI.h"

int main(void){
    //Init
    printf(BLUE"SETUP START"RESET"\n");
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    resetDeck(deck);
    GAME game;
    initGame(&game);
    printf(BLUE"SETUP END"RESET"\n\n");
    //Start
    initGame(&game);
    sizeDemo();
    dealToActivePlayers(&game);
    drawFrame(&game);
    
    
    
    //start of betting round - PREFLOP
    while(!allBetOrFolded(&game)){
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded == 0 && game.bots[i].active == 1){
                gotoxy(3 + ((i-1)*15), 2);
                printf(" ");
                gotoxy(1,23);

                bot_PreFlop(&game, i);

                updateBotWindow(&game, i);
                communityWindow(&game);
                gotoxy(3 + (i*15), 2);
                ColPrintfBot(">",i);
                gotoxy(1,23);
                _sleep(1500);
            }
        }
        gotoxy(3+60,2);printf(" ");
        game.playerChoice == inputpl(&game);
        PlayerActionExec(game.playerChoice, &game.player, &game.board);
        playerWindow(&game);
        communityWindow(&game);
    }
    //end ofbetting round - PREFLOP
    autoPot(&game);
    drawFrame(&game);//redraw whole frame for convenience

    return 0;
}