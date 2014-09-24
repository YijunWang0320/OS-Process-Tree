#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/init_task.h>

asmlinkage long sys_ptree(struct prinfo *buf, int *nr)
{
	int i = 0;
	struct task_struct *p = &init_task;
	struct task_struct *par = NULL;

	list_head ch = p->children;
	list_head sib = p->sibling;
	do {
		if (p == par) {
			i ++;
			par = p->parent;
			p = list_entry(sib, struct task_struck, sibling);
			ch = p->children;
			sib = p->sibling;
		} else if (ch->next == ch) {
			i ++;
			p = list_entry(sib, struct task_struck, sibling);
			ch = p->children;
			sib = p->sibling;
		} else if (ch->next != ch) {
			par = p;
			p = list_entry(ch, struct task_struck, children);
			ch = p->children;
			sib = p->sibling;
		}
	} while (p != &init_task);
	return i;
}
