#include "binary_tree.h"
//struct for node
struct node *p_root = NULL;

//use typedef to make calling the compare function easier
typedef int (*Compare)(const char *, const char *);

//compares value of the new node against the previous node
int CmpStr(const char *a, const char *b)
{
    return (strcmp (a, b));     // string comparison instead of pointer comparison
}

//inserts elements into the tree
void inner_insert(char* key,struct page_id_link_list* page_id, struct node** leaf, Compare cmp)
{
    int res;
    if( *leaf == NULL ) {
        *leaf = (struct node*) malloc( sizeof( struct node ) );
        (*leaf)->name_value= malloc( strlen (key) +1 );     // memory for key
        strcpy ((*leaf)->name_value, key);                   // copy the key
        (*leaf)->p_left = NULL;
        (*leaf)->p_right = NULL;
        (*leaf)->page_id = page_id;
    } else {
        res = cmp (key, (*leaf)->name_value);
        if( res < 0)
            inner_insert( key,page_id, &(*leaf)->p_left, cmp);
        else if( res > 0)
            inner_insert( key,page_id, &(*leaf)->p_right, cmp);
        else                                            // key already exists
            printf ("Key '%s' already in tree\n", key);
    }
}

void insert(char *key , struct page_id_link_list* page_id ){
    inner_insert(key , page_id ,&p_root , (Compare)CmpStr);
}



//recursive function to print out the tree inorder
void in_order(struct node *root)
{
    if( root != NULL ) {
        in_order(root->p_left);
        printf("   %s\n", root->name_value);     // string type
        in_order(root->p_right);
    }
}


//searches elements in the tree
struct node * inner_search(char* key, struct node* leaf, Compare cmp)  // no need for **
{
    int res;
    if( leaf != NULL ) {
        res = cmp(key, leaf->name_value);
        if( res < 0)
            inner_search( key, leaf->p_left, cmp);
        else if( res > 0)
            inner_search( key, leaf->p_right, cmp);
        else
            return leaf;    // string type
    }
    else printf("\nNot in tree\n");
    return NULL;
}

// this function is called from out . and then this function calls inner serach 
struct node * search(char *key){
    return inner_search(key , p_root ,(Compare) CmpStr );
}

void delete_tree(struct node** leaf)
{
    if( *leaf != NULL ) {
        delete_tree(&(*leaf)->p_left);
        delete_tree(&(*leaf)->p_right);
        free( (*leaf)->name_value);         // free the key
        free( (*leaf) );
    }
}

