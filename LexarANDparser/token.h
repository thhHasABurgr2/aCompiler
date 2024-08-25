#define MAXLENGTH 25
#define NUMSTATES 11
#include<stdlib.h>
#include<stdio.h>
#ifndef TOKEN_H
#define TOKEN_H
/*
q0:q1,q2,q3,q4,q5,q6,q7
q1:q1,q2,q3
q2:q1,q2,q3,q6
q3:q0
q4:q0
q5:q0
q6:q0
q7:q0
qerror:NULL



*/
typedef struct Line {
    char stuff[MAXLENGTH];
    int len;
    struct Line* nextLine;
}Line;


void initLine(Line* line){
    line->len=0;
    line->nextLine=NULL;
}
void appendChar(Line* Line,int countChar){
    Line->stuff[Line->len]=countChar;
    Line->len++;
    Line->stuff[Line->len]='\0';
}
// lines stuff


//atp i dont know if I even need a max length, but fuck it we ball
void freeLines(Line* head){
    Line* hold=head;
    while(hold!=NULL){
        Line* copy=hold->nextLine;
        free(hold);
        hold=copy;
    }
}
//token stuff now
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

//check stuff
int isDigit(char input){
    if (input<=57 &&input>=48){
        return 1;
    }
    return 0;
}
int isLetter(char input){
    if ((input>=65 && input <=90) || (input >= 97 && input <=122)){
        return 1;
    }
    return 0;
}
int isPlus(char input){
    if (input == 43){
        return 1;
    }
    return 0;
}
int isSemicolon(char input){
    if (input == 59){
        return 1;
    }
    return 0;
}
int isEqual(char input){
    if (input == 61){
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
void freeToken(Token* head){
    Token* hold=head;
    while(hold!=NULL){
        Token* copy=hold->nextToken;
        free(hold);
        hold=copy;
    }
    
}



typedef enum{
    q0,//start state
    q1,//on letter; can self loop, go to number, or go to identifier accepting state
    q2,// on number; can self loop, can go to letter(if num is not the first char in token), if neither it has too possibilities: number literal(if num is the first char in token) and identifier accepting statesif num is not the first char in token
    q3,// identifier accepting state
    q4,// plus accepting state
    q5, // semicolon accepting state
    q6,// num literal accepting state
    q7,// state for an empty input
    q8,//= accpeting state
    qerror,//dont recognize
}states;

typedef struct deltaCell{
    states vert;//determines func
    states hori;// our actual state
    void (*deltaFunc)(char* nextChar,struct deltaCell* pos,Token* token);
    
}deltaCell;
void q0q0(char* nextc, deltaCell* mouse,Token* token){
    // this is for the transition q0->q2->any
    if(isDigit(*nextc)){
        mouse->vert=q2;
        mouse->deltaFunc=q1q0;
        appendCharToToken(token,*nextc);
    }else if (isLetter(*nextc))
    {
        mouse->vert=q1;
        appendCharToToken(token,*nextc);
    }else if (isEqual(*nextc)){       
        mouse->vert=q8;
        appendCharToToken(token,*nextc);
    }else if (isPlus(*nextc)){
        mouse->vert=q4;
        appendCharToToken(token,*nextc);
    }else if (isSemicolon(*nextc)){
        mouse->vert=q5;
        appendCharToToken(token,*nextc);
    }
    
}
deltaCell* stateTable[11][11];
// lazy alloc? so the stateTable will be filled at the same time mouse is calling a func
void lazyInit(deltaCell* stateTable[11][11], void(*deltaFunc)(char nextc, deltaCell* pos,Token* token) ){
    
}
Token* mouseRUN(Line* line){
    Token* token1;
    token1=(Token*)malloc(sizeof(Token));
    initToken(token1);
    Token* token=token1;
    char* tracker=line->stuff;
    char nextc=*tracker; 
    states state = q0;
    
    deltaCell* mouse =(deltaCell*)malloc(sizeof(deltaCell));
    stateTable[q0][q0]=(deltaCell*)malloc(sizeof(deltaCell));
    stateTable[q0][q0]->vert=q0;
    stateTable[q0][q0]->hori=q0;
    stateTable[q0][q0]->deltaFunc=q0q0;
    mouse=stateTable[q0][q0];
    
    
  


    while(nextc!='\0'&& token->finalized != 1){
        mouse->deltaFunc(nextc,mouse,token);

    }
}
/*

q0 q1 q2 q3 q4 -outp ofdeltafunc?

q1 q1 q2 q4 NULL - reaason why this is null is that u cant go from q1->q4

q2 q1 q2 q4 NULL - same reason as q1's but there's a prob. What 8f the sequence is q0->q2->q1. that doessnt work
-one way to fix would be that q2's q1 is diff than q1's self loop;
- so like q0->q2 and deltaFunc has a var that tracks token->input to see
q3

q4
-mouse cell

*/


void printToken(Token* token,FILE* OUT) {
    Token* cpy=token;
    while(cpy!=NULL){
        fprintf(OUT,"Token: %s (Type: %d)\n", cpy->input, cpy->type);
        cpy=cpy->nextToken;
    }
    

}

void appendCharToToken(Token* tokens,char nextc){
    tokens->input[tokens->len]=nextc; 
    tokens->input[tokens->len+1]='\0';
    tokens->len++;

}

Token* makeTokens(Line* line){
    Token* token1;
    token1=(Token*)malloc(sizeof(Token));
    initToken(token1);
    Token* token=token1;
    char* tracker=line->stuff;
    int nextc=*tracker; 
    states state = q0;
    int B;

    while(1){
        
        if(nextc=='\0' && token->finalized==1){
            break;
        }
        
            
            
            
        
        switch(state){
            case(q0):
                if(isLetter(nextc)){
                    state=q1;
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }else if(isDigit(nextc)){
                    state=q2;
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }else if(isPlus(nextc)){
                    state=q4;
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;  
                }else if(isSemicolon(nextc)){
                    state=q5;
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }else if(nextc=='\0'){
                    state=q7;

                }else if(isEqual(nextc)){
                    state=q8;
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }
                else{
                    state=qerror;
                }
               
                break;
            case(q1):
                if(isLetter(nextc)){
                    
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }else if(isDigit(nextc)){
                    state=q2;
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }else if(isSemicolon(nextc)){
                    state=q3;
                    
                }else if(isPlus(nextc)){
                    state=q3;
                }else if(nextc=='\0'){
                    state=q3;
                }else if(isEqual(nextc)){
                    state=q8;
                }else{
                    state=qerror;
                }
                
                break;

            case(q2):
                B=isFirstNum(token);
                if(isLetter(nextc)){
                    if(B==0){
                        state=q1;
                        appendCharToToken(token,nextc);
                        tracker++;
                        nextc=*tracker;
                    }else{
                        state=q6;

                    }
                }else if(isDigit(nextc)){
                    
                    appendCharToToken(token,nextc);
                    tracker++;
                    nextc=*tracker;
                }else if(isSemicolon(nextc)){
                    if(B==1){
                        state=q6;
                    }else{
                        state=q3;
                    }
                    
                }else if(isPlus(nextc)){
                    if(B==1){
                        state=q6;
                    }else{
                        state=q3;
                    }
                }else if(isEqual(nextc)){
                    if(B==1){
                        state=q6;
                    }else{
                        state=q3;
                    }
                }else if(nextc=='\0'){
                    if(B==1){
                        state=q6;
                    }else{
                        state=q3;
                    }
                
                }else{
                    state=qerror;
                }
                break;
              
            case(q3):
                state=q0;
                token->type=IDENTIFIER;
                token->finalized=1;
               
                if(nextc!='\0'){
                   
                    
                    token->nextToken=(Token*)malloc(sizeof(Token));
                    initToken(token->nextToken);
                    token=token->nextToken;
                }
                break;
            case(q4):
                state=q0;
                token->type=PLUS;
                token->finalized=1;
                if(nextc!='\0'){
                 
                    Token* hold;
                    hold=(Token*)malloc(sizeof(Token));
                    initToken(hold);
                    token->nextToken=hold;
                    token = hold;
                }
                break;
                


            case(q5):
                state=q0;
                token->type=SEMICOLON;
                token->finalized=1;
                if(nextc!='\0'){
                 
                    Token* hold;
                    hold=(Token*)malloc(sizeof(Token));
                    initToken(hold);
                    token->nextToken=hold;
                    token = hold;
                }
                break;


            case(q6):
                state=q0;
                token->type=NUMLITERAL;
                token->finalized=1;
                if(nextc!='\0'){
                 
                    Token* hold;
                    hold=(Token*)malloc(sizeof(Token));
                    initToken(hold);
                    token->nextToken=hold;
                    token = hold;
                }
                break;
            case(q7):
                state=q0;
                token->type=EMPTY;
                token->finalized=1;
                break;
            case(q8):
                state=q0;
                token->type=EQUAL;
                
                token->finalized=1;
                if(nextc!='\0'){
                 
                    Token* hold;
                    hold=(Token*)malloc(sizeof(Token));
                    initToken(hold);
                    token->nextToken=hold;
                    token = hold;
                }
                break;
               


            case(qerror):
                printf("inputted bad char: %c",nextc);
                freeToken(token1);
                token1=NULL;
                exit(1);
                break;


            
        
        
        }
        
        
    
    }
    return token1;
}

#endif