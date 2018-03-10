#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc , char ** argv){
    char * buffer = (char *) malloc (1000);
    int fileDes = open("./temp/tempfile" , O_RDONLY);

    return 0 ;
}

int readPageFromFile(int fd, char *buffer){
    return read(fd , buffer , PAGE_SIZE);
}