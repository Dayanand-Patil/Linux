#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MAJORNO 190
#define MINORNO  0
#define CHAR_DEV_NAME "vDev1"
#define SUCCESS 0

/*
you can use either:

struct cdev my_cdev;

in this case you don't need to call cdev_alloc because memory is already allocated. 
Instead you must call cdev_init(&my_cdev, &fops). and then my_cdev.owner = THIS_MODULE;

OR

you can use:

struct cdev *my_cdev_p;

in this case you must call cdev_alloc() to allocate memory. 
Then, you have to initialize my_cdev_p->ops=&fops; and my_cdev_p->owner = THIS_MODULE;. Never use cdev_init() in this case!
*/

static struct cdev *veda_cdev; //char device structure
static dev_t mydev; //for device id--(mejor+minor)
static int count = 1, inuse = 0;

static int char_dev_open(struct inode *inode, struct file *file)
{
	if (inuse) {
		pr_err("Device busy %s", CHAR_DEV_NAME);
		return -EBUSY;
	}
	inuse = 1;
	pr_info("Open operation invoked");
	return SUCCESS;
}

static int char_dev_release(struct inode *inode, struct file *file)
{
	inuse = 0;
	return SUCCESS;
}

static ssize_t char_dev_write(struct file *file, const char __user * buf,
			      size_t lbuf, loff_t * offset)
{
	pr_info("Rec'vd data : %s, of len=%ld\n", buf, lbuf);
	return lbuf;
}

static struct file_operations char_dev_fops = { 
	.owner = THIS_MODULE,
	.write = char_dev_write,
	.open = char_dev_open,
	.release = char_dev_release
};
/* end of driver code */



/* Register Driver with I/O abstraction layer
 *
 *  step 1: Reserve Driver/Device ID.
 *  step 2: Register file operations with devtmpfs
 *
*/
static int __init char_dev_init(void)
{
	int ret;
	mydev = MKDEV(MAJORNO, MINORNO);  //device id -- mejor(12-bit) + minor(20-bit)
	
	// register 'count' no. of devices with mejor no. they all are uniqely identified thr minor number
	register_chrdev_region(mydev, count, CHAR_DEV_NAME);

	/* Allocate cdev instance */
	veda_cdev = cdev_alloc();  //allocate meomory for char device structure 

	/* initialize cdev with fops object */
	cdev_init(veda_cdev, &char_dev_fops);  // operation to device

	/* register cdev with vfs(devtmpfs) */
	ret = cdev_add(veda_cdev, mydev, count);
	if (ret < 0) {
		pr_err("Error registering device driver");
		return ret;
	}
	pr_info("Device Registered %s", CHAR_DEV_NAME);
	return SUCCESS;
}

/* de-register driver  */
static void __exit char_dev_exit(void)
{
	/* remove cdev */
	cdev_del(veda_cdev);

	/* free major/minor no's used */
	unregister_chrdev_region(mydev, count);
	pr_info("Driver unregistered");
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_AUTHOR("www.techveda.org");
MODULE_DESCRIPTION("LKD_CW: Character Device Driver - Test");
MODULE_LICENSE("GPL");
/* End of code */
