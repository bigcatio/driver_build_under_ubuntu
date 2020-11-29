#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/delay.h>

static char *sysfs_string= "my_sysfs_test_string";
static int sysfs_int= 111;
static long sysfs_long= 222;
static short sysfs_short= 333;
static unsigned int sysfs_uint= 444;
static unsigned long sysfs_ulong= 555;
static unsigned short sysfs_ushort= 666;
static bool sysfs_bool= 777;
static bool sysfs_invbool= 888;

module_param(sysfs_string, charp, 00644);
module_param(sysfs_int, int, 00644);
module_param(sysfs_long, long, 00644);
module_param(sysfs_short, short, 00644);
module_param(sysfs_uint, uint, 00644);
module_param(sysfs_ulong,ulong, 00644);
module_param(sysfs_ushort,ushort, 00644);
module_param(sysfs_bool,bool, 00644);
module_param(sysfs_invbool,invbool, 00644);

static int sysfs_int_array[]= {1,2,3,4,5,6,7,8};
module_param_array(sysfs_int_array, int, NULL, S_IRUSR|S_IWUSR);

 
/*----------------------Module_param_cb()--------------------------------*/
static int cb_valueETX = 999;
int notify_param(const char *val, const struct kernel_param *kp)
{
        int res = param_set_int(val, kp); // Use helper for write variable
        if(res==0) {
                printk(KERN_INFO "Call back function called...\n");
                printk(KERN_INFO "New value of cb_valueETX = %d\n", cb_valueETX);
                return 0;
        }
        return -1;
}
 
const struct kernel_param_ops my_param_ops = 
{
        .set = &notify_param, // Use our setter ...
        .get = &param_get_int, // .. and standard getter
};
 
module_param_cb(cb_valueETX, &my_param_ops, &cb_valueETX, S_IRUGO|S_IWUSR );
/*-------------------------------------------------------------------------*/

static int mytest_init(void)
{

    printk("sysfs_buff=%s\n", sysfs_string);
    return 0;
}

static void mytest_exit(void)
{

}

module_init(mytest_init);
module_exit(mytest_exit);
MODULE_LICENSE("GPL");
