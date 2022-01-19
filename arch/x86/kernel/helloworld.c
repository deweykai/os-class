#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_helloworld(void)
{
	printk(KERN_ALERT "Hello World\n");
	return 0;
}
