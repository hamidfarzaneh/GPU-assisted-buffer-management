#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>
#include "cache_manager.c"

#define REQUEST_COUNT 5000

int main(int argc , char ** argv){
    int cacheQueueCapacity = 1000;
    int hashTableCapacity = 3000;
    
    printf("creating a cache queue with %d size \n" , cacheQueueCapacity);
    printf("creating hashtable with %d size " , hashTable);

    LRU_cache_init(cacheQueueCapacity , hashTableCapacity);
    
    FILE * fp ;
    char * line ;
    size_t len = 0;
    int lineCount = 1;
    fp = fopen("READ_REQUESTS.txt" , "r");
    if(fp == NULL){
        printf("Request file not found!");
    } else {
        while((len= getline(&line , &len ,fp)!=-1)){
            printf("running line %d of %d\n" , lineCount++ , REQUEST_COUNT);
            printf("%s\n" , line);
        }

    }
    return 0 ;
}

void runCommand(char * commandLine){
    
}

