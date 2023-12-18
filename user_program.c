#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define BUF_SIZE 128
#define IOCTL_RESET _IO(0, 1)
#define IOCTL_INC_CMD1 _IOW(0, 2, long)
#define IOCTL_INC_CMD2 _IOW(0, 3, long)
#define IOCTL_INC_CMD3 _IOW(0, 4, long)
#define IOCTL_INC_CMD4 _IOW(0, 5, long)
#define IOCTL_INC_CMD5 _IOW(0, 6, long)
#define IOCTL_PRINT_COUNTS _IO(0, 7)

int main()
{
    int fd;

    fd = open("/dev/my_module", O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open /dev/my_module");
        return EXIT_FAILURE;
    }

    long value = 0;

    int choice;
    do
    {
        printf("Menu:\n");
        printf("1. Reset Counters\n");
        printf("2. Increment Counter 1\n");
        printf("3. Increment Counter 2\n");
        printf("4. Increment Counter 3\n");
        printf("5. Increment Counter 4\n");
        printf("6. Increment Counter 5\n");
        printf("7. Print Counters\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            ioctl(fd, IOCTL_RESET);
            printf("Counters reset.\n");
            break;
        case 2:
            ioctl(fd, IOCTL_INC_CMD1, &value);
            printf("Counter 1 incremented.\n");
            break;
        case 3:
            ioctl(fd, IOCTL_INC_CMD2, &value);
            printf("Counter 2 incremented.\n");
            break;
        case 4:
            ioctl(fd, IOCTL_INC_CMD3, &value);
            printf("Counter 3 incremented.\n");
            break;
        case 5:
            ioctl(fd, IOCTL_INC_CMD4, &value);
            printf("Counter 4 incremented.\n");
            break;
        case 6:
            ioctl(fd, IOCTL_INC_CMD5, &value);
            printf("Counter 5 incremented.\n");
            break;
        case 7:
            ioctl(fd, IOCTL_PRINT_COUNTS);
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }

    } while (choice != 0);

    close(fd);

    return EXIT_SUCCESS;
}
