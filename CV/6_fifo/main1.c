/*

In the directory in which write and read programs are created, do the following:

-> mkfifo sum

NOTE:

It'll create a fifo named "sum"

The implementation would be as follows:

1. main1.c will open the created fifo "sum" in write_only mode and write some value in it.
2. main2.c will open the created fifo "sum" in read_only mode and read value from it
    (the values written by main1.c will be read in main2.c)

*/



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

/*

int main(void){

    int arr[5];
    int i;
    srand(time(NULL));                      //without this, rand() will generate same random number everytime it runs
    for(i = 0; i<5; i++){
        arr[i] = rand()%10;
    }

    int fd = open("sum", O_WRONLY);
    if(fd==-1){
        return 1;
    }

    for(i=0; i<5; i++){
        if(write(fd, &arr[i], sizeof(int))==-1){
            return 2;
        }
        printf("Write in sum (a fifo): %d\n", arr[i]);
    }
    close(fd);

    return 0;
}
*/

/*

OUTPUT:

Terminal 1 = ./main1.c
Terminal 2 = ./main2.c

*/

int main(){

    int arr[5];
    srand(time(NULL));

    int fd = open("sum", O_WRONLY);
    if(fd==-1){
        printf("Failed to open fifo");
        return 1;
    }
    
    for(int i = 0; i < 5; i++){
        arr[i] = rand()%100;
        if(write(fd, &arr[i], sizeof(int))==-1){
            printf("Failed to write in fifo");
            return 2;
        }
        printf("Write in sum (a fifo): %d\n", arr[i]);
    }
    close(fd);

    return 0;
}