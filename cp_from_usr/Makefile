obj-m := char.o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(MAKE) orz

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm orz
