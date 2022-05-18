//Program to create TCP server
#include <iostream>
#include "../include/func.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
using namespace std;
int main(int argc, char* argv[]){
        createShm();
        int sock = createSocket("0.0.0.0",8002);
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
         //accept all clients and create new process for each client

        while(1){
        int client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
        if(client_sock < 0){
            perror("Error accepting client");
            exit(EXIT_FAILURE);
        }
        int clientsNO = writetoShm();
        cout << "Number of connection: " << clientsNO << endl;

        //fork a child process
        pid_t pid = fork();
        if(pid < 0){
            perror("Error ");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0){
            //child process
            close(sock);
            char buf[1024];
            while(1){
                memset(buf, 0, sizeof(buf));
                int len = recv(client_sock, buf, sizeof(buf), 0);
                if(len < 0){
                    perror("Error while accepting");
                    exit(EXIT_FAILURE);
                }
                else if(len == 0){
                    cout << "Client closed" << endl;
                    break;
                }
                else{
                    cout << "client message: " << buf << endl;
                   
                    memset(buf,0,sizeof(buf));
                    cout << "Enter Message: ";
                    cin.getline(buf,sizeof(buf));
                    send(client_sock, buf, strlen(buf), 0);
                }
            }
            close(client_sock);
            exit(0);
        }
        else{
            //parent process
            close(client_sock);
        }
    }
    destroyShm();
    close(sock);
}
