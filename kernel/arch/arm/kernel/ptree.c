#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/list.h>
#include <linux/string.h>

asmlinkage long sys_ptree(struct prinfo *buf, int *nr)
{
	long i = 0;
	long zero=0;
	long size=sizeof(struct prinfo);
	int tempNr=0;
	copy_form_user(&tempNr,nr,sizeof(int));
	struct prinfo *tempBuf=(struct prinfo*)kmalloc(size*tempNr,GFP_KERNEL);
	copy_from_user(tempBuf,buf,tempNr);

	read_lock(&tasklist_lock);
	struct task_struct *par = &init_task;
	struct task_struct *root = par;
	struct list_head *firstch = &par->children;
	struct task_struct *p = list_entry(firstch->next,struct task_struct, sibling);

	struct list_head *ch = &p->children;
	struct list_head *sib = &p->sibling;

	do {
		if (p == par) {
			memcpy(&tempBuf[i]->pid,p->pid,sizeof(p->pid));
			memcpy(&tempBuf[i]->parent_pid,p->parent->pid,sizeof(p->parent->pid);
			memcpy(&tempBuf[i]->first_child_pid,p->children.next->pid,sizeof(p->children.next->pid));
			if(p->sibling.next=par->children)
				memcpy(tempBuf[i]->next_sibling_pid,&zero,sizeof(long));
			else
				tempBuf[i]->next_sibling_pid=p->sibling.next->pid;
			tempBuf[i]->state=p->state;
			
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
	read_unlock(&tasklist_lock);
	return i;
}
