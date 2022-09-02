
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#define EHCO_PORT 8080
#define MAX_CLIENT_NUM 10

int main()
{
        int sock_fd;
        /*___________________struct sockaddr_in____________________
        member: 1. family : address family
        2. port : COM of TCP/UDP (HEX) ( big-endian  little-endian )
        3. addr : address of .32       ( big-endian  little-endian )
        4. no used                                              */
        struct sockaddr_in serv_addr;
        int clientfd;
        struct sockaddr_in clientAdd;
        char buff[101];
        socklen_t len;
        int n ;

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
        2. n : size of **serv_addr**(long)                       */
        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        /*              big-endian  little-endian                */
        serv_addr.sin_port = htons(EHCO_PORT);
        serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
        bzero(&(serv_addr.sin_zero), 8);

        /*int bind(int sockfd,  const struct sockaddr, socklen_t addrlen)
        object: take protocol to a key 
        parameter: 1. sockfd : flag bit of socket **sock_fd**
        2. sockaddr : address of socket
        3. addrlen : size of address                              */
        if(bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))!=0) {
                printf("bind address fail! %d\n", errno);
        /*stop the COM of socket flag bit*/
                close(sock_fd);
                return 0;
        } else {
                printf("Success to bind address!\n");
        }

        /*__________int listen(int sockfd, int backlog)____________
        object: take socket mode from closed to listen
        parameter: 1. sockfd : a closed mode socket
        2. backlog : max number of client                         */
        if(listen(sock_fd, MAX_CLIENT_NUM) != 0) {
                perror("listen socket error!\n");
                close(sock_fd);
                return 0;
        } else {
                printf("Success to listen!\n");
        }

        len = sizeof(clientAdd);
        /*____int accept(int sockfd, void *addr, int *addrlen);____   *****
        object: connect a listen mode socket
        parameter: 1. sockfd : a listen mode socket
        2. addr : address of client
        3. addrlen : size of address                              */
        clientfd = accept(sock_fd, (struct sockaddr*)&clientAdd, &len);
        if (clientfd<=0) {
                perror("accept() error!\n");
                close(sock_fd);
                return 0;
        }

        /*_int recv( SOCKET s, char FAR *buf, int len, int flags);_
        object: received info from rx_buf of socket
        parameter: 1. socket 
        2. buf : rx_buf to save the info rx
        3. len : len of buf
        4. flags : normal as 0                                    */
        while((n = recv(clientfd, buff, 100, 0)) > 0) {
                buff[n] = '\0';
                printf("number of receive bytes = %d data = %s\n", n,buff);
                /*___________int fflush(FILE *stream);____________
                object: Flush the buffer and output the data 
                in the buffer to the device
                parameter: stream : object to stdout(printf)      */
                fflush(stdout);
                send(clientfd, buff, n, 0);
                /*int strncmp(const char* str1, const char* str2, size_t num)
                object: Compare the size of two strings*/
                if(strncmp(buff, "quit", 4) == 0)
                        break;
        }

        close(clientfd);
        close(sock_fd);
        return 0;
}
