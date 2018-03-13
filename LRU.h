#define PAGE_SIZE 4096
#define QUEUE_SIZE 1000
#define SUPPORTED_PAGE_COUNT_TO_SAVE 1000000
#define MAX_STACK_SIZE 1000
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>


int stackArray[MAX_STACK_SIZE] ;
int biggestID= 0 ;
int stackPointer = 0;
// A Qnode 
typedef struct Qnode{
    char* data ; // the chunk of the buffer . 
    struct Qnode* next;
    struct Qnode* prev;
    unsigned int page_id ;
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

Queue* pageQueue ;
Hash* hashTable ;

int addPageToTheHashTable(char * page_data);
char * getPageFromCache(int page_id);
void LRU_cache_init(int queueCapacity , int hashTableCapacity);