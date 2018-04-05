// it's just a link list
struct page_id_node{
    char *name_value ; 
    int blockIndex ;   
    int id;

    struct page_id_node* next;

};
struct page_id_link_list{
    struct page_id_node* head ;
    struct page_id_node* tail;
};

struct page_id_link_list* createNewPageIDLinkList(char* name , int startPointOfFile,int page_id);
void addNewElementToALinkList(struct page_id_link_list** linklist , struct page_id_node* newElement);