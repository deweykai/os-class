#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>

asmlinkage long sys_3753add(int a, int b, int *result)
{
	int c = a + b;
	printk(KERN_INFO "calculating %d + %d = %d\n", a, b, c);
	copy_to_user(result, &c, 1);
	return 0;
}
