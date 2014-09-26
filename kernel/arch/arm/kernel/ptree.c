#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/list.h>

asmlinkage long sys_ptree(struct prinfo *buf, int *nr)
{
	long i = 0;
	struct task_struct *par = &init_task;
	struct task_struct *root = par;
	struct list_head *firstch = &par->children;
	struct task_struct *p = list_entry(firstch->next,struct task_struct, sibling);

	struct list_head *ch = &p->children;
	struct list_head *sib = &p->sibling;

	do {
		if (p == par) {
			i ++;
			printk("[%d] %s, parent:%s\n", p->pid, p->comm, p->parent->comm);
			par = p->parent;
			if (&par->children == p->sibling.next)
				p = list_entry(sib->next, struct task_struct, children);
			else
				p = list_entry(sib->next, struct task_struct, sibling);
			ch = &p->children;
			sib = &p->sibling;
		} else if (list_empty(ch)) {
			i ++;
			printk("[%d] %s, parent:%s\n", p->pid, p->comm, p->parent->comm);
			if (&par->children == p->sibling.next)
				p = list_entry(sib->next, struct task_struct, children);
			else
				p = list_entry(sib->next, struct task_struct, sibling);
			ch = &p->children;
			sib = &p->sibling;
		} else {
			par = p;
			p = list_entry(ch->next, struct task_struct, sibling);
			ch = &p->children;
			sib = &p->sibling;
		}
	} while (p != root);	
	return i;
}
