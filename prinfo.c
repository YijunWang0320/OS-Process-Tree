#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <memory.h>
#include "prinfo.h"

int main(int argc, char **argv) {
	long t;
	int i;
	struct prinfo *userPrinfo;
	int nr=100;
	userPrinfo=(struct prinfo*)malloc(sizeof(struct prinfo)*nr);
	t = syscall(223,userPrinfo,&nr);
	for(i=0;i<t;i++)
	{
		printf("%ld\n",userPrinfo[i].pid);
	}
	printf("num of processes: %ld\n", t);
	return 0;
}
