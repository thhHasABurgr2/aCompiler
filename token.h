#define MAXLENGTH 25
#include<stdlib.h>
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
typedef enum{
    INDENTIFIER,
    PLUS,
    SEMICOLON,
    NUMLITERAL,
}TokenType;
void printTokens(Tokens* tokens) {
    for (int i = 0; i < tokens->len; i++) {
        printf("Token %d: %s (Type: %d)\n", i, tokens->input[i]->input, tokens->input[i]->type);
    }
}

void sortLine(line* Line){
    int count=0;
    states state=q0;
    int character=Line->stuff[count];
    Tokens tokens;
    initTokens(&tokens);
    Token* token=NULL;
    while (1){
       
        character = (count < Line->len) ? Line->stuff[count] : '\0';
        if (character == '\0') {
        if (token != NULL) {
           
            switch (state) {
                case q3:
                    token->type = INDENTIFIER;
                    break;
                case q4:
                    token->type = PLUS;
                    break;
                case q5:
                    token->type = SEMICOLON;
                    break;
                case q6:
                    token->type = NUMLITERAL;
                    break;
                default:
                    free(token);
                    token = NULL;
                    break;
            }
            if (token != NULL) {
                Appendtoken(&tokens, token);
            }
            token = NULL;
        }
        break; // End of input
    }

       

       
        switch (state){
            
            case q0:
                if (isDigit(character)){
                    state = q2;
                    token = (Token*)malloc(sizeof(Token));
                    initToken(token);
                    token->input[0] = character;
                    token->input[1] = '\0';  
                    token->len++;
                    
                }else if (isPlus(character)){
                    state = q4;
                    token = (Token*)malloc(sizeof(Token));
                    initToken(token);
                    token->input[0] = character;
                    token->input[1] = '\0';  
                    token->len++;
                    
                }else if(isLetter(character)){
                    state = q1;
                    token = (Token*)malloc(sizeof(Token));
                    initToken(token);
                    token->input[0] = character;
                    token->input[1] = '\0';  
                    token->len++;
                   
                }else if(isSemicolon(character)){
                    state = q5;
                    token = (Token*)malloc(sizeof(Token));
                    initToken(token);
                    token->input[0] = character;
                    token->input[1] = '\0';  
                    token->len++;
                 
                }
                else{
                    state=qerror;
                    
                }
                break;
            case q1:
                if(isLetter(character)){
                    token->input[token->len]=character;
                    token->input[token->len+1]='\0';
                    token->len++;
                    
                }
                if(isDigit(character)){
                    state=q2;
                    token->input[token->len]=character;
                    token->input[token->len+1]='\0';
                    token->len++;
                   
                }else if(isPlus(character)==1 || isSemicolon(character)==1){
                    state=q3;

                }else{
                    state=qerror;
                }
                
                break;

            case q2:
                int res=isFirstNum(token);
                if(isDigit(character)){
                    token->input[token->len]=character;
                    token->input[token->len+1]='\0';
                    token->len++;
                    

                }
                if(isLetter(character)&&res!=1){
                    state=q1;
                    token->input[token->len]=character;
                    token->input[token->len+1]='\0';
                    token->len++;
                    
                    

                }else{
                    if (isPlus(character)==1||isSemicolon(character)==1)
                    {
                        if (res==1)
                        {
                            state=q6;
                            token->input[token->len]=character;
                            token->input[token->len+1]='\0';
                            token->len++;
                           
                        }else{
                            state=q3;
                            token->input[token->len]=character;
                            token->input[token->len+1]='\0';
                            token->len++;
                            
                            
                        }
                        
                    }else{
                        state=qerror;
                    }
                    

                }
                
                break;

            case q3:

                token->type=INDENTIFIER;
                Appendtoken(&tokens,token);
                //add anything else for accepting states?
                break;
            case q4:

                token->type=PLUS;
                Appendtoken(&tokens,token);
                //add anything else for accepting states?
                break;
            case q5:
                token->type=SEMICOLON;
                Appendtoken(&tokens,token);
                //add anything else for accepting states?
                break;
            case q6:
                token->type=NUMLITERAL;
                Appendtoken(&tokens,token);
                //add anything else for accepting states?
                break;
            case qerror:
                fputs("U dumbass u gave me a char that wasn't supported go f yourself",stderr);
                freeTokens(&tokens);

                exit(1);
                break;
            default:
                state=qerror;
                break;

        }if(character=='\0'){
            break;
        }
        

  
    

        
        count++;


   
}
 printTokens(&tokens);
 freeTokens(&tokens);

}
#endif