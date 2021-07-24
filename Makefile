# obj-m:kernelHook.o
# 
# CURRENT_PATH :=$(shell pwd)
# VERSION_NUM :=$(shell uname -r)
# LINUX_PATH :=/usr/src/linux-headers-$(VERSION_NUM) #linuxKernel 源码路径
# 
# -C选项：此选项指定内核源码的位置，make在编译时将会进入内核源码目录，执行编译 ；M=$(CURRENT_PATH)：需要编译的模块源文件地址
# modules默认行为是将源文件编译并生成内核模块
# all:
# make -C $(LINUX_PATH) M=$(CURRENT_PATH) modules # 
# clean:
# make -C $(LINUX_PATH) M=$(CURRENT_PATH) clean

ifeq ($(KERNELRELEASE),)
    KERNDIR = /lib/modules/$(shell uname -r)/build
    PWD     = $(shell pwd)
module:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
else
    modulename = hookTtest
    $(modulename)-objs = kernelHook.o
    obj-m = $(modulename).o
endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module* modules* .cache.mk *.mod
