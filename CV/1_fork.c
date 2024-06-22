#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**********************************

// CODE:
int main(void){
    fork();
    printf("Hello World!\n");
    return 0;
}

// OUTPUT:
// Hello World! -> child
// Hello World! -> parent

***********************************/


/**********************************

//CODE:
int main(void){
    fork();
    fork();
    printf("Hello World!\n");
    return 0;
}

// OUTPUT:
// Hello World! -> P1.2
// Hello World! -> P1.1
// Hello World! -> P0.2
// Hello World! -> P0.1

//BLOCK DIAGRAM:

                  P0
                   |
                fork()
                   |
         +---------+---------+
         |                   |
        P0                  P1
         |                   |
      fork()              fork()
         |                   |
    +----+----+          +----+----+
    |         |          |         |
   P0.1     P0.2        P1.1      P1.2


***********************************/




//CODE:
int main(void){
    
    int pid = fork();
    if(pid!=0){
        fork();
    }
    printf("Hello World! with pid: %d\n", pid);
    return 0;
}

// OUTPUT:
// Hello World! with pid: 0
// Hello World! with pid: 23600
// Hello World! with pid: 23600

