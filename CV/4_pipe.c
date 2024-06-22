/*
pipe() -> It is used for inter-process communication

Steps to implement pipe:
1. Create an array of size 2 (i.e. file descriptor -> this is used to read and write from the file [i.e. stdin, stdout]). Ex: int fd[2].
   We had an array of size 2 cuz, the pipe had 2 ends.
   fd[0] -> READ
   fd[1] -> WRITE
2. Then fork() it.


Implementation:
1. We gonna take input from child process.
2. Write it in the fd[1] (this happens in child process itself).
3. Read the given input using fd[0] (this happens in parent process).
4. Print the read number.
*/


/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

    //Step-1
    int fd[2];

    if(pipe(fd)==-1){
        printf("Error while opening a pipe\n");
        return 1;
    }

    //Step-2
    int id = fork();

    if(id==0){
        close(fd[0]);                                       //closing read-end to avoid anamoly
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));                      //writing x's value in fd[1]
        close(fd[1]);                                       //closing write-end after written
    }else{
        close(fd[1]);                                       //closing write-end to avoid anamoly
        int y;
        read(fd[0], &y, sizeof(int));                       //reading fd[0]'s value and storing it in y
        close(fd[0]);                                       //closing read-end after being read
        printf("Number given by child process: %d\n", y);     
    }

    return 0;

}


// OUTPUT:
// Enter a number: 42                           -> happened in child_process
// Number given by child process: 42            -> happened in parent_process

*/





//Added some extra lines to check the error condn (this helps in debugging whenver an error occurs)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

    //Step-1
    int fd[2];

    if(pipe(fd)==-1){
        printf("Error while opening a pipe\n");
        return 1;
    }

    //Step-2
    int id = fork();
    if(id==-1){
        printf("Error while forking\n");
        return 2;
    }

    if(id==0){
        close(fd[0]);                                       //closing read-end to avoid anamoly
        int x;
        printf("Enter a number: ");
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int))==-1){              //writing x's value in fd[1]
            printf("Error while writing in a pipe\n");
            return 3;
        }                      
        close(fd[1]);                                       //closing write-end after written
    }else{
        close(fd[1]);                                       //closing write-end to avoid anamoly
        int y;
        if(read(fd[0], &y, sizeof(int))==-1){               //reading fd[0]'s value and storing it in y
            printf("Error while read from a pipe\n");
            return 4;
        }                      
        close(fd[0]);                                       //closing read-end after being read
        printf("Number given by child process: %d\n", y);     
    }

    return 0;

}


