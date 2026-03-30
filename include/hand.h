#ifndef HAND_H
#define HAND_H
#include "deck.h"
#include "player.h"
#define MAX_HAND 5

typedef struct {
    Card cards[MAX_HAND];
    int count;
    char* name;
} Hand;

void initHand(Hand* hand, Player *player);
void dealToHand(Hand* hand, Card* deck, int* deckTop);
void printHand(Hand* hand);

#endif