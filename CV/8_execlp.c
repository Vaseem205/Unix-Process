/*

execlp() -> It enables you to run another program from within your C program. And, it never returns.

That means, if you had any code below execlp(), it wont get executed. 


Ex:

int main(){

    execlp(...,...,...,...);
    printf("Success\n")
    retunr 0;
}

"Success" wont get printed, as the program calls execlp() first and execlp() never returns.
To solve this, we can use fork() and call execlp() inside child process. We wait in parent process 
till child process completes its execution and we do other computation in parent process.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
int main(){

    int pid = fork();

    if(pid==-1){
        return 1;
    }

    if(pid==0){
        printf("Iniside Child Process\n");
        fflush(stdout);                                             // otherise the above printf statement wont get executed (check below NOTE)
        
        //execlp("file_to_calll", "command", "args_1", "args_2",....., NULL);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);      // don't forget to add NULL at the end (cmd: pinging google.com 5 times)
    }else{
        wait(NULL);                                                 // wait for the child process to complete its execution
        printf("--------------------------------------------------------------------------------------------------\n");
        printf("Iniside Parent Process\n");
        printf("More Logical Computation can be Done here\n");
    }

    return 0;
}

*/

/*

OUTPUT:
Iniside Child Process
PING google.com(maa05s26-in-x0e.1e100.net (2404:6800:4007:821::200e)) 56 data bytes
64 bytes from maa05s26-in-x0e.1e100.net (2404:6800:4007:821::200e): icmp_seq=1 ttl=59 time=13.1 ms
64 bytes from maa05s26-in-x0e.1e100.net (2404:6800:4007:821::200e): icmp_seq=2 ttl=59 time=11.4 ms
64 bytes from maa05s26-in-x0e.1e100.net (2404:6800:4007:821::200e): icmp_seq=3 ttl=59 time=10.8 ms
64 bytes from maa05s26-in-x0e.1e100.net (2404:6800:4007:821::200e): icmp_seq=4 ttl=59 time=10.4 ms
64 bytes from maa05s26-in-x0e.1e100.net (2404:6800:4007:821::200e): icmp_seq=5 ttl=59 time=10.3 ms

--- google.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 4004ms
rtt min/avg/max/mdev = 10.348/11.202/13.071/1.012 ms
--------------------------------------------------------------------------------------------------
Iniside Parent Process
More Logical Computation can be Done here



NOTE:

why fflush(stdout) ?
    - The printf() writes to the stdout buffer
    - Before the buffer gets flushed (which would actually print the content), execlp() is called
    - execlp() replaces the entire process image with the new program (ping in this case)
    - When this replacement happens, the unflushed buffers are discarded
    - As a result, the printf content never makes it to the terminal

*/


int main(){

    int pid = fork();

    if(pid==-1){
        return 1;
    }

    if(pid==0){
        printf("Iniside Child Process\n");
        fflush(stdout);                                                     // otherise the above printf statement wont get executed (check below NOTE)
        
        //execlp("file_to_calll", "command", "args_1", "args_2",....., NULL);
        int err = execlp("pingr", "ping", "-c", "2", "google.con", NULL);              // don't forget to add NULL at the end (cmd: pinging google.com 5 times)

        if(err == -1){
            printf("Could not find program to execute\n");
            return 3;
        }

    }else{
        printf("\n\n");
        int waitStatus;                                                     // wait() retruns the child process's exit status (the child process which recently finished its execution)
        wait(&waitStatus);                                                  // wait for the child process to complete its execution
        if(WIFEXITED(waitStatus)){                                          // WIFEXITED -> WaitIfExited(): It'll get the exit status of child process
            int statusCode = WEXITSTATUS(waitStatus);                       // storing the child exit status into statusCode       
            if(statusCode == 0){
                printf("Successfully completed Child Process Execution\n");
            }else{
                printf("Failed Child Process Execution With Code: %d\n", statusCode);
            }
        }
        printf("Iniside Parent Process\n");
        printf("More Logical Computation can be Done here\n");
    }

    return 0;
}


/*

------------------------------------------------------------------------------------------------------
1. For proper command: execlp("ping", "ping", "-c", "2", "google.com", NULL)
OUTPUT:
    Iniside Child Process
    PING google.com(maa03s34-in-x0e.1e100.net (2404:6800:4007:806::200e)) 56 data bytes
    64 bytes from maa03s34-in-x0e.1e100.net (2404:6800:4007:806::200e): icmp_seq=1 ttl=59 time=12.0 ms
    64 bytes from maa03s34-in-x0e.1e100.net (2404:6800:4007:806::200e): icmp_seq=2 ttl=59 time=12.4 ms

    --- google.com ping statistics ---
    2 packets transmitted, 2 received, 0% packet loss, time 1001ms
    rtt min/avg/max/mdev = 11.986/12.207/12.429/0.221 ms


    Successfully completed Child Process Execution
    Iniside Parent Process
    More Logical Computation can be Done here
-------------------------------------------------------------------------------------------------------
2. For improper command: execlp("pingr", "ping", "-c", "2", "google.com", NULL)
OUTPUT:
    Iniside Child Process
    Could not find program to execute


    Failed Child Process Execution With Code: 3
    Iniside Parent Process
    More Logical Computation can be Done here
--------------------------------------------------------------------------------------------------------

NOTE:

WIFEXITED(status):
    It checks if a child process terminated normally (i.e., by calling exit() or returning from main). 
    It returns true (non-zero) if the process ended normally, and false (zero) otherwise.

WEXITSTATUS(status):
    It extracts the actual exit code that the child process returned when it terminated. 
    
Important: You should only use WEXITSTATUS if WIFEXITED returns true, otherwise the result is undefined.


*/