/*

Why we need fifo for ineter-process communication, if we have pipes?

Pipes:
Pipes are a way for processes to communicate.
They can only be used by processes in the same hierarchy (parent-child relationship).
When you create a pipe, you get two file descriptors (FDs).
These FDs are special because they're copied to child processes when you fork.


Limitations of pipes:
You can't use pipes between unrelated processes (processes not in the same hierarchy).


FIFO (First In, First Out):
FIFO is another feature in UNIX systems for inter-process communication.
It's similar to pipes but more flexible.
FIFOs are represented as a special type of file in the filesystem.
Any process can open and use a FIFO, regardless of hierarchy.

*/


//This is also called as -> Named FIFO

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


int main(void){
    if(mkfifo("fifo1", 0777)==-1){                                  //0777 -> Octal Representation (cuz, starts with '0') of file permissions in Unix-Like OS. This grants full permissions (read, write, execute) to all users (owner, group, others) on the system
        if(errno != EEXIST){                                         
            printf("Could not create fifo file\n");                 //prints only for errors other than EEXIST. If file exists (EEXIST is true), code continues silently without prrinting this message.
            return 1;
        }
    }

    int fd = open("fifo1", O_WRONLY);                               //Creating file descriptor with WRITE_ONLY
    if(fd==-1){
        return 2;
    }
    int x = 97;
    if(write(fd, &x, sizeof(int))==-1){
        return 3;
    }
    close(fd);

    return 0;
}

/*

-------
OUTPUT:
-------
The program creates fifo1 and opens a write only file descriptor. After that it'll hang.
The reason behind this behaviour of fifo (written in linux manual) is:

open() blocks until both ends of the FIFO are opened; it hangs here as only write end is opened.

NOTE: The FIFO must be opened on both ends (reading and writing) before data can be passed


---------
SOLUTION:
---------
1. Compile and prepare the program:
   - Compile the C program that creates and writes to the FIFO.
   - Let's assume the compiled executable is named `fifo_writer`.

2. Open two terminal windows:
   - Terminal 1 will run the C program.
   - Terminal 2 will act as the reader for the FIFO.

3. In Terminal 1:
   - Run the compiled program: ./fifo_writer
   - The program will create the FIFO (if it doesn't exist) and attempt to open it for writing.
   - It will then wait (hang) until a reader opens the other end of the FIFO.

4. In Terminal 2:
   - Use the `cat` command to open the FIFO for reading: cat fifo1
   - This opens the read end of the FIFO.

5. Result:
   - As soon as you execute the `cat` command in Terminal 2, the program in Terminal 1 will unblock.
   - The C program will write the integer value to the FIFO and terminate.
   - The `cat` command in Terminal 2 will display the contents written to the FIFO.

6. Completion:
   - The program in Terminal 1 will finish execution.
   - The `cat` command in Terminal 2 will display the output and then wait for more input.


-----
NOTE:
-----
If you open just one terminal and run `cat fifo1`:

1. Open a single terminal and execute: cat fifo1

2. Result:
   - The `cat` command will hang, waiting for input.
   - This occurs because `cat` is opening the FIFO for reading, but there's no writer yet.

3. Explanation:
   - FIFOs require both a reader and a writer to be open before data can flow.
   - When `cat` opens the FIFO for reading, it waits for a writer to open the other end.
   - Since there's no writer (the C program isn't running), `cat` continues to wait indefinitely.


-----
NOTE:
-----
Instead of  : int fd = open("fifo1", O_WRONLY); //Write Only
If I do    : int fd = open("fifo1", O_RDWR);   //Read & Write, now the program won't hang, as both the ends of FIFO (i.e. fifo1) are open.    


*/