#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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
void botFace(int xCord, int yCord,int variant){
   switch(variant){
    case 0:
        gotoxy(xCord,yCord);
        printf("   / ");
        gotoxy(xCord,yCord+1);
        printf("[°  °]");
        gotoxy(xCord,yCord+2);
        printf("  -  ");
        break;
    default:
        break;
   } 
}

int main(void){
    system("chcp 65001");
    system("cls");
    //bot boxes
    botWindow(1     , 1, "Bot 1", 1238, 12, 0, 0, 1);
    botWindow(1 + 15, 1, "Bot 2", 762, 12, 1, 0, 1);
    botWindow(1 + 30, 1, "Bot 3", 873, 12, 2, 1, 0);
    botWindow(1 + 45, 1, "Bot 4", 247, 12, 3, 1, 1);
    botWindow(1 + 60, 1, "Bot 5", 675, 12, 4, 1, 1);
    
    gotoxy(1,6);
    for(int i = 0; i < 74; i ++){
        printf("─");
    }
    gotoxy(1,7);
    printf("Community Cards");
    gotoxy(1,8);
    printf(" > Pot:   "YELLOW"%4d"RESET, 1234);
    gotoxy(1,9);
    printf(" > MinBet:"YELLOW"%-4d"RESET,12);
    gotoxy(65,7);
    printf("Round: %-3d", 5);
    //community cards
    cardPrint(18, 8, 0,0);
    cardPrint(18+8, 8, 1,0);
    cardPrint(18+16, 8, 2,0);
    cardPrint(18+24, 8, 3,0);
    cardPrint(18+32, 8, 4,0);
    //Player area
    gotoxy(1,14);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┬");}
    }
    printf("\n");
    printf("Player:\n");
    printf(" > Chips: "YELLOW"%-4d"RESET"\n", 9999);
    printf(" > Bet:   "YELLOW"%-4d"RESET"\n", 12);
    cardPrint(29,16, 8,3);
    cardPrint(39,16, 8,3);
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
//      gotoxy(70, 21);     User choice place
//      printf("here");
    gotoxy(1,22);
    for(int i = 0; i < 74; i ++){
        if(i != 53){printf("─");}
        else{printf("┴");}
    }
    
    gotoxy(1,23);
    printf("Pairs: %d | Three of a kind: %d | Four of a kind: %d | Straight: %d | Flush: %d ",2, 0, 0, 1, 0);
    
    gotoxy(70,21);
    int x;
    scanf("%d",&x);
    gotoxy(70, 24);
    printf("%d",x);
}