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

#define BOT_TIMER 150
#define CARD_TIMER 40

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
                gotoxy(3 + (i*15), 2);ColPrintfBot(">",i);
                gotoxy(1,23);
                _sleep(BOT_TIMER);
                gotoxy(3 + (i*15), 2);printf(" ");
            }
        }
        gotoxy(3+60,2);printf(" ");
        game.playerChoice = inputpl(&game);
        PlayerActionExec(game.playerChoice, &game.player, &game.board);
        playerWindow(&game);
        communityWindow(&game);
        int botFolds = 0;
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded){botFolds++;}
        }
        if(botFolds == 5){
            break;
        }
    }
    //need to check if game can still continue - all bots folded or similar situations ->award pot
    //end ofbetting round - PREFLOP
    autoPot(&game);
    drawFrame(&game);//redraw whole frame for convenience
    //drawing community cards
    for(int i = 0; i < 3; i++){
        dealToHand(&game.boardHand, deck, &game.deckTop);
        communityWindow(&game);
        _sleep(CARD_TIMER);
    }
    game.board.communityCount = 3;
    game.boardHand.count = 3;
    //community cards dealt
    //FLOP
    while(!allBetOrFolded(&game)){
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded == 0 && game.bots[i].active == 1){
                gotoxy(3 + ((i-1)*15), 2);
                printf(" ");
                gotoxy(1,23);

                bot_Flop(&game, i);
                updateBotWindow(&game, i);
                communityWindow(&game);
                gotoxy(3 + (i*15), 2);ColPrintfBot(">",i);
                gotoxy(1,23);
                _sleep(BOT_TIMER);
                gotoxy(3 + (i*15), 2);printf(" ");
            }
        }
        gotoxy(3+60,2);printf(" ");
        game.playerChoice = inputpl(&game);
        PlayerActionExec(game.playerChoice, &game.player, &game.board);
        playerWindow(&game);
        communityWindow(&game);
        int botFolds = 0;
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded){botFolds++;}
        }
        if(botFolds == 5){
            break;
        }
    }
    autoPot(&game);
    drawFrame(&game);
    dealToHand(&game.boardHand,deck, &game.deckTop);
    communityWindow(&game);
    _sleep(CARD_TIMER);
    game.board.communityCount = 4;
    game.boardHand.count = 4;
    //TURN
    while(!allBetOrFolded(&game)){
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded == 0 && game.bots[i].active == 1){
                gotoxy(3 + ((i-1)*15), 2);
                printf(" ");
                gotoxy(1,23);

                bot_Turn(&game, i);
                updateBotWindow(&game, i);
                communityWindow(&game);
                gotoxy(3 + (i*15), 2);ColPrintfBot(">",i);
                gotoxy(1,23);
                _sleep(BOT_TIMER);
                gotoxy(3 + (i*15), 2);printf(" ");
            }
        }
        gotoxy(3+60,2);printf(" ");
        game.playerChoice = inputpl(&game);
        PlayerActionExec(game.playerChoice, &game.player, &game.board);
        playerWindow(&game);
        communityWindow(&game);
        int botFolds = 0;
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded){botFolds++;}
        }
        if(botFolds == 5){
            break;
        }
    }
    autoPot(&game);
    drawFrame(&game);
    dealToHand(&game.boardHand, deck, &game.deckTop);
    communityWindow(&game);
    _sleep(CARD_TIMER);
    game.board.communityCount = 5;
    game.boardHand.count = 5;
    //RIVER
    while(!allBetOrFolded(&game)){
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded == 0 && game.bots[i].active == 1){
                gotoxy(3 + ((i-1)*15), 2);
                printf(" ");
                gotoxy(1,23);

                bot_River(&game, i);
                updateBotWindow(&game, i);
                communityWindow(&game);
                gotoxy(3 + (i*15), 2);ColPrintfBot(">",i);
                gotoxy(1,23);
                _sleep(BOT_TIMER);
                gotoxy(3 + (i*15), 2);printf(" ");
            }
        }
        gotoxy(3+60,2);printf(" ");
        game.playerChoice = inputpl(&game);
        PlayerActionExec(game.playerChoice, &game.player, &game.board);
        playerWindow(&game);
        communityWindow(&game);
        int botFolds = 0;
        for(int i = 0; i < 5; i++){
            if(game.bots[i].folded){botFolds++;}
        }
        if(botFolds == 5){
            break;
        }
    }
    showdownScreen();
    _sleep(1000);
    return 0;
}