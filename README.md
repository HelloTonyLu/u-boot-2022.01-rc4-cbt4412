修改者：HelloTonyLu

代码适合的开发板：

cbt4412或者友善之臂Tiny4412或类似的板子。

CPU处理器：Samsung ARM Cortex-A9 四核Exynos 4412 Quad-core处理器

DDR3 SDRAM内存： 1G

FLASH存储：8G eMMC NandFlash

编译方法：

ARCH=arm && CROSS_COMPILE=arm-none-linux-gnueabihf- && export ARCH CROSS_COMPILE

make distclean && make cbt4412_defconfig && make

分支介绍：

1、master：初步移植成功的u-boot-2022.01-rc4代码，可以从SD卡启动U-Boot。对应博文是：《为Exynos4412移植2022版U-Boot的步骤及其原理分析》https://blog.csdn.net/weixin_42408707/article/details/122376553

2、DM9000：移植DM9000A驱动，实现了tftp烧写kernel。对应博文是：
①《为Exynos4412移植2022版U-Boot（二）支持DM9000网卡》https://blog.csdn.net/weixin_42408707/article/details/122099170
②《Exynos4412 Linux Kernel 5.15移植过程记录（一）——编译内核的准备工作》https://blog.csdn.net/weixin_42408707/article/details/122515910
③《Exynos4412 Linux Kernel 5.15移植过程记录（二）——解决U-Boot启动内核，卡在Starting kernel的问题》https://blog.csdn.net/weixin_42408707/article/details/122519116
