#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/moduleparam.h>
//module_init(lkm_example_init);
//module_exit(lkm_example_exit);
static int capture=0;
module_param(capture, int, 0644);
static int __init lkm_example_init(void) {
int pid;int leader;int uid;int comm;
struct task_struct *thisprocess = pid_task(find_vpid(capture), PIDTYPE_PID);
pid=thisprocess->pid;
leader=thisprocess->group_leader->pid;
printk(KERN_INFO "The pid of the process is: %d\n",pid);
printk(KERN_INFO "The process group id is: %d\n",leader);
printk(KERN_INFO "The process UID is: %d\n", thisprocess->cred->uid);
printk(KERN_INFO "The command path of the process is: %s\n",thisprocess->comm);
return 0;
}
//module_init(lkm_example_init);
//module_exit(lkm_example_exit);
static void __exit lkm_example_exit(void) {
}
module_init(lkm_example_init);
module_exit(lkm_example_exit);
MODULE_LICENSE(“GPL”);