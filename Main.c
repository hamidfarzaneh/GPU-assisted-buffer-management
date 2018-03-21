#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>
#include "cache_manager.h"

#define REQUEST_COUNT 5000

void runCommand(char * commandLine);
int main(int argc , char ** argv){
    int cacheQueueCapacity = 1000;
    int hashTableCapacity = 3000;
    
    printf("creating a cache queue with %d size \n" , cacheQueueCapacity);
    printf("creating hashtable with %d size " , hashTableCapacity);

    LRU_cache_init(cacheQueueCapacity , hashTableCapacity);
    
    FILE * fp ;
    char * line ;
    size_t len = 0;
    //int lineCount = 1;
    fp = fopen("READ_REQUESTS.txt" , "r");
    if(fp == NULL){
        printf("Request file not found!");
    } else {
        while((len= getline(&line , &len ,fp)!=-1)){
            // printf("running line %d of %d\n" , lineCount++ , REQUEST_COUNT);
            runCommand(line);
        }

    }
    getchar();
    return 0 ;
}

void runCommand(char * commandLine){
    char * fileName ;
    char * command ;
    char * startPoint ; 
    fileName = strsep(&commandLine , " ");
    command = strsep(&commandLine , " ");
    startPoint = strsep(&commandLine , " ");

    printf("\n%s %s %s" , fileName , command , startPoint);
    if(strcmp(command,"read")==0){
        // printf("reading ...\n");
        accessFile(fileName , atoi(startPoint));
    } else if (strcmp(command, "write") == 0){
        printf("writing ... ");
    }
}

