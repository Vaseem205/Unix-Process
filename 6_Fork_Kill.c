/*

kill(): It is used to kill our child process if we so desire. To do so, we need to use the kill function of the <signal.h> library
to send a signal to the child process that will force it to terminate immediately.

SYNTAX:

int kill(pid_t pid, int sig);

Description:

    • pid: the PID of the process that we want to kill.
    • sig: the signal that we want to send to the process in order to kill it. There are many different possible signals for kill,
           each with its own nuances (see man 7 signal), but the most frequently used are perhaps SIGTERM (soft termination signal) and SIGKILL (hard kill signal).


kill functions returns 0 for success and -1 for failure

In the following CODE, 3 child process are created and send them straight to infinte loop, then kill(using SIGKILL) them with a signal.
The WTERMSIG macro is used to extract the signal number that caused the child process to terminate.

*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>


// Child process routine:
void    child_routine(void)
{
    printf("\e[36mChild: Hi! I'm a child. I'm in an infinite loop.\e[0m\n");
    while (1) // Infinite loop
        continue;
}

// Parent process routine:
void    kill_and_get_children(pid_t *pid)
{
    int	status;
    int	i;

    printf("Parent: I'm the murderous parent.\n");
    i = 0;
    while (i < 3) // Kill all three children with a signal
    {
        kill(pid[i], SIGKILL);
        i++;
    }
    printf("Parent: I killed all my children! Mwahahaaa!\n");
    i = 0;
    while (i < 3) // Wait for each child and get its exit status
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status)){
            printf("Parent: Child [%d] terminated normally.\n", pid[i]);
        }else if (WIFSIGNALED(status)){

            printf("Parent: Child [%d] was interrupted.\n", pid[i]);

            if (WTERMSIG(status) == SIGTERM)
                printf("\e[31mParent: Child [%d] got the %d signal, SIGTERM\e[0m\n", pid[i], WTERMSIG(status));
            if (WTERMSIG(status) == SIGKILL)
                printf("\e[31mParent: Child [%d] got the %d signal, SIGKILL\e[0m\n", pid[i], WTERMSIG(status));
        }
        i++;
    }
}

int    main(void)
{
    pid_t    pid[3]; // Store fork's return values
    int      i;

    i = 0;
    while (i < 3) // Create 3 children
    {
        pid[i] = fork(); // Create a child
        if (pid[i] == -1)
            return (EXIT_FAILURE);
        else if (pid[i] == 0)
            child_routine();
        else if (pid[i] > 0)
            printf("Parent: Child #%d created with pid = %d\n", i, pid[i]);
        usleep(1000); // Delay next child's creation
        i++;
    }
    kill_and_get_children(pid);
    return (EXIT_SUCCESS);
}




/*

OUTPUT:

Parent: Child #0 created with pid = 327920
Child: Hi! I'm a child. I'm in an infinite loop.
Parent: Child #1 created with pid = 327921
Child: Hi! I'm a child. I'm in an infinite loop.
Parent: Child #2 created with pid = 327922
Child: Hi! I'm a child. I'm in an infinite loop.
Parent: I'm the murderous parent.
Parent: I killed all my children! Mwahahaaa!
Parent: Child [327920] was interrupted.
Parent: Child [327920] got the 9 signal, SIGKILL
Parent: Child [327921] was interrupted.
Parent: Child [327921] got the 9 signal, SIGKILL
Parent: Child [327922] was interrupted.
Parent: Child [327922] got the 9 signal, SIGKILL


Number 9: This represents SIGKILL in Unix-Like Systems

*/