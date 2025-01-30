#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

    int pid = fork();

    if(pid==-1){
        return 1;
    }

    if(pid==0){
        printf("Iniside Child Process\n");
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);       // O_WRONLY | O_CREAT -> These values are in octal and it exanpands to: 01 | 0100 => 0101, this creates the file if it does not exist and write on it
        if(file==-1){
            printf("Failed to create a file\n");
            return 2;
        }
        printf("File descriptor of recetly created file: %d\n", file);
        fflush(stdout);                                                     // otherise the above printf statement wont get executed (check below NOTE)
        dup2(file, 1);                                                      // changing the file fd to STDOUT fd
        close(file);                                                        // closing the "file" cuz we dont need another fd of same file
        
        //execlp("file_to_calll", "command", "args_1", "args_2",....., NULL);
        int err = execlp("ping", "ping", "-c", "2", "google.com", NULL);              // don't forget to add NULL at the end (cmd: pinging google.com 5 times)

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

OUTPUT:
Iniside Child Process
File descriptor of recetly created file: 3


Successfully completed Child Process Execution
Iniside Parent Process
More Logical Computation can be Done here



NOTE:

It also cretes the "pingResults.txt" and writes the result of "ping" in that file:
    PING google.com(maa03s35-in-x0e.1e100.net (2404:6800:4007:813::200e)) 56 data bytes
    64 bytes from maa03s35-in-x0e.1e100.net (2404:6800:4007:813::200e): icmp_seq=1 ttl=118 time=9.05 ms
    64 bytes from maa03s35-in-x0e.1e100.net (2404:6800:4007:813::200e): icmp_seq=2 ttl=118 time=9.45 ms

    --- google.com ping statistics ---
    2 packets transmitted, 2 received, 0% packet loss, time 1001ms
    rtt min/avg/max/mdev = 9.046/9.250/9.454/0.204 ms



*/