#include <cstddef>
#include<stdlib.h>

#ifndef DAREALTOKEN
#define DAREALTOKEN
#define MAXLENGTH 100
typedef enum{
    IDENTIFIER,
    PLUS,
    SEMICOLON,
    NUMLITERAL,
    UNKNOWN,
    EMPTY,
    EQUAL,
}Lexeme;
typedef struct Token{
    char input[MAXLENGTH];
    Lexeme type;
    int len;
    int finalized;
    struct Token* nextToken;
}Token;



void initToken(Token* token){
    token->len=0;
    token->type=UNKNOWN;
    token->nextToken=NULL;
    token->finalized=0;
}
void freeToken(Token* head){
    Token* hold=head;
    while(hold!=NULL){
        Token* copy=hold->nextToken;
        free(hold);
        hold=copy;
    }
    
}



#endif