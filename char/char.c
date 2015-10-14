#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/slab.h>
MODULE_LICENSE("Dual BSD/GPL");

unsigned int count = 1;
int reg_major = 232;
int reg_minor = 0;
dev_t devNum;
struct cdev *gDev;
struct file_operations *gFile;

int testOpen(struct inode *p, struct file *f)
{
	printk("testOpen\n");
	return 0;
}

ssize_t testRead(struct file *f, char __user *u, size_t s, loff_t *l)
{
	printk("test read\n");
	return 0;
}

ssize_t testWrite(struct file *f, const char __user *u, size_t s, loff_t *l)
{
	printk("test write\n");
	return 0;
}

long testIoctl(struct file *f, unsigned int cmd, unsigned long arg)
{
	printk("test ioctl\n");
	printk("on/off: %d\n", cmd);
	printk("led_num: %d\n", arg);
	return 0;
}

int test_init(void)
{
	devNum = MKDEV(reg_major, reg_minor);
	if(register_chrdev_region(devNum, count, "testchar") == 0){
		printk("register success\n");
	}else{
		return -1;
	}
	
	printk("dev number = %x\n", devNum);
	gDev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
	gFile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);

	gFile->open = testOpen;
	gFile->read = testRead;
	gFile->write = testWrite;
	gFile->unlocked_ioctl = testIoctl;
	gFile->owner = THIS_MODULE;

	cdev_init(gDev, gFile);
	cdev_add(gDev, devNum , 3);
	return 0;
}

void test_exit(void)
{
	cdev_del(gDev);
	unregister_chrdev_region(devNum, count);
	return;
}

module_init(test_init);
module_exit(test_exit);
