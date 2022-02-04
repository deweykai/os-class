#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(helloworld)
{
	printk(KERN_ALERT "Hello World\n");
	return 0;
}
