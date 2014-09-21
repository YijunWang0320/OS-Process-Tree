#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>

int main(int argc, char **argv) {
	pid_t t;
	t = syscall(223, NULL, NULL);	
	return 0;
}
