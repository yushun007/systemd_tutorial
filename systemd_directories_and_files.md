# intor
## configration files
    位于`/etc/systemd/`中，查看每个配置文件的做用使用`man <config_file>`

## systemd unit files
    systemd使用各种类型的单元文件控制系统和服务操作。  
    `/lib/systemd/system`目录是随操作系统或者任何可能安装的安装包的但愿文件的默认位置。  
    `/etc/systemd/system`是自定义单元文件的目录。此目录中具有与上面目录中完全相同的单元文件。  
### Type of unit files
    - service:服务配置文件。
    - socket:sockets可以启用不同系统服务之间的通信，也可以在收到链接请求时自动唤醒睡眠服务
    - slice：配置Cgroup时使用的切片单元
    - target：在系统启动期间使用目标单元,用于分组单元和提供共同的同步点。
    - timer:timer单元用于安排计划运行的作业，取代了就得cron系统。
    - path:路径单元是用于可以通过基于路径激活开始的服务。
    - swap:包含有关交换分区的信息

## systemd executables
    通常的系统的命令可执行文件都在`/bin or /sbin`目录下，systemd也有些在此目录，但是systemd的可执行文件都能在`/lib`目录中找到。  
    最常用的命令`systemctl`用来控制systemd.例如：`systemctl list-units`列出所有单元  