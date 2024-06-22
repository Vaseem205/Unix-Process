/*

A child process that has finished its task but stays on the process table is known as ZOMBIE process.
This zombie process is waiting for its parent to clean up the traces of it from process table.
The system will already have freed its resources (code, data, execution stack) but saved its process control block and its PID in Process Table.
That entry is not deleted by the parent.

PROCESS TABLE:
+-----+-------------------------+
| PID |  Process Control Block  |
+-----+-------------------------+
|     |                         |
+-----+-------------------------+
|     |                         |
+-----+-------------------------+
|     |                         |
+-----+-------------------------+

i.e. CHILD is DEAD, but its ALIVE as its entry is still present in Process Table.


*/


#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0)
    {
        printf("Child: I'm the child, my internal pid is %d.\n", pid);
        printf("Child: Done!\n"); //child is done executing
    }
    else if (pid > 0)
    {
        printf("Parent: I'm the parent, my child's pid is %d.\n", pid);
        while (1) // Infinite loop, the parent will never end, hence it doesn't acknowledge that child execution is over.
            usleep(1);
    }
    return (0);
}

/*

OUTPUT:

TERMINAL 1: ./a.aout
Parent: I'm the parent, my child's pid is 246592.
Child: I'm the child, my internal pid is 0.
Child: Done!

TERMINAL 2: ps aux | grep <type_child's_pid_here> | grep Z+
vaseem    246592  0.0  0.0      0     0 pts/0    Z+   19:14   0:00 [a.out] <defunct>

NOTE: 
    • vaseem: The username of the user who owns the process. 
    • 246592: The process ID (PID) of the process. 
    • 0.0 0.0: The CPU and memory usage of the process, which is negligible in this case. 
    • 0 0: Additional information about the process, such as the process group ID and session ID. 
    • pts/0: The terminal or pseudo-terminal where the process is running. 
    • Z+: The process state, where Z indicates a "zombie" process, and + indicates that it is in the foreground process group. 
    • 19:14: The time when the process was started. 
    • 0:00: The CPU time consumed by the process. 
    • [a.out]: The name of the process, which appears to be an executable named a.out. 
    • <defunct>: An indication that the process is a "defunct" or "zombie" process, which means that the process has completed execution, but its parent process has not yet waited for or collected its exit status.


Another Explanation:
Child_Process has exited and resources allocated to Child_Process has de-allocated.
BUT, its entry in Process Table is still present (cuz, it was parent duty to erase Child_Process traces after it exits,
and this did not happen cuz, Parent_Process did not call wait()). So such a process whose entry is still in the Process Table,
but it actually is terminated, then this process is called as ZOMBIE.

WHAT HAPPENS TO ZOMBIE PROCESS?
1. Eventually even the Parent_Process exits, which will lead ZOMBIE process become ORPHAN.
2. The ORPHAN process (initially ZOMBIE) will get adopted (re-parenting) by init_process with PID=1.

*/
