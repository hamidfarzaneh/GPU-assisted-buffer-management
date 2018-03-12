#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "binary_tree.h"
#include "LRU.h"

char * accessFile(char * name , int startPoint){
    struct node* temp = search(name);
    char * page_data ; 
    if(temp == NULL){
        // there is no node in the tree related to this file 
        // so we should load the file from disk then add it to cache 
        // so we should create it 
        
        addPageToTheHashTable(page_data);           
    }

    return page_data;
    
}

char * loadPageFromDisk(char *file_name , int startPoint){
    int f_write = open("start.txt", O_RDONLY);
}