#ifndef TEXTCOLOR_H
#define TEXTCOLOR_H

#define BLUE "\033[34m" // 0
#define RED "\e[0;31m" // 1
#define RESET "\033[0m"

void ColPrintf(char* str,int colorChoice);
void ColPrintfPlus(char* str, int num, int colornum);
#endif