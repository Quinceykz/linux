
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define TIME_PORT 9090
#define DATA_SIZE 256

int main()
{
        int sock_fd;
        /*___________________struct sockaddr_in____________________
        member: 1. family : address family
        2. port : COM of TCP/UDP (HEX) ( big-endian  little-endian )
        3. addr : address of .32       ( big-endian  little-endian )
        4. no used                                              */
        struct sockaddr_in serv;
        int n;
        socklen_t servlen;
        char buff[DATA_SIZE];

        /*______int socket(int domain, int type, int protocol)______
        object: creat a socket data: **sock_fd**
        parameter: 1. domain : protocol of socket. ex:  **AF_INET**
        AF_INET6   AF_LOCAL   AF_ROUTE
        2. type : Data transmission mode 
        ex:  **SOCK_STREAM** SOCK_DGRAM                         */
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock_fd<=0) {
                perror("Create socket error!");
                return 0;
        } 
        perror("Create socket");

        serv.sin_family = AF_INET;
        serv.sin_port = htons(TIME_PORT);
        serv.sin_addr.s_addr = INADDR_ANY;
        servlen = sizeof(serv);

        strcpy(buff, "time");
        if (-1==sendto(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)
        &serv, servlen)) {
                perror("Send data");
                close(sock_fd);
                return 0;
        }
        printf("Send time request\n");

        n = recvfrom(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)
        &serv, &servlen);
        if (n<=0) {
                perror("Rece data!\n");
                close(sock_fd);
                return 0;
        }
        buff[n] = '\0';
        printf("Time from server: %s", buff);

        strcpy(buff, "quit");
        if (-1==sendto(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)
        &serv, servlen)) {
                perror("Send data");
                close(sock_fd);
                return 0;
        }
        printf("Send quit command\n");

        close(sock_fd);
        return 0;
}
