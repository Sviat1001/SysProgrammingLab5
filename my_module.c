#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define MSG_PREF "TEST: "
#define IOCTL_RESET _IO(0, 1)
#define IOCTL_INC_CMD1 _IOW(0, 2, long)
#define IOCTL_INC_CMD2 _IOW(0, 3, long)
#define IOCTL_INC_CMD3 _IOW(0, 4, long)
#define IOCTL_INC_CMD4 _IOW(0, 5, long)
#define IOCTL_INC_CMD5 _IOW(0, 6, long)
#define IOCTL_PRINT_COUNTS _IO(0, 7)

static long cmd1_count, cmd2_count, cmd3_count, cmd4_count, cmd5_count;

static long my_module_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    long value = 0;

    switch (cmd)
    {
    case IOCTL_RESET:
        cmd1_count = 0;
        cmd2_count = 0;
        cmd3_count = 0;
        cmd4_count = 0;
        cmd5_count = 0;
        printk(KERN_INFO MSG_PREF "Counters reset\n");
        break;

    case IOCTL_INC_CMD1:
        cmd1_count++;
        printk(KERN_INFO MSG_PREF "Counter 1 incremented. Total: %ld\n", cmd1_count);
        break;

    case IOCTL_INC_CMD2:
        cmd2_count++;
        printk(KERN_INFO MSG_PREF "Counter 2 incremented. Total: %ld\n", cmd2_count);
        break;

    case IOCTL_INC_CMD3:
        cmd3_count++;
        printk(KERN_INFO MSG_PREF "Counter 3 incremented. Total: %ld\n", cmd3_count);
        break;

    case IOCTL_INC_CMD4:
        cmd4_count++;
        printk(KERN_INFO MSG_PREF "Counter 4 incremented. Total: %ld\n", cmd4_count);
        break;

    case IOCTL_INC_CMD5:
        cmd5_count++;
        printk(KERN_INFO MSG_PREF "Counter 5 incremented. Total: %ld\n", cmd5_count);
        break;

    case IOCTL_PRINT_COUNTS:
        printk(KERN_INFO MSG_PREF "Counts: %ld %ld %ld %ld %ld\n",
               cmd1_count, cmd2_count, cmd3_count, cmd4_count, cmd5_count);
        break;

    default:
        return -EINVAL;
    }

    if (copy_to_user((long *)arg, &value, sizeof(long)))
        return -EFAULT;

    return 0;
}

static const struct file_operations my_module_fops = {
    .unlocked_ioctl = my_module_ioctl,
};

static int my_module_major;

static int __init my_module_init(void)
{
    my_module_major = register_chrdev(0, "my_module", &my_module_fops);
    if (my_module_major < 0)
    {
        printk(KERN_ERR MSG_PREF "Failed to register a major number\n");
        return my_module_major;
    }

    printk(KERN_INFO MSG_PREF "Module loaded with major number %d\n", my_module_major);
    return 0;
}

static void __exit my_module_exit(void)
{
    unregister_chrdev(my_module_major, "my_module");
    printk(KERN_INFO MSG_PREF "Module unloaded\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
