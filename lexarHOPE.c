/*
regex mayb?:
only escape sequence im going to process is ;
letter = 'A'|...|'Z'|'a'|...|'z'
digit  = '0'|'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'
number = digit digit*
identifier = letter (letter|digit)*
operator = '='
keyword = '+'|'-'|'*'|'/'|'='
escape sign = ';'
openPar='('
closePar=')'
statement = identifier operator identifier keyword 
closedStatement= openPar statement closedPar



*/
#include<stdio.h>
#include<stdlib.h>
#include "token.h"




int main(int argc,char* argv[]){
    int countChar=0;
    FILE* ptr;

   
    lines Lines;
    initLines(&Lines);

    line* Line=NULL;
    

    
 

    ptr=fopen("exe.toyYEHE","r");
    if(NULL==ptr){
        printf("file cant be open sadge");
    }

    while (countChar != EOF){
        
        countChar=getc(ptr);


        if (countChar == ' '){
            continue;
        }else if(countChar=='\n'){
            if(Line==NULL){
                continue;
            }
            if(Line!=NULL){
                appendLine(&Lines,Line);
            }


            Line=(line*)malloc(sizeof(line));
        }else{
            if(Line != NULL){
                appendChar(Line,countChar);

            }else{
                Line=(line*)malloc(sizeof(line));
                initLine(Line);
                appendChar(Line,countChar);
            }
        }   
    }
    sortLine(Lines.stuff[0]);
    
    freeLines(&Lines);
    

    fclose(ptr);

}