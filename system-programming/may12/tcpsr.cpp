//The program to create a test TCP server
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define PORTNO 8045
#define MAX 256
using namespace std;


int main() {
        struct sockaddr_in servaddr, cliaddr;
        char smsg[MAX];
        char cmsg[MAX];
        int sockfd,mlen,slen,connfd;//Initialising sock filedescriptor, message length, structure length
        socklen_t clen;
        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);

        servaddr.sin_family = AF_INET;//To use internet family of addressing
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);; 
        servaddr.sin_port = htons(PORTNO);

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        bind(sockfd,(const struct sockaddr *)&servaddr,slen);
        listen(sockfd,5);

        connfd=accept(sockfd,(struct sockaddr *) &cliaddr, &clen);

        mlen=read(connfd,cmsg,MAX);
	write(1,"Message from client:",21);
	write(1,cmsg,strlen(cmsg));
	write(1,"Enter your message for client:",32);
	mlen = read(0,smsg,MAX);
        mlen=write(connfd,smsg,strlen(smsg));

        cout << mlen <<"Bytes message sent from the server"<< endl;
        close(connfd);
}
