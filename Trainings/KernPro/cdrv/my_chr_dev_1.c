static char *name = _NAME_ ;

static int __init chrdv()
{
	pr_err("ERR:%d\n", name);
}

static void __exit chr_exit(void)
{
	pr_err("ERR:");
}

static struct file_operations fops = {
	.open = my_open,
	.read = my_read,
	.write = my_write,
	.release = my_release
};

static char *buf = NULL;
static int msg_len;

static int __init my_init(void)
{
	major = register_chrdev(0, DEVICE_NAME, &fops);
	
	class_name = class_create(THIS_MODULE, CLASS_NAME);
	
	device_create(class_name, NULL, MKDEV(mejor_num, 0), NULL, DEVICE_NAME);



