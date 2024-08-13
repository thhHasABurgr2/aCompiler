#define TABLESIZE 5
#include<stdlib.h>
#ifndef HASHTABLE
#define HASHTABLE

unsigned int hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++){
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % TABLESIZE;
       
}



typedef struct Cell{
    char* key;
    unsigned long val;
    struct Cell* nextCell;

}Cell;


void initCell(Cell* cell) {
    cell->key = "";
    cell->val = 0;
    cell->nextCell=NULL;
}
// I think Cells should be an array of fixed size (prime num)
// [NULL,2,NULL]

int insert(Cell** cells, char* inp){
    unsigned int index=hash((unsigned char*)inp);
    Cell* exp= (Cell*)malloc(sizeof(Cell));
    initCell(exp);
    exp->key=inp;
    exp->val=index;
   
    if(cells[index]==NULL){
        cells[index]=exp;
    }else{// cell alr has a pigeon in it
        return -1;
    }

}
int look(Cell** cells,char* keye){
    return cells[hash((unsigned char*) keye)]->val;

}
#endif