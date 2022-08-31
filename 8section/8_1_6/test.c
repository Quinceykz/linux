
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>   

#ifdef TEST

#else


int main()
{
        int fd[2];
        int status;
        pid_t pid;
        char buf[64] = "I'm parent process!\n";
        char line[64];

        if (0!=pipe(fd)) {
                fprintf(stderr, "Fail to create pipe1\n");
                return 0;
        }
        pid = fork();
        if (pid<0) {
                fprintf(stderr, "Fail to create process!\n");
                return 0;
        } else if (0==pid) {
                close(fd[0]);
                write(fd[1], buf, strlen(buf));
                close(fd[1]);
        } else {
                close(fd[1]);
                read(fd[0], line, 64);
                printf("DATA From Parent: %s", line);
                close(fd[0]);
        }

        waitpid(pid, &status, 0);

        return 0;

}

#endif
