//Server Implementation of UDP
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8002
#define MAX 1024
using namespace std;
// Driver code
int main() {
    int sockfd;
    char buffer[MAX];
    char hello[MAX] = "Hello from server to client";
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    int n;

   // len = sizeof(cliaddr);  //len is value/result

    n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
    buffer[n] = '\0';
    cout<<"Client :"<<buffer<<"\n";
    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
    cout<<"Hello message sent to server.\n";

    return 0;
}
