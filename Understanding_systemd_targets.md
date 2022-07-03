# Understanding systemd Targets
## review
- Understanding the purpose of systemd targets(理解systemd targets 的目的)
- Understanding the structure of a target file
- Comparing systemd targets to sysVinit run levels
- Understanding target dependencies
- Changing the default target
- Temporarily changing the target
## Understanding the purpose of systemd targets
SysVinit系统中具有runlevels，定义了当操作系统进入特定的运行状态时要自动启动的服务。  
目标但是并不是只有runlevels,systemd一个target是一个集合了其他systemd单元的单元。  
targets可以集合的包括servcie，paths，sockets and other targets  
- `systemctl list-units -t target`可以查看当前的激活的target,最后跟`--state inactive`可以查看未激活的target

## Understanding the structure of a target file
- [Unit]:
    - Description = ：描述
    - Documentation = ：文档
- 在`/etc/systemd/system/<target>.target.wants`目录中包含了此target的其他单元。如果其他单元的[Install]中`Wantedby = `字段设置了此target就会在此目录中创建一个软连接到相应的单元。

有些target是没有wants目录的，这些target被硬编码到了`/lib/systemd/systemd`文件中，使用`strings systemd | grep '\.target'`可以看到其中的target单元。这里的target单元并非所有的单元都是被动自动启动的。被动单元会在操作系统启动时自动启动。

## Understanding service templates
在target文件中，[Unit]单元中使用@符号链接的字段，@之前的字段是服务模板，@之后到`.service`之间的字段是具体服务。当在service单元中引用这些模板时使用`%i`,直接可以全部引用。同时在此单元的其他字段也可以使用`%i`表示不同的模板。


## Comparing systemd targets to SysVinit runlevels
sysVinit定义了操作系统到达某个状态时将运行的服务。  
runlevels与systemd target的对应表：
|SysVinit|systemd target |what is does|
|--------|--------------|----------|
|runlevel 0|poweroff.target|It shuts down the operation system|
|runlevel 1|rescue.target|It prevents all services from running and prevents all users excupt for the root user from logging in to the system .all filesystems are mounted normally.It's just a root shell for performing maintenance operations|
|runlevel 2 runlevel 3 runlevel 4|multi-user.target|The operating system is fully operational,without a graphical interface|
|runlevel 5|graphical.target|The operationg system is fully operational with a graphical interface|
|runlevel 6|reboot.target|This is for rebooting the system|

systemd 中一些没有sysvinit对应的目标：
- emergency.target 和rescue.target 第一个是紧急目标，后一个是救援目标，第一个会把所有文件系统设为只读
- hibernate.target 休眠，保存系统状态并关掉电源。
- suspend.target 挂起，和上面一样但是并不断掉电源。

## Understanding target dependencies
- `systemctl list-dependencies <target>`查看target的依赖。最后加上`--after or --before`可以查看启动之前的依赖项和启动之后的依赖项。
- `systemd-analyze dot <target> | dot -Tsvg > <target>.svg`会生成一张依赖图。
- `systemctl get-default`查看默认启动项
- `sudo systemctl isolate multi-user|graphical`临时切换图形或者文本模式
systemd同样对sysvinit样式的runlevels创建了链接，在`/lib/systemd/system`目录中