//Program to Demonstrate an IPC using Pipe
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256
using namespace std;
char msg1[] = "Hello World #1";
char msg2[] = "Hello World #2";
char msg3[] = "Hello World #3";
int print_error(int ret,const char msg[])
{
	if (ret <0){
	perror(msg);
	exit(EXIT_FAILURE);
	}
	return 0;
}

int main() 
{
	char buff[MAX];
	int pipefd[2],i,ret,len;
	len = strlen(msg1);
	ret = pipe(pipefd);

	print_error(ret,"Error Creating Pipe");
	ret = write(pipefd[1],msg1,strlen(msg1));
	print_error(ret,"Unable to write message to pipe");
	ret = write(pipefd[1],msg2,strlen(msg2));
	print_error(ret,"Unable to write message to pipe");
	ret = write(pipefd[1],msg3,strlen(msg3));
	print_error(ret,"Unable to write message to pipe");

	for (i = 1; i <=3 ; i++)
	{
		ret = read(pipefd[0],buff,len);
		print_error(ret,"Error Reading the Pipe");
		cout << buff <<endl;
	}
		

	close(pipefd[0]);
	close(pipefd[1]);
	return 0;
	
}
