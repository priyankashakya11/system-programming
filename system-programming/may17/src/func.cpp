//Program to define function for server.cpp
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<iostream>
using namespace std;

void createShm(){//creating shared memory
        key_t key = ftok("../data/keyfile",65);//for unique id
        short int shm_id = shmget(key,1,0666 );
        if(shm_id == -1){
                perror("error creating shared memory");
                exit(EXIT_FAILURE);
        }
        //shmat() returns the address of shared memory
        short* no_of_connections = (short*)shmat(shm_id,(void*)0,0);
        *no_of_connections = 0;
}
void destroyShm(){//destroying shared memory
        key_t key = ftok("../data/keyfile",65);
        short int id = shmget(key,1,0666);
        shmctl(id,IPC_RMID,0);
}
short writetoShm(){//write into shared memory
        key_t key = ftok("../data/keyfile",65);
        short int shm_id = shmget(key,1,0666 );
        if(shm_id == -1){
                perror("Error Accessing Shared Memory");
                exit(EXIT_FAILURE);
        }
        //shmat return the address of shared memory
        short* no_of_connections = (short*)shmat(shm_id,(void*)0,0);
        *no_of_connections += 1;
        return *no_of_connections;
}
int createSocket(const char* ip,int port){
    //create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("Socket not created");
        exit(EXIT_FAILURE);
    }
    cout << "Socket created successfully" << endl;

    //create server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //bind
    int ret = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret < 0){
        perror("Error while binding");
        exit(EXIT_FAILURE);
    }
    cout << "Socket bind successfully" << endl;

    //listen for client
    ret = listen(sock, 5);
    if(ret < 0){
        perror("Server is not listening");
        exit(EXIT_FAILURE);
    }
    cout << "listening to port "<< port <<endl;
    return sock;
}
