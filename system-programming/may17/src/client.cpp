//This program creates a TCP client and connects with TCP server
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
using namespace std;

int main(){
        const char* port = "8002";
        int portno = atoi(port);
        //create a socket
        int socketid = socket(AF_INET,SOCK_STREAM,0);
        if(socketid==-1){
                perror("Socket creation failed");
                exit(EXIT_FAILURE);
        }

        //create a server address to connect
        struct sockaddr_in serveraddr;

        //clear the structure
        memset(&serveraddr,0,sizeof(serveraddr));

        //set the server address
        serveraddr.sin_family=AF_INET;
        serveraddr.sin_port=htons(portno);
        serveraddr.sin_addr.s_addr= inet_addr("127.0.0.1");

        //connect to the server
        int connect_status = connect(socketid,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
        if(connect_status==-1){
                perror("Connection failed");
                exit(EXIT_FAILURE);
        }
        //send message to the server
        cout<<"Enter the message for client: ";

        const char* message;
        string m;
        getline(cin,m);
        message = m.c_str();
        ssize_t send_status = send(socketid,message,strlen(message),0);
        if(send_status==-1){
                perror("Message sending failed");
                exit(EXIT_FAILURE);
        }

        while(1){

        //create a buffer to store the message
        char buffer[256];
        //clear the buffer
        memset(buffer,0,sizeof(buffer));

        //receive the message from client
        int len=sizeof(serveraddr);
        ssize_t receive_status = recv(socketid,buffer,256,0);
        if(receive_status==-1){
                perror("Message receiving failed");
                exit(EXIT_FAILURE);
        }
        else if(receive_status==0){
                cout<<"Server closed the connection"<<endl;
                break;
        }
        cout << "Message received successfully" <<endl;

        //print the message from client
        cout<<"Message received : "<<buffer<<endl;

        if(strcmp(buffer,"Bye")==0)
        break;

        //send message to the server
        cout << "Enter the message for server : ";
        const char* message;
        string m;
        getline(cin,m);
        message = m.c_str();
        ssize_t send_status = send(socketid,message,strlen(message),0);
        if(send_status==-1){
                perror("Message sending failed");
                exit(EXIT_FAILURE);
        }
        cout<<"Message sent successfully"<<endl;
        if(strcmp(message,"Bye")==0)
        break;
        }
        //close the socket
        close(socketid);
}
