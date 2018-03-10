#include <stdio.h>
#include <stdlib.h>
#define PAGE_SIZE 4096

// A Qnode 
typedef struct Qnode{
    char data[PAGE_SIZE] ; // the chunk of the buffer . 
    struct Qnode* next;
    struct Qnode* prev;
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

Qnode* createQueueNode(int pageNumber){
    Qnode* newNode = (Qnode *) malloc(sizeof(Qnode));
    newNode->next = newNode->prev = NULL;
    newNode->pageNumber = pageNumber;
    return newNode ;
}

Queue* createQueue(int numberOfFrames){
    Queue* newQueue = (Queue *) malloc(sizeof(Queue));
    newQueue->filledFramesCount = 0;
    newQueue->front = newQueue->rear = NULL;
    newQueue->numberOfFrames = numberOfFrames;
    return newQueue ;
}

Hash * createHash(int capacity){
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
    free(temp);
    queue->filledFramesCount--;
    
}

void Enqueue (Queue* queue ,Hash * hashTable , unsigned pageNumber){
    //if all frames are full , remove the page at the rear 
    if(AreAllFramesFull(queue)){
        // remove page from hash
        hashTable->array[queue->rear->pageNumber] = NULL;
        dequeue(queue);
    }
    // create a new node with given page number ,
    // And add the new node to the front of queue 
    Qnode* temp = createQueueNode(pageNumber);
    temp->next = queue->front;

    if(isQueueEmpty(queue)){
        queue->rear = queue->front = temp ;
    } else {
        queue->front->prev = temp ;
        queue->front = temp ;
    }
    // add page entry to hash also 
    hashTable->array[pageNumber] = temp ;
    queue->filledFramesCount++;


}

void ReferencePage(Queue * queue ,Hash* hashTable , unsigned pageNumber){
    Qnode* requestedPage = hashTable->array[pageNumber];
   
    if(requestedPage == NULL){
        Enqueue(queue , hashTable , pageNumber);
    // page is there , but not at the front 
    } else if (requestedPage != queue->front){
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

}

int main()
{
    // Let cache can hold 4 pages
    Queue* q = createQueue( 4 );
 
    // Let 10 different pages can be requested (pages to be
    // referenced are numbered from 0 to 9
    Hash* hash = createHash( 10 );
 
    // // Let us refer pages 1, 2, 3, 1, 4, 5
    ReferencePage( q, hash, 1);
    printf ("%d ", q->front->pageNumber);
    ReferencePage( q, hash, 3);
    ReferencePage( q, hash, 3);
    ReferencePage( q, hash, 1);
    ReferencePage( q, hash, 4);
    ReferencePage( q, hash, 5);
 
 
    return 0;
}