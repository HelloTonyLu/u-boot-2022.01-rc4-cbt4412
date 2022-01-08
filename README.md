修改者：HelloTonyLu

代码适合的开发板：

cbt4412或者友善之臂Tiny4412或类似的板子。

CPU处理器：Samsung ARM Cortex-A9 四核Exynos 4412 Quad-core处理器

DDR3 RAM内存： 1G

FLASH存储：4G eMMC

编译方法：

ARCH=arm && CROSS_COMPILE=arm-none-linux-gnueabihf- && export ARCH CROSS_COMPILE

make distclean && make cbt4412_defconfig && make
