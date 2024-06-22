/*

In order to execute another program within ours or to execute part of our program simultaneously, it can often be very useful to create child processes.

The operating system manages all processes and allocates a memory zone to each of them. Each has its own stack, its own heap, its own instruction pointer, etc.

So processes are organized in a hierarchy, with:
a. parent processes that create child processes,
b. child processes that are created by their parent process and can in turn create child processes of their own.

For example, when we input a command into the shell like ls, the shell creates a child process whose job it is to execute the ls program.
If the shell executed the ls program directly without first creating a child, the shell process would be overwritten by the ls program and
we wouldn’t be able to continue using our shell…

*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void){

    pid_t pid;

    printf("Fork Here.\n");

    pid = fork();

    if(pid==-1){
        perror("Fork failed");
        return 1;
    }

    printf("Fork Successful.\n");

    if(pid==0){
        printf("Child: I'm the child, my internal pid is %d.\n", pid);
    }else if(pid>0){
        printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
    }

    return 0;
}

/*

OUTPUT:

Fork Here.
Fork Successful.
Parent: I'm the parent, my child's pid is 119416.
Fork Successful.
Child: I'm the child, my internal pid is 0.

-----------------------------------------------------

Q. Why Fork Successful was printed twice?
When the fork() system call is executed(ln. 11), it creates a new process by duplicating the calling process.
The new process, known as the child process, is an almost exact copy of the parent process.
Both processes continue executing the same code after the fork() system call.

                       +---------------------+
                       |      Main Process   |
                       +---------------------+
                                   |
                                   | (print "Fork Here.")
                                   |
                       +---------------------+
                       |    pid = fork();    |
                       +---------------------+
                                   |
              +--------------------------------------------+
              |                                            |
+---------------------------+               +---------------------------+
|     Parent Process        |               |     Child Process         |
+---------------------------+               +---------------------------+
|                           |               |                           |
| (print "Fork Successful.")|               | (print "Fork Successful.")|
|                           |               |                           |
| (print "Parent: ...")     |               | (print "Child: ...")      |
| pid = child's PID         |               | pid = 0                   |
|                           |               |                           |
+---------------------------+               +---------------------------+

Here, parent process completes its execution first, then it gives control to child process. The child process start executing the same code as parent process,
its just that child process start executing after fork(). (This things changes if wait() and exit() is implemented)


Q.There is a difference of pid from parent pov and childs pov?
1. child pid is 119416, in parent pov, this is because parent has multiple child and it needs to identify and manage (this even helps in tracing back child towards parent, we can see which process created this pid using this pid that is unique)
2. child pid is 0, in child pov. this is to confirm it is child


*/