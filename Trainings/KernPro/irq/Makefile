obj-m :=inttest.o
obj-m +=inttest1.o
obj-m +=tasklet_ex.o
obj-m +=tasklet_ex2.o
obj-m +=tasklet_ex3.o
obj-m +=tasklet_ex4.o
obj-m +=tbh.o
obj-m +=intthread.o
#obj-m +=key_press.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean: 
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
