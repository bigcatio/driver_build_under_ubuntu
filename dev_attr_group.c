#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/delay.h>

static char sysfs_buff[100] = "my_sysfs_test_string";
static ssize_t show_sys_device(struct device *dev,
                              struct device_attribute *attr, char *buf) //cat命令时,将会调用该函数
{
    return sprintf(buf, "%s\n", sysfs_buff);
}

static ssize_t store_sys_device(struct device *dev,
                             struct device_attribute *attr,
                             const char *buf, size_t count) //echo命令时,将会调用该函数
{
    sprintf(sysfs_buff, "%s", buf);
    return count;
}

//定义多个sys_device_file的设备属性文件

static DEVICE_ATTR(sys_device_file, S_IWUSR | S_IRUSR, show_sys_device, store_sys_device);
static DEVICE_ATTR(sys_device_file0, S_IWUSR | S_IRUSR, show_sys_device, store_sys_device);
static DEVICE_ATTR(sys_device_file1, S_IWUSR | S_IRUSR, show_sys_device, store_sys_device);
static DEVICE_ATTR(sys_device_file2, S_IWUSR | S_IRUSR, show_sys_device, store_sys_device);

static struct attribute *sys_device_attributes[] = {
    &dev_attr_sys_device_file.attr,
    &dev_attr_sys_device_file0.attr,
    &dev_attr_sys_device_file1.attr,
    &dev_attr_sys_device_file2.attr,
    NULL////属性结构体数组最后一项必须以NULL结尾。
};

static const struct attribute_group sys_device_attr_group = {
    .attrs = sys_device_attributes,
};

struct file_operations mytest_ops = {
    .owner = THIS_MODULE,
};

static int major;
static struct class *cls;
struct device *mydev;
static int mytest_init(void)
{
    
    major = register_chrdev(0, "mytest", &mytest_ops);
    cls = class_create(THIS_MODULE, "mytest_class");
    mydev = device_create(cls, 0, MKDEV(major, 0), NULL, "mytest_device"); //创建mytest_device设备

    if (sysfs_create_group(&(mydev->kobj), &sys_device_attr_group))
    { 
        //在mytest_device设备目录下创建多个sys_device_file属性文件
        return -1;
    }

    return 0;
}

static void mytest_exit(void)
{
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, "mytest");
    sysfs_remove_group(&(mydev->kobj), &sys_device_attr_group);
}

module_init(mytest_init);
module_exit(mytest_exit);
MODULE_LICENSE("GPL");
