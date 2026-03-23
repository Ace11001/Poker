#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "deck.h"
#include "board.h"
#include "hand.h"

typedef struct GAME{
    int round;
    int startingChips;

    Player player;
    Hand playerHand;
    Player bots[5];
    Hand botHands[5];
    Board board;
    Hand boardHand;

    int numberOfPlayers;
    int numberofActive;
    int playerChoice;
    int deckTop;
}GAME;
void initGame(GAME *g);
void testRound(GAME *g);
void dealToActivePlayers(GAME *g);

#endif