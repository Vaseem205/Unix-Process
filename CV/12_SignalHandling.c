/*

Controling the way signals behave.

Implementation:

We gonna change the way process behaves for these two signals: 

1. Ctrl+Z (SIGTSTP)
2. fg (SIGCONT)

by using sigaction structure

*/
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handleSIGTSTP(int sig){
    printf("Trying to stop the process, but not allowed.\n");
}

void handleCONT(int sig){
    printf("Enter the number: \n");
    fflush(stdout);
}

int main(){

    struct sigaction sa;
    sa.sa_handler = &handleCONT;
    sa.sa_flags = SA_RESTART;               // to avoid some erros which occurs due to the conflict with scanf()
    // sigaction(SIGTSTP, &sa, NULL);       // whenever you press Ctrl+Z, handleSIGTSTP() gets called
    sigaction(SIGCONT, &sa, NULL);          // NULL: Holds the previous state.

    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    num *= 5;
    printf("multiplied by 5: %d\n", num);
    printf("\n");
    return 0;
}



/*

OUTPUT (SIGTSTP):
vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ ./12
Enter a number: 
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
^ZTrying to stop the process, but not allowed.
4
multiplied by 5: 20



OUTPUT (SIGCONT):
vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ ./12
Enter a number: ^Z
[1]+  Stopped                 ./12
vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ fg
./12
Enter the number: 
12
multiplied by 5: 60





*/