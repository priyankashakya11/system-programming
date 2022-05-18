//Program to demonstrate a race condition
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
//#define MAX 5000
using namespace std;

long balance = 0;
void *computebal(void *arg) {
	long bal,c;
	bal = balance;
	for (int i=0; i < 50000; i++) {
		c = 5000 * 123478;
	}
	bal += 10;
       balance = bal;
       return NULL;
}

int main() {
	int i;
	pthread_t thread_id[200];
	cout << "Balance Before Thread: " << balance <<endl;
       for (i=0; i <200; i++) {
       pthread_create(&thread_id[i],NULL,computebal,NULL);
       }

       for (i=0; i <200; i++) {
       pthread_join(thread_id[i],NULL);	
       }
	cout <<"Balance After Thread: " << balance <<endl;
	
	exit(EXIT_SUCCESS);
}	


