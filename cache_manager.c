#include <stdio.h>
#include "cache_manager.h"

char * accessFile(char * name , int startPoint){
    struct node* temp = search(name);
    char * page_data ; 
    if(temp == NULL){
        // there is no node in the tree related to this file 
        // so we should load the file from disk then add it to cache 
        // so we should create it 
        page_data = loadPageFromDisk(name , startPoint);        
        int indexOfAddedPage = addPageToTheHashTable(page_data);           
        struct page_id_link_list* newLinkList = createNewPageIDLinkList(name , startPoint , indexOfAddedPage);
        insert(name , newLinkList); 
    } else {
        struct page_id_node* page_id_temp_head =  temp->page_id->head;
        while(page_id_temp_head!=NULL){
            if(page_id_temp_head->page_address_start == startPoint){
                break;
            } else {
                page_id_temp_head = page_id_temp_head->next;
            }
        }
        if(page_id_temp_head == NULL){
            printf("WTF!?");
            return NULL;
        }
        page_data = getPageFromCache(page_id_temp_head->id);

    }

    return page_data;
    
}

char * loadPageFromDisk(char *file_name , int startPoint){
    int file=0;
    if((file=open(file_name,O_RDONLY)) < -1)
        return NULL;
    char *buffer = (char *) malloc(PAGE_SIZE);
    off_t ret = lseek (file, (off_t) startPoint, SEEK_SET);
    if(ret == (off_t) -1){
        return NULL;
    }
    read(file,buffer,PAGE_SIZE);
    return buffer;    
}