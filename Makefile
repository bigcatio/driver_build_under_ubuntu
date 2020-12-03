obj-m += char_hello_register_chrdev_statically.o \
         char_hello_register_chrdev_dynamically.o \
         char_hello_register_chrdev_alloc.o \
         char_hello_register_chrdev_region.o\
         dev_attr_file.o dev_attr_group.o module_param.o

CURRENT_PATH:=$(shell pwd)
LINUX_KERNEL_PATH:=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	$(MAKE) -C $(LINUX_KERNEL_PATH)  M=$(CURRENT_PATH) clean
