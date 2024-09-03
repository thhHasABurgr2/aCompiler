#define TABLESIZE 31
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#ifndef HASHTABLE
#define HASHTABLE

unsigned int hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;
    
    
    while (c = *str++){
        hash = ((hash << 5) + hash) + c; 
    }
    hash %= TABLESIZE;
    return (unsigned int) hash;
       
}



typedef struct Cell{
    char* key;
    unsigned int val;
    struct Cell* nextCell;

}Cell;


void initCell(Cell* cell) {
    cell->key =(char*)malloc(1);
    strcpy(cell->key,"");
    cell->key[0]='\0';
    cell->val = 0;
    cell->nextCell=NULL;
}
// I think Cells should be an array of fixed size (prime num)
// [NULL,2,NULL]

int insert(Cell** cells, char* inp,unsigned int value){
    unsigned int index=hash((unsigned char*)inp);
    Cell* exp= (Cell*)malloc(sizeof(Cell));
    initCell(exp);
    exp->key=(char*)malloc(strlen(inp)+1);
    strcpy(exp->key,inp);
    exp->val=value;
   
    if(cells[index]==NULL){
        cells[index]=exp;
    }else{// cell alr has a pigeon in it
        Cell* bbg=cells[index];
        while(bbg->nextCell!=NULL){
            bbg=bbg->nextCell;
        }
        bbg->nextCell=exp;

    }

}
unsigned int look(Cell** cells,char* keye){
    unsigned int index=hash((unsigned char*) keye);
    Cell* bbg=cells[index];
    if(bbg==NULL){
        return 100;
    }
    while(strcmp(bbg->key,keye)!=0){
        bbg=cells[index]->nextCell;
        if(bbg->nextCell==NULL){
            return 200;
        }
    }

    return bbg->val;
    

}
void freeCells(Cell** cells){
    for(int i=0; i<TABLESIZE;i++){
        while(cells[i]!= NULL){
            Cell* ce=cells[i]->nextCell;
            free(cells[i]);
            cells[i]=ce;
        }
    }
    free(cells);
}
unsigned int compare(Cell** cells,char* inp){
    
    for(int i=0;i<TABLESIZE;i++){
        Cell* bbg=cells[i];
        while(bbg!=NULL){
            if(strcmp(cells[i]->key,inp)!=0){
                return 1;
            }
            bbg=bbg->nextCell;
        }
    }
    return -1;


}
#endif