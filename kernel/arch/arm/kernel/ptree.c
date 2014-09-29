#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
#include <linux/list.h>
#include <linux/string.h>
#include <linux/uaccess.h>

void doCopy(struct prinfo *tempBuf, struct task_struct *p, struct task_struct *par, int i)
{
	tempBuf[i].pid = p->pid;
	tempBuf[i].parent_pid = p->parent->pid;
	tempBuf[i].state = p->state;
	strcpy(tempBuf[i].comm, p->comm);
	tempBuf[i].uid = p->real_cred->uid;
	if( p == par) {
		struct task_struct *chp, *realp;

		realp = p->parent;
		chp = list_entry(p->children.next, struct task_struct, sibling);
		tempBuf[i].first_child_pid = chp->pid;
		printk("tempBuf[i].first_child_pid = chp->pid: %ld \n", chp->pid);//test
		if (&realp->children == p->sibling.next)
			tempBuf[i].next_sibling_pid = 0;
		else {
			struct task_struct *sib;

			sib = list_entry(p->sibling.next, struct task_struct, sibling);
			tempBuf[i].next_sibling_pid = sib->pid;
		}
	} else if (list_empty(&p->children)) {
		tempBuf[i].first_child_pid = 0;
		if (&par->children == p->sibling.next)
			tempBuf[i].next_sibling_pid = 0;
		else {
			struct task_struct *sib;

			sib = list_entry(p->sibling.next, struct task_struct, sibling);
			tempBuf[i].next_sibling_pid = sib->pid;
		}
	}
	/*tempBuf[i].pid = p->pid;
	if(p->parent->pid != p->pid)
		tempBuf[i].parent_pid=par->pid;
	else
		tempBuf[i].parent_pid=0;
	if(list_empty(&p->children))
		tempBuf[i].first_child_pid=0;
	else
		tempBuf[i].first_child_pid=list_entry(p->children.next,struct task_struct,sibling)->pid;
	tempBuf[i].state=p->state;
	if(p->sibling.next==&par->children)
		tempBuf[i].next_sibling_pid=0;
	else
		tempBuf[i].next_sibling_pid=sib->pid;
	tempBuf[i].uid=p->real_cred->uid;
	strcpy(&tempBuf[i].comm,&p->comm);
	return;
	*/
}

asmlinkage long sys_ptree(struct prinfo *buf, int *nr)
{
	long i = 0;
	long zero=0;
	int returnVal=10;
	long size=sizeof(struct prinfo);
	int tempNr=0;
	copy_from_user(&tempNr,nr,sizeof(int));
        struct prinfo *tempBuf=(struct prinfo*)kmalloc(size*tempNr,GFP_KERNEL);
	copy_from_user(tempBuf,buf,tempNr*sizeof(struct prinfo));

	read_lock(&tasklist_lock);
	struct task_struct *par = &init_task;
	struct task_struct *root = par;
	struct list_head *firstch = &par->children;
	struct task_struct *p = list_entry(firstch->next,struct task_struct, sibling);

	struct list_head *ch = &p->children;
	struct list_head *sib = &p->sibling;

	do {
		if (p == par) {
			doCopy(tempBuf,p,par,i);
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
			doCopy(tempBuf,p,par,i);
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
	copy_to_user(buf,tempBuf,i*sizeof(struct prinfo));
	return i;
}
