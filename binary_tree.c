#include "binary_tree.h"
//struct for node
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
void insert(char* key,struct page_id_link_list* page_id, struct node** leaf, Compare cmp)
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
            insert( key,page_id, &(*leaf)->p_left, cmp);
        else if( res > 0)
            insert( key,page_id, &(*leaf)->p_right, cmp);
        else                                            // key already exists
            printf ("Key '%s' already in tree\n", key);
    }
}

//compares value of the new node against the previous node
int CmpStr(const char *a, const char *b)
{
    return (strcmp (a, b));     // string comparison instead of pointer comparison
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
struct node * search(char* key, struct node* leaf, Compare cmp)  // no need for **
{
    int res;
    if( leaf != NULL ) {
        res = cmp(key, leaf->name_value);
        if( res < 0)
            search( key, leaf->p_left, cmp);
        else if( res > 0)
            search( key, leaf->p_right, cmp);
        else
            return leaf;    // string type
    }
    else printf("\nNot in tree\n");
    return NULL;
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


// int main()
// {
//     char *temp1 = "test.txt";
//     char *temp2 = "laskfjs.jpg";
//     char *temp3 = "aflksdjf.mp3";
//     insert(temp1,  &p_root, (Compare)CmpStr);
//     insert(temp2,  &p_root, (Compare)CmpStr);
//     insert(temp3,  &p_root, (Compare)CmpStr);

//     struct node * t = search(temp1, p_root, (Compare)CmpStr);     // no need for **
//     in_order(p_root);
//     printf("%s" , t->value);
//     return 0;
// }