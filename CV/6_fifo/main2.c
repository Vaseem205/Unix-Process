#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main(void){

    int arr[5];

    int fd = open("sum", O_RDONLY);                     //keep the name of the file descriptor same (i.e. sum)
    if(fd==-1){
        return 1;
    }

    for(int i=0; i<5; i++){
        if(read(fd, &arr[i], sizeof(int))==-1){
            return 2;
        }
        printf("Read it from sum (a fifo): %d\n", arr[i]);
    }
    close(fd);


    return 0;
}



/*

OUTPUT:

Terminal 1 = ./main1.c
Terminal 2 = ./main2.c

*/