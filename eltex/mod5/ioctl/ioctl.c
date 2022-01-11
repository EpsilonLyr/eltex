#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include <linux/ioctl.h>

#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
 
int32_t value = 0;
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;

static int __init ioctl_init(void);
static void __exit ioctl_exit(void);
static long ioctl_read_write(struct file *file, unsigned int cmd, unsigned long arg);


static struct file_operations fops ={
        unlocked_ioctl: ioctl_read_write
};

static long ioctl_read_write(struct file *file, unsigned int cmd, unsigned long arg){
         switch(cmd) {
                case WR_VALUE:
			if(copy_from_user(&value ,(int32_t*) arg, sizeof(value)) ){
				pr_err("Data Write : Err!\n");
			}
			break;
                case RD_VALUE:
			if(copy_to_user((int32_t*) arg, &value, sizeof(value)) ) {
				pr_err("Data Read : Err\n");
			}
			break;
                default:
			pr_info("Default\n");
			break;
        }
	return 0;
}
 

static int __init ioctl_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
                pr_err("Cannot allocate major number\n");
                return -1;
        }
	pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&etx_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&etx_cdev,dev,1)) < 0){
		pr_err("Cannot add the device to the system\n");
		unregister_chrdev_region(dev,1);
		return -1;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL){
		pr_err("Cannot create the struct class\n");
		unregister_chrdev_region(dev,1);
		return -1;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"mydev")) == NULL){
		pr_err("Cannot create the Device 1\n");
		class_destroy(dev_class);
		unregister_chrdev_region(dev,1);
		return -1;
        }
        return 0;
 
}

static void __exit ioctl_exit(void){
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&etx_cdev);
	unregister_chrdev_region(dev, 1);
}


MODULE_LICENSE("GPL"); 
module_init(ioctl_init);
module_exit(ioctl_exit);
 

