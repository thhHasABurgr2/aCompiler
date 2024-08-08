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

   
    Line* daHead;
    daHead=(Line*)malloc(sizeof(Line));
    initLines(&daHead);

    Line* line=daHead;
    

    
 

    ptr=fopen("exe.toyYEHE","r");
    if(NULL==ptr){
        printf("file cant be open sadge");
    }

    while (countChar != EOF){
        
        countChar=getc(ptr);


        if (countChar == ' '){
            continue;
        }else if(countChar=='\n'){
            if(line==NULL){
                continue;
            }
            if(line!=NULL){
                Line* hold;
                hold=(Line*)malloc(sizeof(Line));
                initLine(hold);
                line->nextLine=hold;
                line = hold;
                
            }
            



        }else{
            if(line != NULL){
                appendChar(line,countChar);

            }else{
                line=(Line*)malloc(sizeof(Line));
                initLine(line);
                appendChar(line,countChar);
            }
        }   
    }
   
    
        
    
    while(daHead!=NULL){
        for(int i=0;i<daHead->len;i++){
            printf("%c",daHead->stuff[i]);
        }
        Line* copy=daHead->nextLine;
        daHead=copy;
    }
    freeLines(daHead);
    

    fclose(ptr);

}