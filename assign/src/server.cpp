//Program to call function
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include "../include/header.h"
#define MAX 80
#define PORT 8002
#define SA struct sockaddr
using namespace std;   
// Function designed for chat between client and server
int main()
{
	int connfd;

	char buff[MAX];
	int n;
        // infinite loop for chat
	for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        cout <<"From client : " <<buff <<endl;
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
         ;
   
        // and send that buffer to client
        write(connfd, buff, sizeof(buff));
   
        // if msg contains "Bye" then server exit and chat ended.
        if (strncmp("Bye", buff, 4) == 0) {
            cout <<"Server Exit...\n";
            break;
        }
    }
}
   




