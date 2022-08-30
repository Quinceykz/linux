
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef TEST

#else

int main()
{
        pid_t pid;

        pid = fork();
        if (-1==pid) {
                printf("Error to create new process!\n");       
                return 0;         
        }
        else if (pid==0) {
                printf("Child process!\n");
        } else {
                printf("Parent process! Child process ID: %d\n", pid);
        }

        return 0;

}

#endif
