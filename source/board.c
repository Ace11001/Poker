#include "board.h"
#include <stdio.h>
#include "board.h"
#include "player.h"

void initBoard(Board *b){
    b->pot = 0;
    b->minBet = 2;
    b->phase = 0;
    b->AllInStatus = 0;
    b->AllInSize = 0;
    b->communityCount = 0;
}
void payOutPot(Board *b, Player *p){
    int transfer = b->pot;
    b->pot = 0;
    p->chips += transfer;
}
void placeInPot(Player *p, Board *b){
    int amount = p->bet;
    p->chips -=amount;
    b->pot += amount;
}
void bustDetection(Player *p){
    if(p->chips==0){
        p->active = 0;
    }
}
int getShowdown(int scores[],int playerCount){
    int bestIndex = 0;
    for(int i = 1; i<playerCount;i++){
        if(scores[i] >scores[bestIndex]){
            bestIndex = i;
        }
    }
    return bestIndex;//no ties
}