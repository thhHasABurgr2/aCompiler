#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#ifndef TOKEN_H
#define TOKEN_H
typedef enum{
    q0,//start state
    q1,//on letter; can self loop, go to number, or go to identifier accepting state
    q2,// on number; can self loop, can go to letter(if num is not the first char in token), if neither it has too possibilities: number literal(if num is the first char in token) and identifier accepting statesif num is not the first char in token
    q3,// identifier accepting state
    q4,// plus accepting state
    q5, // semicolon accepting state
    q6,// num literal accepting state

    q8,//= accpeting state
    qerror,//dont recognize
    INVALID,
}states;

typedef enum{
    IDENTIFIER,
    PLUS,
    SEMICOLON,
    NUMLITERAL,
    UNKNOWN,
    EMPTY,
    EQUAL,
    KEYWORD,
}Lexeme;
typedef struct Token{
    char* input;
    Lexeme type;
    int len;
    int finalized;
    states currentState;
    struct Token* nextToken;

}Token;

void initToken(Token* token){
    token->input=(char*)malloc(1);
    token->input[0]='\0';
    token->len=0;
    token->type=UNKNOWN;
    token->nextToken=NULL;
    token->finalized=0;
    token->currentState=q0;
}
void resizeToken(Token* token){
    token->input=(char*)realloc(token->input,token->len+8);
}
void appendCharToToken(Token* tokens,char nextc){
    tokens->input[tokens->len]=nextc;
    if(tokens->len>sizeof(tokens)){
        resizeToken(tokens);
    } 
    tokens->input++;
    tokens->input[tokens->len]='\0';
}
void printToken(Token* token,FILE* OUT) {
    Token* cpy=token;
    while(cpy!=NULL){
        fprintf(OUT,"Token: %s (Type: %d)\n", cpy->input, cpy->type);
        cpy=cpy->nextToken;
    }
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