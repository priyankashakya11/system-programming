//The program to create multiple test TCP server
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
        char smsg[MAX];
        char cmsg[MAX];
        int sockfd,mlen,slen,connfd,ret;//Initialising sock filedescriptor, message length, structure length
        socklen_t clen;
        pid_t client_pid;

        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);


        servaddr.sin_family = AF_INET;//To use internet family of addressing
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORTNO);


        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if (sockfd < 0){
                fputs("Error: Can't create socket",stderr);
                exit(EXIT_FAILURE);
        }


        ret = bind(sockfd,(const struct sockaddr *)&servaddr,slen);
        if (ret < 0){
                fputs("Error: Can't create socket",stderr);
                exit(EXIT_FAILURE);
        }


        ret = listen(sockfd,5);
        if (ret < 0){
                fputs("Error: Can't create socket",stderr);
                exit(EXIT_FAILURE);
        }

        while(1) {
        connfd=accept(sockfd,(struct sockaddr *) &cliaddr, &clen);
        if (connfd < 0){
                fputs("Error: Can't accept the connection",stderr);
                exit(EXIT_FAILURE);
        }



        client_pid = fork();
        if (client_pid == 0) {
                close(sockfd);
                mlen=read(connfd,cmsg,MAX);
                write(1,"Message from the client:",24);
                write(1,cmsg, strlen(cmsg));
                write(1,"Enter message for client:",32);
                mlen = read(0,smsg,MAX);
                mlen=write(connfd,smsg,strlen(smsg));
                cout << mlen << "Message sent from the server" << endl;
                close(connfd);
                exit(EXIT_SUCCESS);
        }
                close(connfd);
        }
}

