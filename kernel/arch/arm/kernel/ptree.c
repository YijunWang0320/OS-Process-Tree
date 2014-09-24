#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/init_task.h>

asmlinkage long sys_ptree(struct prinfo *buf, int *nr)
{
	read_lock(&tasklist_lock);
	long i = 0;
	struct task_struct *p = &init_task;
	struct task_struct *par = NULL;

	struct list_head *ch = &p->children;
	struct list_head *sib = &p->sibling;
	do {
		if (p == par) {
			i ++;
			par = p->parent;
			p = list_entry(sib->next, struct task_struct, sibling);
			ch = &p->children;
			sib = &p->sibling;
		} else if (ch->next == ch) {
			i ++;
			p = list_entry(sib->next, struct task_struct, sibling);
			ch = &p->children;
			sib = &p->sibling;
		} else if (ch->next != ch) {
			i ++;
			par = p;
			p = list_entry(ch->next, struct task_struct, children);
			ch = &p->children;
			sib = &p->sibling;
		} else
			return -1;
	} while (p != &init_task);
	read_unlock(&tasklist_lock);
	return i;
}
