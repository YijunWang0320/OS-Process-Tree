#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

int main(int argc, char **argv) {
	long t;
	struct prinfo *userPrinfo;
	int nr=100;
	userPrinfo=malloc(sizeof(struct prinfo)*nr);
	t = syscall(223,userPrinfo,&nr);
	for(int i=0;i<nr;i++)
	{
		print("%ld\n",userPrinfo[i]->pid);
	}
	printf("num of processes: %ld\n", t);
	return 0;
}
