#ifndef TEXTCOLOR_H
#define TEXTCOLOR_H

#define BLUE "\033[34m" //0
#define RED "\e[0;31m" //1
//bot colors
#define CYAN "\e[0;36m"    //0
#define MAGENTA "\e[0;35m" //1
#define GREEN "\e[0;32m"   //2
      //red from above     //3
#define BYELLOW "\e[0;93m" //4

#define RESET "\033[0m"
void ColPrintf(char* str,int colorChoice);
void ColPrintfPlus(char* str, int num, int colornum);
void ColPrintfBot(char* str, int clrChoice);
#endif