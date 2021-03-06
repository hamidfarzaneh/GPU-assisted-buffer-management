#include "LRU.h"
#include <stdlib.h>

int stackArray[MAX_STACK_SIZE] ;
int biggestID= 0 ;
int stackPointer = 0;

int getAvailableIDForHashTable(){
    if(stackPointer>0){
        return stackArray[--stackPointer];
    } else {
        return biggestID++;
    }
    
}
void addIDToStack(int inputID){
    stackArray[stackPointer++] = inputID;
}



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
    addIDToStack(temp->page_id);
    free(temp->data);
    free(temp);
    queue->filledFramesCount--;
    
}


void putAPageToTheRearOfTheQueue(Queue * queue ,Qnode* requestedPage){
    
    if(requestedPage->prev !=NULL){
        requestedPage->prev->next = requestedPage -> next ;
    }
    
    if(requestedPage->next != NULL){ // if next of current page is not null
        requestedPage->next->prev = requestedPage->prev ;
    }
    
    if(requestedPage == queue->rear){
        if(requestedPage->prev != NULL){
            queue->rear = requestedPage->prev ; 
            queue->rear->next = NULL;
        }
    }
    requestedPage->next = queue->front ;
    requestedPage->prev = NULL;
    requestedPage->next->prev = requestedPage ;

    queue->front =requestedPage ; 
}

int addPageToTheHashTable(char * page_data){
    int page_id = getAvailableIDForHashTable();
    Qnode * temp = hashTable->array[page_id] ; 
    if(temp != NULL){
        printf("OH NO! there is a conflict , the page already exists!\n");
        return -1 ;
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

    return page_id;
    
}
char * getPageFromCache(int page_id){
    
    Qnode* requestedPage= hashTable->array[page_id] ;
    if(requestedPage == NULL){
        // CACHE MISS!!!
        // get the data from disk!
        // it should not come here , but if it comes?!
        printf("WTF???!!!!");
        return NULL;

    } else {
        // put the page to the rear of the cache 
        if(requestedPage == NULL){
            printf("veeeeey");
        }
        putAPageToTheRearOfTheQueue(pageQueue , requestedPage);

        return requestedPage->data;


    }
}

void LRU_cache_init(int queueCapacity , int hashTableCapacity){
    pageQueue = createQueue(queueCapacity);
    hashTable = createHashTable(hashTableCapacity);
}