#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_id_node.h"
#include "descriptions.h"

struct node {
    char *name_value;          
    int page_id; 
    struct node *p_left;
    struct node *p_right;
};
struct node *p_root = NULL;

//use typedef to make calling the compare function easier
typedef int (*Compare)(const char *, const char *);

//inserts elements into the tree
void insert(char* key,struct page_id_link_list* page_id, struct node** leaf, Compare cmp);
