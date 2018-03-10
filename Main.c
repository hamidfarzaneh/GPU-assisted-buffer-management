#include <stdio.h>
#include <unistd.h> 

int PAGE_SIZE ;
int main(int argc , char ** argv){

	sysconf(_SC_PAGESIZE);
    PAGE_SIZE = sysconf(_SC_PAGE_SIZE);
    printf("current page size %d Bytes\n" , PAGE_SIZE);
    char * myBufferPtr = " Greetings , Professor Falken .\ n " ;

    printf("%016p\n" , &(myBufferPtr));
    return 0 ;
}