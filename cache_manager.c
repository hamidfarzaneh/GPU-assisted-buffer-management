#include <stdio.h>
#include "cache_manager.h"

char * accessFile(char * name , int startPoint){
    struct node* temp = search(name);
    char * page_data ; 
    int blockIndex = startPoint/PAGE_SIZE;
    if(temp == NULL){
        // there is no node in the tree related to this file 
        // so we should load the file from disk then add it to cache 
        // so w should create it 
        page_data = loadPageFromDisk(name , blockIndex);        
        int indexOfAddedPage = addPageToTheHashTable(page_data);           
        struct page_id_link_list* newLinkList = createNewPageIDLinkList(name , blockIndex, indexOfAddedPage);
        insert(name , newLinkList); 

    } else {
       
        
        struct page_id_node* page_id_temp_head =  temp->page_id_list->head;
        // printf("^^%d %d^^^" , blockIndex , page_id_temp_head->blockIndex);
        while(page_id_temp_head!=NULL){
            if(page_id_temp_head->blockIndex== blockIndex){
                break;
            } else {
                page_id_temp_head = page_id_temp_head->next;
            }
        }
        if(page_id_temp_head == NULL){
            printf("WTF!?");
            return NULL;
        }
        // printf("$$ %d %d $$ " , page_id_temp_head->id , page_id_temp_head->blockIndex);
        page_data = getPageFromCache(page_id_temp_head->id);
    }

    return page_data;
    
}

char * loadPageFromDisk(char *file_name , int blockIndex){
    int file=0;
    if((file=open(file_name,O_RDONLY)) < -1)
        return NULL;
    char *buffer = (char *) malloc(PAGE_SIZE);
    off_t ret = lseek (file, (off_t) blockIndex*PAGE_SIZE, SEEK_SET);
    if(ret == (off_t) -1){
        return NULL;
    }
    read(file,buffer,PAGE_SIZE);
    return buffer;    
}