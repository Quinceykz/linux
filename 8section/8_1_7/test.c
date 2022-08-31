
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>   

#ifdef TEST

#else


int main()
{
        int fd[2];
        pid_t pid;
        char buff[64], *cmd = "exit";

        if (pipe(fd)) {
                perror("Create pipe fail!");
                return 0;
        }

        pid = fork();
        if (-1==pid) {
                perror("Create process fail!");
                return 0;
        } else if (0==pid) {
                printf("function child has pid as: %d \n",pid);
                close(fd[1]);
                printf("wait command from, parent!\n");
                while(1) {
                        read(fd[0], buff, 64);
                        if(0==strcmp(buff, cmd)) {
                                printf("recv command ok!\n");
                                close(fd[0]);
                                exit(0);
                        }
                }
        } else {
                printf("Parent process! child process id : %d\n", pid);
                close(fd[0]);
                sleep(2);
                printf("Send command to child process.\n");
                write(fd[1], cmd, strlen(cmd)+1);
                close(fd[1]);
        }

        return 0;

}

#endif
