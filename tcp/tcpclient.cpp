//The program to create a test TCP Client
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define PORTNO 8002
#define MAX 256
using namespace std;


int main() {
        struct sockaddr_in servaddr, cliaddr;
        char cmsg[MAX];
        char smsg[MAX];
        int sockfd,mlen,slen;//Initialising sock filedescriptor, message length,                                                        structure length
        socklen_t servaddrlen;
        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(smsg,0,MAX);


        servaddr.sin_family = AF_INET;//To use internet family of addressing
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORTNO);


        sockfd = socket(AF_INET,SOCK_STREAM,0);
        connect(sockfd,(struct sockaddr *)&servaddr,slen);
        write(1,"Enter your message for server:",30);
        mlen = read(0,cmsg,MAX);
        mlen = write(sockfd,cmsg,strlen(cmsg));
        write(1,"Message sent from the client:",30);
        write(1,cmsg,strlen(cmsg));
        mlen = read(sockfd,smsg,MAX);
        write(1,smsg,strlen(smsg));
        close(sockfd);
}

