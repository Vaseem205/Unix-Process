#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

/*

Implemenation:
1. Split the array into half.
2. Calculate the sum of each elements in both the halves, simulataneously
3. Return the sum separately

*/

/*
int main(void){

    int start, end;

    int arr[] = {1,2,3,4,5,6,7};
    int arrSize = sizeof(arr)/sizeof(int);
    int fd[2];

    if(pipe(fd)==-1){
        return 1;                                   //pipe error
    }

    int id = fork();                                //forking

    if(id==-1){
        return 2;                                   //forking error
    }

    if(id==0){
        start = 0;                                  //child start
        end = arrSize/2;                            //child end
    }else{
        start = arrSize/2;                          //parent start
        end = arrSize;                              //parent end
    }

    int sum = 0;
    int i;
    for(i=start; i<end; i++){
        sum += arr[i];
    }

    printf("Sum is: %d\n", sum);
}

*/

/*

OUTPUT:
Sum is: 22          -> Parent sum
Sum is: 6           -> Child sum

*/


/*

Implementation: Inter-Process Commn
Now send the sum of Child_process to Parent_process (using pipe)

*/


/*

int main(void){

    int start, end;

    int arr[] = {1,2,3,4,5,6,7,8};
    int arrSize = sizeof(arr)/sizeof(int);
    int fd[2];

    if(pipe(fd)==-1){
        return 1;                                   //pipe error
    }

    int id = fork();                                //forking

    if(id==-1){
        return 2;                                   //forking error
    }

    if(id==0){
        start = 0;                                  //child start
        end = arrSize/2;                            //child end
    }else{
        start = arrSize/2;                          //parent start
        end = arrSize;                              //parent end
    }

    int sum = 0;
    int i;
    for(i=start; i<end; i++){
        sum += arr[i];
    }

    printf("Sum is: %d\n", sum);

    if(id==0){
        close(fd[0]);                               //esuring read-end is closed
        if(write(fd[1], &sum, sizeof(int))==-1){
            return 3;
        }
        close(fd[1]);
    }else{
        int childSum;
        close(fd[1]);
        if(read(fd[0], &childSum, sizeof(int))==-1){
            return 4;
        }
        close(fd[0]);

        int totalSum = sum + childSum;
        printf("Total sum is: %d\n", totalSum);
        wait(NULL);                                 //waiting for Child_process to complete
    }


}

*/


/*

Explanation of above code:

File descriptor creation:
Before forking, the parent process creates a pipe using pipe(fd).
This creates two file descriptors: fd[0] for reading and fd[1] for writing.

Forking:
When fork() is called, the operating system creates an exact copy of the parent process.
This copy includes all the memory, variables, and open file descriptors of the parent process.

Child process inheritance:
The child process inherits a copy of all the parent's file descriptors.
This means the child process has its own copies of fd[0] and fd[1], which refer to the same pipe as the parent's file descriptors.

After forking:
Both the parent and child processes now have access to the same pipe through their respective file descriptors.
They can use these to communicate with each other.

*/
