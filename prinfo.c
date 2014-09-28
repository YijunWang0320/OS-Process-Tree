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
		printf("pid:%ld  ",userPrinfo[i].pid);
		printf("par:%ld:  ",userPrinfo[i].parent_pid);
		printf("fir:%ld:  \n",userPrinfo[i].first_child_pid);
		printf("nex:%ld:  ",userPrinfo[i].next_sibling_pid);
		printf("state:%ld:  ",userPrinfo[i].state);
		printf("uid:%ld:  \n",userPrinfo[i].uid);
		printf("comm:%s\n",userPrinfo[i].comm);
		printf("\n");
	}
	printf("num of processes: %ld\n", t);
	return 0;
}
