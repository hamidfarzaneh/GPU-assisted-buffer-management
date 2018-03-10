#include <stdio.h>
#include <stdlib.h>
#define PAGE_SIZE 4096

// A Qnode 
typedef struct Qnode{
    char data[PAGE_SIZE] ; // the chunk of the buffer . 
    unsigned int pageNumber ;
}Qnode ;

typedef struct Queue {
    unsigned int filledFramesCount;
    unsigned int numberOfFrames ;
    Qnode *front , *rear ;
}Queue;

typedef struct Hash {
    int capacity ;
    Qnode ** array ;

} Hash ;

Qnode* createQueue(int numberOfFrames){
    
}