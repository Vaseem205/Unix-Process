/*

In order to suspend the parent process execution until the child process state changes(wait for child process to complete),
we can use the wait() or waitpid() system calls from the <sys/wait.h> library.

wait(): This sys call retrive info about first terminated child process.
waitpid(): It is flexible version of wait(). It allows a parent process to wait for a specific child process to terminate.


SYNTAX:

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);


Description:

  • status: It tells information about the way in which a child process finished its execution. It is a pointer to an integer type variable in which wait and waitpid can store the child’s exit status.
	We will be able to examine this number with different macros to determine if the child finished normally or was interrupted, among other things.
	    • WIFEXITED(status): returns true if the child terminated normally, for example by calling exit or finishing through the main function of the program.
        	◦ WEXITSTATUS(status): to be used only if WIFEXITED returned true. Returns the child’s exit code, meaning the number the child specified to the exit function or in the main function’s return.
    	• WIFSIGNALED(status): returns true if the child was forcefully terminated by a signal.
        	◦ WTERMSIG(status): to be used only if WIFSIGNALED returned true. Returns the signal number that provoked the child’s termination.

  • pid: This specifies the PID of the child process we should wait for.
    The parent process knows this PID because, it is the return value that fork provided when the child was created.
	Alternatively, we can specify -1 in order to wait for whichever child finished first, just like wait. Indeed, waitpid(-1, status, 0) is exactly the same as wait(status)

  • options: 
	WNOHANG: The parent process uses waitpid with WNOHANG to check for the child process periodically.
			 If the child process has terminated, waitpid returns the child process ID, and the parent process can then handle the termination.
			 If no child process is ready, waitpid returns 0, and the parent process continues to check periodically.

	WUNTRACED: The parent process uses waitpid with WUNTRACED to wait for both terminated and stopped child processes.
			   If the child process has terminated, waitpid returns the child process ID. If the child process has been stopped (e.g., by a signal),
			   waitpid also returns the child process ID.

*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// Defining a macro for a specific child exit code (if we do not
// specify this exit code during compilation with the 
// -D CHILD_EXIT_CODE=[number] option), by default, it will be 42:
#ifndef CHILD_EXIT_CODE
# define CHILD_EXIT_CODE 42
#endif

// Define a macro for the expected exit status
#define EXPECTED_CODE 42

// Child process routine:
void	child_routine(pid_t pid)
{
	printf("\e[36mChild: Hi! I'm the child. PID received from fork = %d\e[0m\n", pid);
	printf("\e[36mChild: Exiting with exit code %d.\e[0m\n", CHILD_EXIT_CODE);
	exit(CHILD_EXIT_CODE);
}

// Parent process routine:
void	parent_routine(pid_t pid)
{
	int	status;

	printf("Parent: I'm the parent. PID received from fork = %d\n", pid);
	printf("Parent: Waiting for my child with PID [%d].\n", pid);

	waitpid(pid, &status, 0); // Wait for child
	
	printf("Parent: My child exited with status %d\n", status);

	if (WIFEXITED(status)) // If child exited normally
	{
		printf("Parent: My child's exit code is %d\n", WEXITSTATUS(status));

		if (WEXITSTATUS(status) == EXPECTED_CODE)
			printf("Parent: That's the code I expected!\n");
		else
			printf("Parent: I was not expecting that code...\n");
	}
}

int	main(void)
{
	pid_t	pid; // Store fork's return value

	pid = fork(); // Create child process
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0) // Child process
		child_routine(pid);
	else if (pid > 0) // Parent process
		parent_routine(pid);
	return (EXIT_SUCCESS);
}

/*

OUTPUT:

We can compile this code with the -D flag to define an exit status for the child to use, like this:

$ gcc wait.c -D CHILD_EXIT_CODE=42 && ./a.out	--> Success

$ gcc wait.c -D CHILD_EXIT_CODE=9 && ./a.out	--> Failure

*/