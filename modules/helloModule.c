#include<linux/init.h>
#include<linux/module.h>

MODULE_AUTHOR("Kai Dewey");
MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

int hello_init(void) {
    printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
    return 0;
}

void hello_exit(void) {
    printk(KERN_ALERT "inside %s function\n",__FUNCTION__);
}

module_init(hello_init);
module_exit(hello_exit);
