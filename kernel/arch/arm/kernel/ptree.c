#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>

asmlinkage long sys_ptree(struct prinfo *buf, int *nr)
{
	long i = 0;
	struct task_struct *task;
	
	for_each_process(task)
	{
		i++;
		printk("%s [%d]\n",task->comm , task->pid);
	}
	
	return i;
}
