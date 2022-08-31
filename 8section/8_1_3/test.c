
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
        pid_t pid;

// __pid_t fork (void); creat a new process.
        pid = fork();
        if (-1==pid) {
                printf("Error to create new process!\n");       
                return 0;         
        }
        else if (pid==0) {
                while(1) {
                        printf("Child process!\n");   
                        sleep(100);
                }

        } else {
                printf("Parent process! Child process ID: %d\n", pid);
        }

        return 0;

}

// use   ps aux  watch the process
// use   kill PID   stop it.
