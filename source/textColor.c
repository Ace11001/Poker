#include <stdio.h>
#define BLUE "\033[34m" //0
#define RED "\e[0;31m" //1
#define RESET "\033[0m"

void ColPrintf(char* str,int colorChoice){
    switch(colorChoice){
        case 0:
            printf(BLUE"%s",str);
            printf(RESET);        
            break;
        case 1:
            printf(RED"%s",str);
            printf(RESET);        
            break;
        //more colors to be added
        default:
            printf("%s",str);
    }
}
void ColPrintfPlus(char* str, int num, int colornum){//str must include a format specifyer %d!
    char Temp[64];
    snprintf(Temp,sizeof(Temp),str,num);
    ColPrintf(Temp,colornum);
}
/*
    char DEBUGplayerScore[64];
    snprintf(DEBUGplayerScore, sizeof(DEBUGplayerScore), "Player Hand result: %d\n", evaluatedPlayer);
    char DEBUGbot1Score[64];
    snprintf(DEBUGbot1Score, sizeof(DEBUGbot1Score), "Bot 1 Hand result: %d\n", evaluatedBot1);
    ColorfulPrintf(DEBUGplayerScore,0);
    ColorfulPrintf(DEBUGbot1Score, 0);
*/