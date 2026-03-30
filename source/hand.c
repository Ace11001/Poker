#include "hand.h"
#include <stdlib.h>

void initHand(Hand* hand){
    hand->count = 0;
}
void dealToHand(Hand* hand, Card* deck, int* deck_top) {
    hand->cards[hand->count] = deck[*deck_top];
    (hand->count)++;
    (*deck_top)++;
}

void printHand(Hand* hand){
    int cardCount = hand->count;
    printf(" Cards:\n");
    if(cardCount == 0){
        printf(">empty");
    }
    for(int i = 0; i < cardCount; i++){
        printCardName(&hand->cards[i]);
    }
    printf("\n");
}