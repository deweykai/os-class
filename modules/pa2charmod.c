#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kernel.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define DEV_NAME "PA2"

MODULE_AUTHOR("Kai Dewey");
MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

#define BUF_SIZE 1024

static char* module_buf;

static int majorNumber;
static int open_count;
static int close_count;

static int     my_open (struct inode *, struct file *);
static int     my_close (struct inode *, struct file *);
static ssize_t my_read (struct file *, char __user *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);
static loff_t  my_seek(struct file *, loff_t, int);

static const struct file_operations my_fops = {
	.owner   = THIS_MODULE,
	.open    = my_open,       // int my_open  (struct inode *, struct file *);
	.release = my_close,      // int my_close (struct inode *, struct file *);
	.read    = my_read,       // ssize_t my_read  (struct file *, char __user *, size_t, loff_t *);
	.write   = my_write,      // ssize_t my_write (struct file *, const char __user *, size_t, loff_t *);
	.llseek  = my_seek        // loff_t  my_seek  (struct file *, loff_t, int);
};

static int __init pa2char_init(void)
{
	printk(KERN_INFO "PA2: hello\n");
	module_buf = kmalloc(BUF_SIZE, GFP_KERNEL);
	majorNumber = register_chrdev(0, DEV_NAME, &my_fops);
	printk(KERN_INFO "PA2: major number %d\n", majorNumber);
	open_count = 0;
	close_count = 0;
	return 0;
}

static void __exit pa2char_exit(void)
{
	printk(KERN_INFO "PA2: goodbye\n");
	kfree(module_buf);
	unregister_chrdev(majorNumber, DEV_NAME);
}


static int my_open (struct inode *inode, struct file *file)
{
	open_count++;
	printk(KERN_INFO "PA2: opened %d times\n", open_count);
	return 0;
}

static int my_close (struct inode *inode, struct file *file)
{
	close_count++;
	printk(KERN_INFO "PA2: closed %d times\n", open_count);
	return 0;
}

static int my_min(int a, int b) {
	if (a > b) {
		return b;
	} else {
		return a;
	}
}

static ssize_t my_read (struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	int num_bytes = my_min(BUF_SIZE - *offset, count);
	int err = copy_to_user(buf, module_buf, num_bytes);	
	if (err != 0) {
		return err;	
	}
	*offset += num_bytes;
	printk(KERN_INFO "PA2: read %d bytes\n", num_bytes);
	return num_bytes;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	int num_bytes = my_min(BUF_SIZE - *offset, count);
	int err = copy_from_user(module_buf, buf, num_bytes);
	if (err != 0) {
		return -EFAULT;
	}
	*offset += num_bytes;
	printk(KERN_INFO "PA2: write %d bytes\n", num_bytes);
	return num_bytes;
}

static loff_t my_seek(struct file *file, loff_t offset, int whence)
{
	loff_t new_pos = offset;
	switch (whence) {
		case 0: // SEEK_SEt
			new_pos = offset;
			break;
		case 1: // SEEK_CUR
			new_pos += offset;
			break;
		case 2: // SEEK_END
			new_pos = BUF_SIZE + offset;
			break;
	}
	if (new_pos < 0 || new_pos > BUF_SIZE) {
		return -1;
	} else {
		return new_pos;
	}
}

module_init(pa2char_init);
module_exit(pa2char_exit);
