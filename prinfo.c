#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
	long t;
	t = syscall(223,NULL,NULL);
	printf("num of processes: %ld\n", t);
	return 0;
}
