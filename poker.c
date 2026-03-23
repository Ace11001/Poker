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

int main(void){
    //Init
    printf(BLUE"SETUP START"RESET"\n");
    srand(time(NULL));
    createDeck(deck);
    shuffleDeck(deck);
    resetDeck(deck);
    GAME gameSpace;
    initGame(&gameSpace);
    printf(BLUE"SETUP END"RESET"\n\n");
    //Init end
    printf("active%d|folded%d\n", gameSpace.player.active, gameSpace.player.folded);
    testRound(&gameSpace);
    return 0;
}