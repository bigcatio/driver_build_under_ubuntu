/* hello.c */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
// MODULE_LICENSE("leo BSD/GPL");

static const struct file_operations hello_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = NULL,
	.open = NULL,
};

int major;
#define HELLO_MAJOR (66)
static int hello_init(void)
{

	printk(KERN_ALERT "Hello, world\n");
	printk("Hello, world\n");
	major = register_chrdev(HELLO_MAJOR, "hello_world", &hello_fops);
	printk(KERN_WARNING "hello_world: register character device %d.", HELLO_MAJOR);
	if (major < 0)
		printk(KERN_WARNING "hello_world: Failed to register character device.");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, Hello world\n");
	printk("Goodbye, Hello world\n");
	printk(KERN_WARNING "hello_world: unregister character device %d.", HELLO_MAJOR);
	unregister_chrdev(HELLO_MAJOR, "hello_world");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("bigcatio");
MODULE_DESCRIPTION("A good start");
MODULE_VERSION("0.0.1");