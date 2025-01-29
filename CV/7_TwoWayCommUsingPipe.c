/*

Two-Way Communication using Pipes, how?

Parent_process  writes to   parent_pipe -> parent_pipe[1]
Child_process   reads from  parent_pipe -> parent_pipe[0]
Child_process   writes to   child_pipe  -> child_pipe[1]
Parent_process  reads from  child_pipe  -> child_pipe[0]

*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int main(){
    int child_pipe[2];
    int parent_pipe[2];


    if(pipe(child_pipe)==-1){return 1;}
    if(pipe(parent_pipe)==-1){return 2;}

    srand(time(NULL));

    int pid = fork();
    if(pid ==-1){return 3;}

    if(pid==0){
        close(child_pipe[0]);
        close(parent_pipe[1]);

        int x;

        if(read(parent_pipe[0], &x, sizeof(x))==-1){
            printf("read failed in child\n");
            return 4;
        }
        x *= 5;
        if(write(child_pipe[1], &x, sizeof(x))==-1){
            printf("write failed in child\n");
            return 5;
        }

        close(child_pipe[0]);
        close(parent_pipe[1]);
    }else{
        close(child_pipe[1]);
        close(parent_pipe[0]);

        int y = rand()%100;

        if(write(parent_pipe[1], &y, sizeof(y))==-1){
            printf("read failed in parent\n");
            return 4;
        }

        if(read(child_pipe[0], &y, sizeof(y))==-1){
            printf("write failed in parent\n");
            return 5;
        }

        printf("Result: %d\n", y);

        close(child_pipe[1]);
        close(parent_pipe[0]);

    }

    return 0;
}