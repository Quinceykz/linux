
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>   

int main()
{
        int fd[2];
        int status;
        pid_t pid;
        char buf[64] = "I'm parent process!\n";
        char line[64];

        // int pipe (int __pipedes[2]);
        if (0!=pipe(fd)) {
                fprintf(stderr, "Fail to create pipe1\n");
                return 0;
        }
        pid = fork();
        if (pid<0) {
                fprintf(stderr, "Fail to create process!\n");
                return 0;
        } else if (0==pid) {
                // close a pipe of W/R
                close(fd[0]);
                // write buf to adress fd[1]
                write(fd[1], buf, strlen(buf));
                close(fd[1]);
        } else {
                close(fd[1]);
                // read from fd[0] ,write to line
                read(fd[0], line, 64);
                printf("DATA From Parent: %s", line);
                close(fd[0]);
        }

        // parent process will go on afer child process end.
        waitpid(pid, &status, 0);

        return 0;

}
