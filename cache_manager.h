#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "binary_tree.h"
#include "LRU.h"
char * loadPageFromDisk(char *file_name , int startPoint);