obj-m := my_module.o
USER_PROG := user_program

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc $(USER_PROG).c -o $(USER_PROG)

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -f $(USER_PROG)
