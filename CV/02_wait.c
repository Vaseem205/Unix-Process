#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*

//-----> without wait() <-----

int main(void){

    int pid = fork();
    int n;

    if(pid==0){
        n=1;
    }else{
        n=6;
    }
    
    for(int i = n; i<n+5; i++){
        printf("%d ", i);
        fflush(stdout);
    }

    printf("\n");

    return 0;

}

//OUTPUT:
// 6 7 8 9 10 
// 1 2 3 4 5 

//NOTE: The OS decided that PARENT_PROCESS should complete its execution FIRST and then it gave control to CHILD_PROCESS for exection.

*/



//-----> with wait() <-----

int main(void){

    int pid = fork();
    int n;

    if(pid==0){
        n=1;
    }else{
        n=6;
    }

    if(pid!=0){
        wait();
    }
    
    for(int i = n; i<n+5; i++){
        printf("%d ", i);
        fflush(stdout);
    }

    printf("\n");

    return 0;

}

//OUTPUT:
// 1 2 3 4 5 
// 6 7 8 9 10 

//NOTE: wait() func stops the PARENT_PROCESS and let the CHILD_PROCESS completes its execution, then again it gave control back to PARENT_PROCESS.




