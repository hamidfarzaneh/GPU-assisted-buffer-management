#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_id_node.h"

struct page_id_link_list* createNewPageIDLinkList(char* name , int startPointOfFile,int page_id){
    struct page_id_link_list* newLinkList = (struct page_id_link_list *) malloc(sizeof(struct page_id_link_list));
    struct page_id_node* newNode = (struct page_id_node*) malloc(sizeof(struct page_id_node));
    newNode->name_value = (char *) malloc(strlen(name) + 1);
    strcpy(newNode->name_value , name);
    newNode->page_address_start = startPointOfFile ; 
    newNode->id = page_id;
    newNode->next = NULL;
    newLinkList->head = newLinkList->tail = newNode;
    return newLinkList;
}

void addNewElementToALinkList(struct page_id_link_list** linklist , struct page_id_node* newElement){
    if((*linklist)->head == NULL){
        (*linklist)->head = (*linklist)->tail = newElement;
    } else {
        (*linklist)->tail->next = newElement ;
        (*linklist)->tail = newElement;

    }
}
