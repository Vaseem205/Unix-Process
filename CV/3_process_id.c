#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/*
int main(){
    int id = fork();

    printf("CURRENT PID:%d, PARENT PID:%d\n", getpid(), getppid());

    return 0;

}

*/

/*

OUTPUT:
CURRENT PID:61055, PARENT PID:23365  -> Parent_process got executed first
CURRENT PID:61056, PARENT PID:61055  -> Child_process got executed next

NOTE: 
1. Note that CURRENT PID of Parent_process and PARENT PID of Child_process is same
2. Even Parent_process has it's own PARENT (i.e. PARENT PID: 23365)

*/



/*
int main(){
    int id = fork();

    if(id==0){
        sleep(1);   //making the child process sleep -> this sleep cost the child process to become as ORPHAN (i.e. Parent will be dead, but child is alive)
    }

    printf("CURRENT PID:%d, PARENT PID:%d\n", getpid(), getppid());

    return 0;
}
*/

/*

OUTPUT:
CURRENT PID:62698, PARENT PID:23365
(base) vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ CURRENT PID:62699, PARENT PID:1867

NOTE:
1. Note that CURRENT PID of Parent_process and PARENT PID of Child_process is not same
2. This made the Child_process become ORPHAN and it got adopted by different parent (i.e. PARENT PID:1867)
3, Child_process became ORPHAN because Parent_process didn't wait for Child_process to finish its execution.

*/


int main(){
    int id = fork();

    if(id==0){
        sleep(1);   //making the child process sleep -> this sleep cost the child process to become as ORPHAN (i.e. Parent will be dead, but child is alive)
    }

    printf("CURRENT PID:%d, PARENT PID:%d\n", getpid(), getppid());

    int res = wait(NULL); //passing NULL param cuz we included sys/wait.h
    if(res==-1){
        printf("No children to wait for\n");
    }else{
        printf("%d finshed execution\n", res);
    }

    return 0;

}


/*
OUTPUT:
CURRENT PID:65654, PARENT PID:23365
CURRENT PID:65655, PARENT PID:65654
No children to wait for                  -> This was executed by PARENT
65655 finshed execution                  -> This was executed by CHILD

NOTE:
1. Note that CURRENT PID of Parent_process and PARENT PID of Child_process is same (cuz even if the Child_process was sleeping
but wait(NULL) made the Parent_process wait for Child_process to complete its execution)

*/



