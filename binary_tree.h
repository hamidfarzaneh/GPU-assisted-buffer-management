#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_id_node.h"

struct node {
    char *name_value;          
    struct page_id_link_list* page_id_list; 
    struct node *p_left;
    struct node *p_right;
};


//inserts elements into the tree
struct node * search(char* key);  // no need for **

void insert(char *key , struct page_id_link_list* page_id );