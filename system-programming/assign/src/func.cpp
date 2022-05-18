//Program to create function
#include <iostream>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8002
#define SA struct sockaddr
using namespace std;

int create_socket()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    socklen_t len;
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cout<<"socket creation failed...\n";
        exit(0);
    }
    else
        cout<<"Socket successfully created..\n";
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        cout<<"socket bind failed...\n";
        exit(0);
    }
    else
        cout<<"Socket successfully binded..\n";

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        cout<<"Listen failed...\n";
        exit(0);
    }
    else
        cout<<"Server listening..\n";
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        cout<<"server accept failed...\n";
        exit(0);
    }
    else
        cout<<"server accept the client...\n";

        return sockfd;
}

key_t key;
int shmid;
short int *size;
int create_shm()
{
    // ftok to generate unique key
    key = ftok("data/shmfile",65);

    // shmget returns an identifier in shmid
    shmid = shmget(key,2048,0666|IPC_CREAT);

    // shmat to attach to shared memory
    size = (short int *) shmat(shmid,(void*)0,0);


    //detach from shared memory
    shmdt(size);

    return 0;
}
// Destroy shared memory function
int destroy_shm()
{

            //detach from shared memory
            shmdt(size);

           //destroy the shared memory
           shmctl(shmid, IPC_RMID, NULL);
           return 0;
}
