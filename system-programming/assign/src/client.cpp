//Program to define tcp client
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8002
#define SA struct sockaddr
using namespace std; 
int main()
{
    int sockfd, connfd, mlen;
    struct sockaddr_in servaddr, cli;
    char buff[MAX];
    int n;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout<<"socket creation failed...\n";
        exit(EXIT_FAILURE);
    }
    else
        cout<<"Socket successfully created..\n";
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        cout<<"connection with the server failed...\n";
        exit(EXIT_FAILURE);
    }
    else
        cout<<"connected to the server..\n";
   
    for (;;) {
        bzero(buff, sizeof(buff));
        cout <<"Enter the string : ";
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        mlen = read(sockfd, buff, sizeof(buff));
	cout <<mlen <<"Byte message sent"<<endl;
        cout <<"From Server : "<< buff;
        if ((strncmp(buff, "exit", 4)) == 0) {
            cout<<"Client Exit...\n";
            break;
        }
    }
   
    close(sockfd);
}
