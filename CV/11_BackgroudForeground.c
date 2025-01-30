/*

Background = Ctrl+Z
Foreground = fg

While process is executing, if user enters: "Ctrl+Z" (in terminal)
It'll send a "SIGTSTP" signal to the process and send that process to the backgroud.
While the process is in background, it wont execute.

When user press "fg" (in terminal):
It'll send a "SIGCONT" signal to the process and send that process to the foregroud.
Process in foreground starts executing....


What is the difference between SIGSTOP and SIGTSTP?
- SIGSTOP is a signal sent programmatically,
  while SIGTSTP sent through the tty driver by a user typing on a keyboard, usually Control-Z.

- SIGSTOP cannot be ignored. SIGTSTP might be.

*/

#include <stdio.h>

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    num *= 5;
    printf("multiplied by 5: %d\n", num);
    printf("\n");

    return 0;
}


/*

OUTPUT:
vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ ./11
Enter a number: ^Z
[1]+  Stopped                 ./11
vaseem@vaseemakram:~/C_Programming/Operating_Systems/Process/CV$ fg
./11
10
multiplied by 5: 50


*/