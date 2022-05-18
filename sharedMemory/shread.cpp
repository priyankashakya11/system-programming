//Program to read data into shared memory
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
	char *msg;

	key = ftok("keyfile", 65);
	shmid = shmget(key,1024,0666);
	if (shmid == -1){
		perror("Error Creating Shared Memory");
		exit(EXIT_FAILURE);
	}

	msg = (char *) shmat(shmid,(void *)0,0);//assigning value to pointer msg

	cout << "Data in Shared Memory: " <<msg <<endl;
	shmdt(msg);
	shmctl(shmid,IPC_RMID,NULL);

	return 0;
}


