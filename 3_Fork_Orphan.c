/*

The parent process does not systematically take care of its children. In the following example, we will force the child process to sleep for 1 second before ending,
but let the parent terminate right away:

*/

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
    pid_t pid;

    pid = fork();

    if(pid==-1){
        return(EXIT_FAILURE);
    }

    if(pid==0){
        printf("This is child executing\n");
        sleep(1);
        printf("\nChild Done!\n");
    }else if(pid>0){
        printf("This is parent executing\n");
        printf("Parent Done!\n");
    }

    return 0;
}

/*

OUTPUT:
Our command prompt returns before the child process is even terminated.
This is because our shell is only waiting for our parent process (shell's child) to finish.
It doesn’t know or care about our program’s child process (shell's grand-child). In a case like this,
when the parent finished without waiting for its child, the child becomes an orphan process.
It is then adopted by init (child's PPID becomes 1) and is quickly eliminated from the system.

NOTE: This thing won't happen if we use wait() in parent processes.

*/