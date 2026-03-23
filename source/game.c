#include <stdio.h>
#include "player.h"
#include "deck.h"
#include "board.h"
#include "hand.h"
#include "game.h"
#include "textColor.h"

void initGame(GAME *g){
    g->numberOfPlayers = 6;
    g->numberofActive = 6;
    g->startingChips = 1000;
    initPlayer(&(g->player), (g->startingChips),"Player");
    initPlayer(&(g->bots[0]),(g->startingChips),"Bot 1");
    initPlayer(&(g->bots[1]),(g->startingChips),"Bot 2");
    initPlayer(&(g->bots[2]),(g->startingChips),"Bot 3");
    initPlayer(&(g->bots[3]),(g->startingChips),"Bot 4");
    initPlayer(&(g->bots[4]),(g->startingChips),"Bot 5");   
    initBoard(&(g->board));
    g->deckTop = 0;
    g->round = 1;

    g->playerHand.count = 0;
    for(int i = 0; i<5; i++){
        g->botHands[i].count=0;
    }
    g->boardHand.count=0;
}
void dealToActivePlayers(GAME *g) {
    g->playerHand.count = 0;
    for(int i = 0; i<5; i++) g->botHands[i].count = 0;
    
    for (int j = 0; j < 2; j++) {
        if (g->player.active == 1 && g->player.folded == 0) {
            dealToHand(&g->playerHand, deck, &g->deckTop);
        }
        for (int i = 0; i < g->numberOfPlayers - 1; i++) {
            if (g->bots[i].active == 1 && g->bots[i].folded == 0) {
                dealToHand(&g->botHands[i], deck, &g->deckTop);
            }
        }
    }
    printHand(&g->playerHand);
}


void testRound(GAME *g){
    ColPrintfPlus("Round %d starting\n", (g->round), 1);
    int minBet = (g->board).minBet;
    printf(" > Opening bets - %d\n\n", minBet);
    g->playerChoice = playerAction();
    PlayerActionExec(g->playerChoice, &g->player, &g->board);
    dealToActivePlayers(g);
    
    dealToHand(&(g->boardHand),deck, &(g->deckTop));
    dealToHand(&(g->boardHand),deck, &(g->deckTop));
    dealToHand(&(g->boardHand),deck, &(g->deckTop));
    printf("%s's",g->player.name);
    printHand(&g->playerHand);
    printf("Board");
    printHand(&g->boardHand);
}