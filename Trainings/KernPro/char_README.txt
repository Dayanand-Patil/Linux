I'm writing a basic char device driver for Linux kernel. For this, the code flow I have considered is as follows:

    alloc_chrdev_region() -> to use dynamic allocation of major number
    class_create() -> to create device class in sysfs
    device_creat() -> to create device under /dev/
    cdv_init() -> to initialize char device structure
    cdev_add() -> to add my device structure in kernel
