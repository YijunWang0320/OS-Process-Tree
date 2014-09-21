#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
	printf("hello world!!\n");
	long t;
	t = syscall(223,NULL,NULL);
	
	printf("%ld syscall end!!\n",t);	
	return 0;
}
