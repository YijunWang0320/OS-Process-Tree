#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char **argv) {
	long t;
	printf("begin\n");
	t = syscall(223, NULL, NULL);	
	printf("%ld,end\n",t);
	return 0;
}
