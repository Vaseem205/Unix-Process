/*

Using signals you can control the execution of processes

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int main(){

    int pid = fork();

    if(pid==-1){
        return 2;
    }

    if(pid==0){
        while(1){
            printf("Performing operation\n");
            usleep(50000);
        }
    }else{
        kill(pid, SIGSTOP);                     // stopping the child process
        int time;
        do{
            printf("How long you want the child process to execute (in secs): ");
            scanf("%d", &time);
            if(time>0){
                kill(pid, SIGCONT); 
                sleep(time);
                kill(pid, SIGSTOP);
            }
        }while(time>0);

        kill(pid, SIGKILL);                     // if the user input is "0", it'll kill the child process.
        wait(NULL);
    }

    return 0;
}

/*

OUTPUT:
How long you want the child process to execute (in secs): 1
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
Performing operation
How long you want the child process to execute (in secs): 0



*/