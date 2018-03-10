#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>


#define PAGE_SIZE 4096
#define QUEUE_SIZE 1000
#define SUPPORTED_PAGE_COUNT_TO_SAVE 1000000

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


Qnode* createQueueNode(int page_id, char * page_data ){
    Qnode* newNode = (Qnode *) malloc(sizeof(Qnode));
    newNode->next = newNode->prev = NULL;
    newNode->page_id= page_id;
    newNode->data = page_data;
    return newNode ;
}

Queue* createQueue(int numberOfFrames){
    Queue* newQueue = (Queue *) malloc(sizeof(Queue));
    newQueue->filledFramesCount = 0;
    newQueue->front = newQueue->rear = NULL;
    newQueue->numberOfFrames = numberOfFrames;
    return newQueue ;
}

Hash * createHashTable(int capacity){
    Hash* newHashTable = (Hash*) malloc(sizeof(Hash));
    newHashTable->array = (Qnode **) malloc(sizeof(Qnode*) * capacity);

    for(int i=0 ; i < capacity ; i++){
        newHashTable->array[i] = NULL;
    }

    return newHashTable ;
}

int AreAllFramesFull(Queue * queue){
    return queue->filledFramesCount == queue->numberOfFrames;
}

int isQueueEmpty(Queue * queue){
    return queue->rear == NULL;
}

void dequeue(Queue* queue){
    if(isQueueEmpty(queue)){
        return ;
    } 
    if(queue->rear == queue->front){
        // there is only one element in the queue
        queue-> front = NULL;
    }
    Qnode* temp = queue->rear ;
    queue->rear =queue->rear->prev;
    if(queue->rear)
        queue->rear->next = NULL;
    free(temp->data);
    free(temp);
    queue->filledFramesCount--;
    
}


void putAPageToTheRearOfTheQueue(Queue * queue ,Qnode* requestedPage){
    requestedPage->prev->next = requestedPage -> next ;
    if(requestedPage->next){
        requestedPage->next->prev = requestedPage->prev ;
    }
    if(requestedPage == queue->rear){
        queue->rear = requestedPage->prev ; 
        queue->rear->next = NULL;
    }
    requestedPage->next = queue->front ;
    requestedPage->prev = NULL;
    requestedPage->next->prev = requestedPage ;

    queue->front =requestedPage ; 

}

void addPageToTheHashTable(int page_id ,char * page_data){
    Qnode * temp = hashTable->array[page_id] ; 
    if(temp != NULL){
        printf("OH NO! there is a conflict , the page already exists!\n");
        return ;
    } else {
        temp = createQueueNode(page_id , page_data);
        hashTable->array[page_id] = temp; 
    }
    if(AreAllFramesFull(pageQueue)){
        // remove least recently used page from queue 
        hashTable->array[pageQueue->rear->page_id] = NULL;
        dequeue(pageQueue);
    }
    // create a new node with given page number ,
    // And add the new node to the front of queue 
    temp->next = pageQueue->front;

    if(isQueueEmpty(pageQueue)){
        pageQueue->rear = pageQueue->front = temp ;
    } else {
        pageQueue->front->prev = temp ;
        pageQueue->front = temp ;
    }
    // add page entry to hash also 
    hashTable->array[page_id] = temp ;
    pageQueue->filledFramesCount++;
    
}
char * getPageFromCache(int page_id){
    Qnode* requestedPage= hashTable->array[page_id] ;
    if(requestedPage == NULL){
        // CACHE MISS!!!
        // get the data from disk!

        return NULL;

    } else {
        // put the page to the rear of the cache 
        putAPageToTheRearOfTheQueue(pageQueue , requestedPage);
        return requestedPage->data;


    }
}
int main()
{
    // Let cache can hold 4 pages
    //char * buffer[PAGE_SIZE] ; 

    pageQueue = createQueue( QUEUE_SIZE );
    hashTable = createHashTable( SUPPORTED_PAGE_COUNT_TO_SAVE);
    

    int n;
    MD5_CTX c;
    char buf[512];
    ssize_t bytes;
    unsigned char out[MD5_DIGEST_LENGTH];

    MD5_Init(&c);
    
    int fileDes = open("./temp/tempfile" , O_RDONLY);
    char * temp = "tempfile";
    strcpy(buf,temp);
        MD5_Update(&c, buf, bytes);

    MD5_Final(out, &c);

    for(n=0; n<MD5_DIGEST_LENGTH; n++)
        printf("%02x", out[n]);
    printf("\n");
    

 
 
    return 0;
}