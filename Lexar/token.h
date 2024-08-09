#define MAXLENGTH 25
#include<stdlib.h>
#include<stdio.h>
#ifndef TOKEN_H
#define TOKEN_H
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
int isEqual(int input){
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