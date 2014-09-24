#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
<<<<<<< HEAD
	printf("hello world!!\n");
	long t;
	t = syscall(223,NULL,NULL);
	
	printf("%ld syscall end!!\n",t);	
=======
	long t;
	printf("begin\n");
	t = syscall(223, NULL, NULL);	
	printf("%ld,end\n",t);
>>>>>>> a25e985fae8ee4eb0ad58de75e02563c5fd8c233
	return 0;
}
