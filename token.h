#define MAXLENGTH 25
#include<stdlib.h>
#include<stdio.h>
#ifndef TOKEN_H
#define TOKEN_H
typedef struct {
    char stuff[MAXLENGTH];
    int len;
} line;
void initLine(line* Line){
    Line->len=0;
}
void appendChar(line* Line,int countChar){
    Line->stuff[Line->len]=countChar;
    Line->len++;
    Line->stuff[Line->len]='\0';
}
// lines stuff
typedef struct {
    line* stuff[MAXLENGTH];
    int len;
} lines;
void initLines(lines* Lines){
    Lines->len=0;
}
void appendLine(lines* Lines,line* Line){
    Lines->stuff[Lines->len]=Line;
    Lines->len++;
}
void freeLines(lines* Lines){
    for (int i = 0; i < Lines->len; i++) {
        free(Lines->stuff[i]);
    }
}
//token stuff now
typedef enum{
    INDENTIFIER,
    PLUS,
    SEMICOLON,
    NUMLITERAL,
}TokenType;
typedef struct{
    char input[MAXLENGTH];
    TokenType type;
    int len;
}Token;

typedef struct{
    Token* input[MAXLENGTH];
    int len;
 
}Tokens;

void initToken(Token* token){
    token->len=0;
    token->type=INDENTIFIER;
}
void initTokens(Tokens* tokens){
    tokens->len=0;
}
//check stuff
int isDigit(int input){
    if (input<=57 &&input>=48){
        return 1;
    }
    return 0;
}
int isLetter(int input){
    if ((input>=65 && input <=90) || (input >= 97 && input <=122)){
        return 1;
    }
    return 0;
}
int isPlus(int input){
    if (input == 43){
        return 1;
    }
    return 0;
}
int isSemicolon(int input){
    if (input == 59){
        return 1;
    }
    return 0;
}
int isFirstNum(Token* token){
    char inp=token->input[0];
    if(isDigit((int)inp)){
        return 1;
    }
    return 0;

}
void freeTokens(Tokens* tokens){
    for (int i = 0; i < tokens->len; i++) {
        free(tokens->input[i]);
    }
}
void Appendtoken(Tokens* tokens,Token* token){
    tokens->input[tokens->len]=token;
    tokens->len++;
}
typedef enum{
    q0,//start state
    q1,//on letter; can self loop, go to number, or go to identifier accepting state
    q2,// on number; can self loop, can go to letter(if num is not the first char in token), if neither it has too possibilities: number literal(if num is the first char in token) and identifier accepting statesif num is not the first char in token
    q3,// identifier accepting state
    q4,// plus accepting state
    q5, // semicolon accepting state
    q6,// num literal accepting state
    qerror,//dont recognize
}states;




void printToken(Token* token) {
    printf("Token: %s (Type: %d)\n", token->input, token->type);

}

#endif