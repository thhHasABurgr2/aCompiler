
#ifndef LINE_H
#define LINE_H
#include<stdlib.h>

typedef struct Line {
    char* stuff;
    int len;
    struct Line* nextLine;
}Line;


void initLine(Line* line){
    line->len=0;
    line->nextLine=NULL;
    line->stuff=(char*)malloc(1);
    line->stuff[0]='\0';
}
void resizeLine(Line* line){
    line->stuff=(char*)realloc(line->stuff,line->len+8);
}
void appendCharToLine(Line* line,char countChar){
    line->stuff[line->len]=countChar;
    if(line->len >sizeof(line->stuff)){
        resizeLine(line);
    }
    line->len++;
    
    line->stuff[line->len]='\0';
    
    
}
void printLines(Line* lines){
    Line* cpy=lines;
    while(cpy!=NULL){
        printf("%s",cpy->stuff);
        cpy=cpy->nextLine;
    }
}
void freeLines(Line* head){
    Line* hold=head;
    while(hold!=NULL){
        Line* copy=hold->nextLine;
        free(hold);
        hold=copy;
    }
}
#endif