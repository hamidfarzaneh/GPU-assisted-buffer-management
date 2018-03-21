#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "binary_tree.h"
#include "LRU.h"
#define PAGE_SIZE 4096 
char * loadPageFromDisk(char *file_name , int startPoint);
char * accessFile(char * name , int blockIndex);