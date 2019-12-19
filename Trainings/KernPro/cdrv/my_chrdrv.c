static struct file_operations char_dev_fops = {
	.owner = THIS_MODULE,
	.write = my_write,
	.read = my_read,
	.open = my_open,
	.release = my_release
};

static char *name = "my_driver";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "the name display in /var/log/kern.log");

static int __init my_hello(void)
{
	printk(KERN_INFO, "EBB%d\n", name);
	return 0;
}	

static void __exit my_hello_exit()
{
	printk(KERN_INFO, "ERROR:%d\n", name);
}

module_init(my_hello);
module_init(my_hello_exit);
