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
static struct cdev hello_device_cdev;
#define MAX_MINORS 256
static int hello_init(void)
{
	int retval;
	dev_t dev = MKDEV(HELLO_MAJOR, 0);

	if ((retval = register_chrdev_region(dev, MAX_MINORS, "hello_world")) != 0)
	{
		pr_err("hello_world: unable to get major %d\n", HELLO_MAJOR);
		return retval;
	}

	cdev_init(&hello_device_cdev, &hello_fops);
	if ((retval = cdev_add(&hello_device_cdev, dev, MAX_MINORS)) != 0)
	{
		pr_err("hello_world: unable register character device\n");
	}

	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, Hello world\n");
	printk("Goodbye, Hello world\n");
	printk(KERN_WARNING "hello_world: unregister character device %d.", HELLO_MAJOR);
	cdev_del(&hello_device_cdev);
	unregister_chrdev_region(MKDEV(HELLO_MAJOR, 0), MAX_MINORS);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("bigcatio");
MODULE_DESCRIPTION("A good start");
MODULE_VERSION("0.0.1");