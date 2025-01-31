/*

We can communicate  between process using Signals.asm

Impletation:

1. Parent process asks user input.
2. If user takes more than 5 seconds, the child process will send "SIGUSR1" signal. 
3. We gonna handle that signal "SIGUSR1" with sigaction where we redirect the the signal behaviour
    to execute our handler function. 

*/

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>


int x = 0;

void handleSIGUSR1(int sig){
    if(x==0){
        printf("\nHINT: Bro type  15\n");
    }
}

int main(){

    int pid = fork();


    if(pid==-1){
        return 2;
    }

    if(pid==0){
        while(1){
            sleep(5);
            kill(getppid(), SIGUSR1);       // getppid() cuz, we have to send signal to the parent process
        }
    }else{

        struct sigaction sa = {0};      // init to 0
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handleSIGUSR1;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is 3 x 5: ");
        scanf("%d", &x);
        if(x==15){
            printf("Right!\n");
            kill(getpid(), SIGKILL);
        }else{
            printf("Wrong!\n");
            kill(getpid(), SIGKILL);
        }
    }

    wait(NULL);
    return 0;
}

/*

OUTPUT: 

vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ ./13
What is 3 x 5: 
HINT: Bro type  15
15
Right!
Killed



*/