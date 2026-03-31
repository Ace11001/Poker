#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#define BLUE "\033[34m" 
#define GRAY "\033[90m" 
#define YELLOW "\e[0;33m" //Chips
#define DARKBLUE "\033[0;36m"
//bot names
#define CYAN "\e[0;36m"    //0
#define MAGENTA "\e[0;35m" //1
#define GREEN "\e[0;32m"   //2
#define RED "\e[0;31m"     //3
#define BYELLOW "\e[0;93m" //4
//format
#define RESET "\033[0m"
#define ITALIC "\033[1;34;3m" 
void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}
void botWindow(int xCord, int yCord, char* botName, int chips, int bet, int colIndex, int foldedStatus, int activeStatus){
if(activeStatus == 1){
    gotoxy(xCord, yCord);
    printf("+------------+");
    gotoxy(xCord, yCord+1);
    switch(colIndex){
        case 0:
            printf("|"CYAN "%8s"RESET"    |",botName);
            break;
        case 1: 
            printf("|"MAGENTA "%8s"RESET"    |",botName);
            break;
        case 2:
            printf("|"GREEN "%8s"RESET"    |",botName);
            break;
        case 3:
            printf("|"RED "%8s"RESET"    |",botName);
            break;
        case 4:
            printf("|"BYELLOW "%8s"RESET"    |",botName);
            break;
        default:
            printf("|%8s    |",botName);
            break;
    }
    gotoxy(xCord, yCord+2);
    printf("|Chips:" YELLOW "%5d" RESET " |", chips);
    gotoxy(xCord, yCord+3);
    if(foldedStatus == 0){
        printf("|Bet:" YELLOW "%7d"RESET" |" , bet);
    }else{
        printf("|"YELLOW "---FOLDED---" RESET "|" , bet);
    }
    gotoxy(xCord, yCord+4);
    printf("+------------+");
    }else{
        gotoxy(xCord, yCord);
        printf(GRAY"+------------+"RESET);
        gotoxy(xCord, yCord+1);
        printf(GRAY"|            |"RESET);
        gotoxy(xCord, yCord+2);
        printf(GRAY"|   "RED"BUSTED"GRAY"   |"RESET);
        gotoxy(xCord, yCord+3);
        printf(GRAY"|            |"RESET);
        gotoxy(xCord, yCord+4);
        printf(GRAY"+------------+"RESET);
    }
}
void cardPrint(int xCord,int yCord, int rank, int suit){
    const char* rankIcon[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K","A"};
    const char* suitIcon[4] = {"♣","♠","♥","♦"};
    if(suit >= 2){
        gotoxy(xCord,yCord);
        printf("┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|"RED"%-2s"RESET"   |",rankIcon[rank]);
        gotoxy(xCord,yCord+2);
        printf("|  "RED"%s"RESET"  |",suitIcon[suit]);
        gotoxy(xCord,yCord+3);;
        printf("|   "RED"%2s"RESET"|",rankIcon[rank]);
        gotoxy(xCord,yCord+4);
        printf("└─────┘");
    }else{
        gotoxy(xCord,yCord);
        printf("┌─────┐");
        gotoxy(xCord,yCord+1);
        printf("|"DARKBLUE"%-2s"RESET"   |",rankIcon[rank]);
        gotoxy(xCord,yCord+2);
        printf("|  "DARKBLUE"%s"RESET"  |",suitIcon[suit]);
        gotoxy(xCord,yCord+3);;
        printf("|   "DARKBLUE"%2s"RESET"|",rankIcon[rank]);
        gotoxy(xCord,yCord+4);
        printf("└─────┘");
    }
}
void drawFrame(GAME *g){
    system("chcp 65001");
    system("cls");
    //bot boxes
    int b1C = g->bots[0].chips;int b2C = g->bots[1].chips;int b3C = g->bots[2].chips;int b4C = g->bots[3].chips;int b5C = g->bots[4].chips;
    int b1B = g->bots[0].bet;int b2B = g->bots[1].bet;int b3B = g->bots[2].bet;int b4B = g->bots[3].bet;int b5B = g->bots[4].bet;
    int b1F = g->bots[0].folded;int b2F = g->bots[1].folded;int b3F = g->bots[2].folded;int b4F = g->bots[3].folded;int b5F = g->bots[4].folded;
    int b1A = g->bots[0].active;int b2A = g->bots[1].active;int b3A = g->bots[2].active;int b4A = g->bots[3].active;int b5A = g->bots[4].active;
    botWindow(1     , 1, "Bot 1", b1C, b1B, 0, b1F, b1A);
    botWindow(1 + 15, 1, "Bot 2", b2C, b2B, 1, b2F, b2A);
    botWindow(1 + 30, 1, "Bot 3", b3C, b3B, 2, b3F, b3A);
    botWindow(1 + 45, 1, "Bot 4", b4C, b4B, 3, b4F, b4A);
    botWindow(1 + 60, 1, "Bot 5", b5C, b5B, 4, b5F, b5A);
    //line segment
    gotoxy(1,6);
    for(int i = 0; i < 74; i ++){
        printf("─");
    }
    //Community Area
    gotoxy(1,7);
    printf("Community Cards");
    gotoxy(1,8);
    int potsize = g->board.pot;
    printf(" > Pot:   "YELLOW"%-4d"RESET, potsize);
    gotoxy(1,9);
    int minbet = g->board.minBet;
    printf(" > MinBet:"YELLOW"%-4d"RESET,minbet);
    gotoxy(65,7);
    int round = g->round;
    printf("Round: %-3d", round);
    //adress the 0/3/4/5 amount of com.cards
    cardPrint(18, 8, 0,0);//Magic Numbers, adress
    cardPrint(18+8, 8, 1,0);//Magic Numbers, adress
    cardPrint(18+16, 8, 2,0);//Magic Numbers, adress
    cardPrint(18+24, 8, 3,0);//Magic Numbers, adress
    cardPrint(18+32, 8, 4,0);//Magic Numbers, adress
    //Player area
    gotoxy(1,14);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┬");}
    }
    printf("\n");
    printf("Player:\n");
    int playerChips = g->player.chips;int playerBet = g->player.bet;
    printf(" > Chips: "YELLOW"%-4d"RESET"\n", playerChips);
    printf(" > Bet:   "YELLOW"%-4d"RESET"\n", playerBet);
    //adress that cards might not exist yet
    cardPrint(29,16, 8,3);//Magic Numbers, adress
    cardPrint(39,16, 8,3);//Magic Numbers, adress
    gotoxy(54,15);
    printf("| Available actions:");
    gotoxy(54,16);
    printf("|  ["CYAN"0"RESET"] Call / Check");
    gotoxy(54,17);
    printf("|  ["CYAN"1"RESET"] Raise");
    gotoxy(54,18);
    printf("|  ["CYAN"2"RESET"] All-In");
    gotoxy(54,19);
    printf("|  ["CYAN"3"RESET"] Fold");
    gotoxy(54,20);
    printf("├────────────────────");
    gotoxy(54,21);
    printf("| Enter choice:");
    gotoxy(54,22);
    printf("┴────────────────────");
    //line segment
    gotoxy(1,22);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┴");}
    }
    //useful info
    gotoxy(1,23);
    //fork evaluate
    printf("Pairs: %d | Three of a kind: %d | Four of a kind: %d | Straight: %d | Flush: %d ",2, 0, 0, 1, 0);//Magic Numbers, adress
    /*
    gotoxy(70,21);
    int x;
    scanf("%d",&x);
    gotoxy(70, 24);
    printf("%d",x);
    */
}
//  TO-DO
//  - Make the window drawing a function
//      - Use GAME *g
//  - Add Linux and MAC support
/*
LINUX version
#include <stdio.h>
#include <stdlib.h>
#include <locale.h> <==
...
int main(void){
    setlocale(LC_ALL, "en_US.UTF-8"); <==
    system("clear"); <==
*/