#define MAXLENGTH 25
#include<stdlib.h>
#include<stdio.h>
#ifndef TOKEN_H
#define TOKEN_H
typedef struct {
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
<<<<<<< HEAD
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
=======


//atp i dont know if I even need a max length, but fuck it we ball
void freeLines(Line* head){
    Line* hold=head;
    while(hold!=NULL){
        Line* copy=hold->nextLine;
        free(hold);
        hold=copy;
>>>>>>> 86ae948 (some struct issues)
    }
}
//token stuff now
typedef enum{
<<<<<<< HEAD
    INDENTIFIER,
    PLUS,
    SEMICOLON,
    NUMLITERAL,
}TokenType;
=======
    IDENTIFIER,
    PLUS,
    SEMICOLON,
    NUMLITERAL,
    UNKNOWN,
    EMPTY
}Type;
>>>>>>> 86ae948 (some struct issues)
typedef struct{
    char input[MAXLENGTH];
    Type type;
    int len;
    int finalized;
    struct Token* nextToken;
}Token;

<<<<<<< HEAD
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
=======


void initToken(Token* token){
    token->len=0;
    token->type=UNKNOWN;
    token->nextToken=NULL;
    token->finalized=0;
>>>>>>> 86ae948 (some struct issues)
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
<<<<<<< HEAD
void freeTokens(Tokens* tokens){
    for (int i = 0; i < tokens->len; i++) {
        free(tokens->input[i]);
    }
}
void Appendtoken(Tokens* tokens,Token* token){
    tokens->input[tokens->len]=token;
    tokens->len++;
}
=======
void freeTokens(Token* head){
    Token* hold=head;
    while(hold!=NULL){
        Token* copy=hold->nextToken;
        free(hold);
        hold=copy;
    }
}

>>>>>>> 86ae948 (some struct issues)
typedef enum{
    q0,//start state
    q1,//on letter; can self loop, go to number, or go to identifier accepting state
    q2,// on number; can self loop, can go to letter(if num is not the first char in token), if neither it has too possibilities: number literal(if num is the first char in token) and identifier accepting statesif num is not the first char in token
    q3,// identifier accepting state
    q4,// plus accepting state
    q5, // semicolon accepting state
    q6,// num literal accepting state
    q7,// state for an empty input
    qerror,//dont recognize
}states;
<<<<<<< HEAD




void printToken(Token* token) {
    printf("Token: %s (Type: %d)\n", token->input, token->type);

=======




void printToken(Token* token) {
    printf("Token: %s (Type: %d)\n", token->input, token->type);

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
        
        if(nextc=='\0' && token->finalized){
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

                }else{
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
              
                token->type=IDENTIFIER;
                token->finalized=1;
                if(nextc!='\0'){
                 
                    Token* hold;
                    hold=(Token*)malloc(sizeof(Token));
                    initToken(hold);
                    token->nextToken=hold;
                    token = hold;
                }
                break;
            case(q4):
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
                token->type=EMPTY;
                token->finalized=1;
                break;

            case(qerror):
                printf("inputted bad char");
                freeTokens(&token1);
                token1=NULL;
                exit(1);
                break;


            
        
        
        }
        
    
    }
    return token1;
>>>>>>> 86ae948 (some struct issues)
}

#endif