//Program to write data into shared memory
#include <iostream>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#define MAX 256
using namespace std;

int main() {
	key_t key;
	int shmid;
	//char msg[MAX];
	char *msg;

	key = ftok("keyfile", 65);
	shmid = shmget(key,1024,0666|IPC_CREAT|IPC_EXCL);
	if (shmid == -1){
		perror("Error Creating Shared Memory");
		exit(EXIT_FAILURE);
	}

	msg = (char *) shmat(shmid,(void *)0,0);//assigning value to pointer msg
	write(1,"Enter your data to store: ",25);
	read(0,msg,MAX);

	cout << "Data Written to Shared Memory: " <<msg <<endl;
	shmdt(msg);

	return 0;
}


