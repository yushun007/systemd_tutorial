# Understanding the systemd boot process
## review
- comparing sysv and systemd bootup
- analyzing bootup performance
- some differences on ubuntu server 20.04
- understanding systemd generators

## Comparing sysv bootup and systemd bootup
### similarities
每个计算机在上电之后都会访问MBR分区并开始加载，在`/boot`目录中有一个压缩的linux内核文件，通常为`VMlinux`。通常还会有一个RAM镜像，通常会以`initramfs or initrd`命名，此过程的第一步是解压内核，并加载到内存中，但是此时内核仍然无法访问跟文件系统，因为没有合适的驱动程序，下一步就是加载RAM镜像中的驱动程序，这会创建一个临时的根文件系统,可以访问内核。一旦内核加载了合适的驱动程序，ram镜像将被卸载。然后启动程序将继续访问根文件系统上的任何需要访问的文件。
### sysv bootup
init进程，PID总是1的第一个进程。此进程将使用`/etc/`目录下的一系列复杂的脚本启动其余的进程。
### systemd bootup
systemd进程的PID也是1,systemd进程启动后，会查看`default.target`文件，再systemd确定了默认启动目标之后，会按照：`local-fs-pre.target local-fs.target sysinit.target basic.target multi-user.target graphical.target(if enable)`的顺序启动目标

## analyze bootup performance
- `systemd-analyze`显示kernel和图形界面的加载耗时  
- `systemd-analyze blame`显示所有服务启动时间
- `systemd-analyze cirtical-chian`显示所有target启动时间

## understanding systemd generators
### understanding mount units
[Mount]:
- What=:文件系统名
- Where=：挂在路径
- Type= ：同What
- Options= mode = ：权限，还有其他的选项