#include <stdio.h>
#include "player.h"
#include "deck.h"
#include "board.h"
#include "hand.h"
#include "game.h"
#include "textColor.h"
#include "evaluate.h"

void initGame(GAME *g){
    shuffleDeck(deck);
    g->boardHand.name = "Community";
    g->numberOfPlayers = 6;
    g->numberofActive = 6;
    g->startingChips = 1000;
    g->statusMSG = "Hello World";
    g->noMoreRaises = 0;
    initPlayer(&(g->player), (g->startingChips),"Player");
    initPlayer(&(g->bots[0]),(g->startingChips),"Bot 1");
    initPlayer(&(g->bots[1]),(g->startingChips),"Bot 2");
    initPlayer(&(g->bots[2]),(g->startingChips),"Bot 3");
    initPlayer(&(g->bots[3]),(g->startingChips),"Bot 4");
    initPlayer(&(g->bots[4]),(g->startingChips),"Bot 5");   
    initBoard(&(g->board));
    g->deckTop = 0;
    g->round = 1;
    initHand(&g->playerHand, &g->player);
    for(int i = 0; i < 5; i++){
        initHand(&g->botHands[i],&g->bots[i]);
    }
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
}

void testFindWinner(int playerScore, int botScores[], int numBots, GAME *g) {
    int maxBotScore = -1;
    int tiedBotCount = 0;
    int tiedBots[5];
    //find max + count ties
    for(int i = 0; i < numBots; i++) {
        if(botScores[i] > maxBotScore) {
            maxBotScore = botScores[i];
            tiedBotCount = 1;
            tiedBots[0] = i + 1;
        } 
        else if(botScores[i] == maxBotScore) {
            tiedBots[tiedBotCount] = i + 1;
            tiedBotCount++;
        }
    }
    printf("Player: %d, Top bots: ", playerScore);
    for(int i = 0; i < tiedBotCount; i++) {
        printf("Bot%d(%d) ", tiedBots[i], maxBotScore);
    }
    printf("\n");
    // Winner logic
    if(playerScore > maxBotScore) {
        payOutPot(&g->board, &g->player);
    } 
    else if(playerScore < maxBotScore) {
        if(tiedBotCount == 1) {
            payOutPot(&g->board, &g->bots[tiedBots[0]-1]);
        } else {
            printf("BOTS ");
            for(int i = 0; i < tiedBotCount; i++) printf("%d ", tiedBots[i]);
            printf("SPLIT POT!\n");
            int splitPot = g->board.pot / tiedBotCount;
            g->board.pot = 0;
            for(int i = 0; i < tiedBotCount; i++) {
                g->bots[tiedBots[i]-1].chips += splitPot;
            }
        }
    }
    else {
        printf("PLAYER ties with BOTS ");
        for(int i = 0; i < tiedBotCount; i++) printf("%d ", tiedBots[i]);
        printf("! SPLIT POT!\n");
        int splitPot = g->board.pot / (tiedBotCount + 1);
        g->board.pot = 0;
        g->player.chips += splitPot;
        for(int i = 0; i < tiedBotCount; i++) {
            g->bots[tiedBots[i]-1].chips += splitPot; 
        }
    }
}
int allBetOrFolded(GAME *game){
    for (int i = 0; i < 5; i++) {
        if (game->bots[i].active && !game->bots[i].folded && game->bots[i].bet != game->board.minBet) {
            return 0;
        }
    }
    if (game->player.active && !game->player.folded && game->player.bet != game->board.minBet) {
        return 0;
    }
    return 1;
}
void autoPot(GAME *g){
    placeInPot(&g->player, &g->board);
    g->player.bet = 0;
    for(int i = 0; i < 5; i++){
        placeInPot(&g->bots[i], &g->board);
        g->bots[i].bet = 0;
    }
}

void resetForNextRound(GAME *game){
    game->board.phase = 0;
    game->board.AllInSize = 0;
    game->board.AllInStatus = 0;
    game->board.minBet = 0;
    game->board.pot = 0;
    for(int i = 0; i < 5; i++){
        game->bots[i].bet = 0;
        game->bots[i].folded = 0;
        game->bots[i].raiseCount = 0;
        game->bots[i].score = 0;
        if(game->bots[i].chips <= 0){
            game->bots[i].active = 0;
        }
        game->botHands[i].count = 0;
    }
    game->player.bet = 0;
    game->player.folded = 0;
    if(game->player.chips <=0){
        game->player.active = 0;
    }
    game->player.score=0;
    game->noMoreRaises=0;
    game->playerChoice = 0;
    clearHand(&game->playerHand);
    for(int i = 0; i < 5; i++){
        clearHand(&game->botHands[i]);
    }
    clearHand(&game->boardHand);
} 