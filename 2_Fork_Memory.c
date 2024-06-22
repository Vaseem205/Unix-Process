/*

MEMORY DUPLICATED BUT NOT SHARED

As we’ve seen, a child process is an exact copy of its parent process. When a child is created,
it is identical to its parent in every way. It has the same code, the same open file descriptors,
the same data stored in memory, etc. But the fact that this memory is identical does not mean it is shared between the two processes.
If the parent process changes the value of one of its variables after creating the child, the child process will not see any change when it reads the same variable.


+-----------------+          +-----------------+
| Parent Process  |   fork   | Child Process   |
| Code:      C    +--------->| Code:      C    |
| File Desc: F    |          | File Desc: F    |
| Memory:    M    |          | Memory:    M    |
|   - X: 10       |          |   - X: 10       |
+-----------------+          +-----------------+

   Parent modifies X to 20

+-----------------+          +-----------------+
| Parent Process  |          | Child Process   |
| Code:      C    |          | Code:      C    |
| File Desc: F    |          | File Desc: F    |
| Memory:    M    |          | Memory:    M    |
|   - X: 20       |          |   - X: 10       |
+-----------------+          +-----------------+

Parent Process:

Label: "Parent Process"
Components:
    Code (C)
    Open File Descriptors (F)
    Memory (M) with a variable X with value 10.
    Child Process Creation:

Label: "Child Process"
Components:
    Identical Code (C)
    Identical Open File Descriptors (F)
    Identical Memory (M) with variable X with value 10.
    Separate Memory:

Show an action where the parent process changes the variable X from 10 to 20.
Illustrate that the child’s memory remains unchanged (X still equals 10).


*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

//Child Process Routine
void child_process_routine(int pid, int *x){
    printf("Child Process: PID = %d\n", pid);
    printf("Child Process: Value of X = %d\n", *x);
}

//Parent Process Routine
void parent_process_routine(int pid, int *x){
    printf("Parent Process: PID = %d\n", pid);
    printf("Parent Process: Value of X = %d\n", *x);
    *x = *x*2;
    printf("Parent Process: Value of X = %d\n", *x);
}

int main(void){
    pid_t pid;
    int X = 4;

    printf("Before fork(): Value of X = %d\n", X);

    pid = fork();

    if(pid==-1){
        return(EXIT_FAILURE);
    }
    if(pid==0){
        child_process_routine(pid, &X);
    }else if(pid>0){
        parent_process_routine(pid, &X);
    }

    return 0;

}

/*

OUTPUT:
Here, after the child process’ creation, the parent doubles the value of the given number using a memory address pointer.
But the child prints the number’s original value, unaware of the parent’s modification.

*/