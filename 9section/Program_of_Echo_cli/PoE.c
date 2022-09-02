
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define EHCO_PORT 8080
#define MAX_COMMAND 5

int main()
{
        int sock_fd;
        /*___________________struct sockaddr_in____________________
        member: 1. family : address family
        2. port : COM of TCP/UDP (HEX) ( big-endian  little-endian )
        3. addr : address of .32       ( big-endian  little-endian )
        4. no used                                              */
        struct sockaddr_in serv_addr;

        char *buff[MAX_COMMAND] = {"abcsdadef", "def", "test", "hello", "quit"};
        char tmp_buf[100];
        int n, i;

        /*______int socket(int domain, int type, int protocol)______
        object: creat a socket data: **sock_fd**
        parameter: 1. domain : protocol of socket. ex:  **AF_INET**
        AF_INET6   AF_LOCAL   AF_ROUTE
        2. type : Data transmission mode 
        ex:  **SOCK_STREAM** SOCK_DGRAM                         */
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(sock_fd==-1) {
                perror("Create socket error!");
                return 0;
        } else {
                printf("Success to create socket %d\n", sock_fd);
        }

        /*______________void bzero(void *s, int n)_________________
        object: set val before s to 0
        parameter: 1. s : flag bit **serv_addr**
        2. n : size of **serv_addr**(long)                       
        memset                                                   */
        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        /*              big-endian  little-endian                */
        serv_addr.sin_port = htons(EHCO_PORT);
        serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
        bzero(&(serv_addr.sin_zero), 8);

        if(-1==connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
                perror("connect() error!\n");
                close(sock_fd);
                return 0;
        }
        printf("Success connect to server!\n");

        for (i=0;i<MAX_COMMAND;i++) {
                send(sock_fd, buff[i], strlen(buff[i]), 0);
                n = recv(sock_fd, tmp_buf, 100, 0);
                tmp_buf[n] = '\0';
                printf("data send: %s receive: %s\n", buff[i], tmp_buf);

                if (0==strncmp(tmp_buf, "quit", 4))
                        break;
        }

        close(sock_fd);
        return 0;
}
