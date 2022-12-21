#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/moduleparam.h>
module_init(lkm_example_init);
module_exit(lkm_example_exit);
static int capture; 
capture=0;
module_param(capture, int, 0644);
static int __init lkm_example_init(void) {
int pid;int leader;int uid;int comm;
struct task_struct *thisprocess = pid_task(find_vpid(capture), PIDTYPE_PID);
pid=thisprocess->pid;
leader=thisprocess->group_leader->pid;
uid=thisprocess->cred->uid;
printk(KERN_INFO "Process uid: %d\n",uid);
printk(KERN_INFO "Process pgid: %d\n",leader);
printk(KERN_INFO "Process ID: %d\n", pid);
printk(KERN_INFO "Process command path: %s\n",task->comm);
return 4;
}
static void __exit lkm_example_exit(void) {
}
MODULE_LICENSE(“GPL”);