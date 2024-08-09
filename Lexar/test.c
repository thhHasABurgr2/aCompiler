#include<stdio.h>
#include<stdlib.h>
#include "token.h"
#include<string.h>
int main(void){


    Line* line=(Line*)malloc(sizeof(Line));
    initLine(line);
    char* ELLO="yb+;";
    for(int i=0;i <strlen(ELLO);i++){
        appendChar(line,(int)ELLO[i]);
    }
    Token* token=makeTokens(line);
    printToken(token);
    
}