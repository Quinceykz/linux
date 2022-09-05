
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
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
        struct sockaddr_in local;
        struct sockaddr_in from;
        int n;
        socklen_t fromlen;
        char buff[DATA_SIZE];
        socklen_t len;
        time_t cur_time;

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

        local.sin_family = AF_INET;
        local.sin_port = htons(TIME_PORT);
        local.sin_addr.s_addr = INADDR_ANY;

        if (0!=bind(sock_fd, (struct sockaddr*)&local, sizeof(local))) {
                perror("bind socket error!");
                close(sock_fd);
                return 0;
        }
        printf("Bind socket");

        fromlen = sizeof(from);
        printf("Waiting request from client...\n");

        while(1)
        {
                /* int recvfrom(int s, void *buf, int len, unsigned int flags,
                struct sockaddr *from, int *fromlen); 
                object: On success, the actual number of characters received 
                is returned.On failure, -1 is returned. The cause of the error
                is stored in errno.
                parameter: 1 . socket handle 2 . UDP data buff 3 . len of data
                4 . way to call 5 . address of client 6 . len of client     
                return: number of data                                      */
                n = recvfrom(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)
                &from, &fromlen);
                if (n<=0) {
                        perror("recv data!\n");
                        close(sock_fd);
                        return 0;
                }
                buff[n] = '\0';
                printf("Client request: %s\n", buff);

                if (0==strcmp(buff, "quit"))
                        break;

                if (0==strcmp(buff, "time")) {
                        cur_time = time(NULL);
                        strcpy(buff, asctime(gmtime(&cur_time)));
                        sendto(sock_fd, buff, sizeof(buff), 0, (struct sockaddr*)
                        &from, fromlen);
                }
        }
        close(sock_fd);
        return 0;
}
