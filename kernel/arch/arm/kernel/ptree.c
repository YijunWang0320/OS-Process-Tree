#include <linux/syscalls.h>
#include <linux/kernel.h>

asmlinkage long ptree(struct prinfo *buf, int *nr)
{
	printk("successful print!~");
	return 123;
}
