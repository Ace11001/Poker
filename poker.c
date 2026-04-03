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
    game.statusMSG = "Start of round";
    drawFrame(&game, 0);
    _sleep(1000);
    game.statusMSG = "Betting start";
    drawFrame(&game, 1);
    PlayerActionExec(game.playerChoice, &game.player, &game.board);
    switch(game.playerChoice){
        case 0:
            game.statusMSG = "Player Checks/Calls";
            break;
        case 1:
            game.statusMSG = "Player Raises";
            break;
        case 2:
            game.statusMSG = "Player goes ALL-IN";
            break;
        case 3:
            game.statusMSG = "Player folds";
            break;
        default: break;
    }
    drawFrame(&game, 0);
    for(int i = 0; i < 5; i++){
        game.bots[i].bet = game.board.minBet;
        placeInPot(&game.bots[i],&game.board);
    }
    dealToActivePlayers(&game);
    for(int i = 0; i < 5; i++){
        bot_PreFlop(&game, i);
        drawFrame(&game, 0);
        printf("Bot %d's turn\n", i+1);
        _sleep(2000);
    }
    if(game.board.minBet > game.player.bet){
        drawFrame(&game, 1);
        for(int i = 0; i < 5; i++){
            bot_PreFlop(&game, i);
            drawFrame(&game, 0);
            printf("Bot %d's turn\n", i+1);
            _sleep(2000);
        }
    }
    drawFrame(&game, 0);

    return 0;
} 