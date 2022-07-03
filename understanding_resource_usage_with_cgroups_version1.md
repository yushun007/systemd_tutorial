# Controlling resource usage with cgroups version 1
## overview
- understanding resource controllers
- Controlling CPU usage
- Controlling memory usage
- Controlling blkio usage
- Understanding pam_limits and ulimit

## understanding resource contrlloers
### Examming the resource controllers
`sudo apt install cgroup-tools`安装cgroup工具  
`lssubsys`查看活动的资源控制器
- cpuset:如果在多核系统上运行linux，则可将进程分配给一个特定的CPU核心或者一组CPU核心。这样可以减少因为进程从一个CPU转移到另一个CPU而造成的内存访问。
- cpu,cpuacct:控制进程或者用户的cpu使用率。
- blkio：块输入输出，设置限制进程或者用户从块设备读写的速度。
- memory：进程或者用户使用内存的限制
- devices：配置系统设备
- freezer：允许将运行进程暂停在cgroup中。
- net-cls,net_prio:可以将标签放在网络数据包上，是的Linux的流量控制器和Linux防火墙可以使用这些标签来控制和确定各种CGroup的网络流量。
- perf_event:用来监控cgroups性能的工具
- hugetlb：允许cgroup使用巨大的虚拟内存页，并在使用时限制
- pids：限制可以在cgroup中运行的过程数量。
- rdma：远程直接内存访问，允许一台计算机访问另一台计算机的内存，二无需设计任何计算机的操作系统。主要用于并行计算簇。
## Controlling CPU usage
`systemctl set-property`或者systemd单元文件，配置CPU资源控制器来处理他。 
`stress-ng -c <cpu_numbers>`使用stress-ng跑满CPU
`top`可以看到cpu的使用率
`systemd-cgls`查看用户slice
`sudo systemctl set-property <slice_name>.slice CPUQuota=<number>%`使用systemd设置cpu限制，并在`/etc/systemd`目录下创建了一个新的文件。
`sudo systemctl deamon-reload`重新加载systemd服务进程。
`sudo systemctl set-property <slice_name>.slice CPUQuota=<number>%`创建了一个system.control目录，并在此目录中创建了一个slice.d目录，在slice.d目录中有创建了一个CPUQuota.conf的配置文件。同时我们在`/sys/fs/cgroup/cpu/user.slice/<user_slice_name>.slice`目录中可以看到一个`cpu.cfs_quota_us`的文件并且已经被设置。

## Setting a blkio limit 
`sudo apt install iotop`用来测量带宽
`dd if=/dev/zero of=afile bs=1M count=10000`创建一个简单的全为零的文件
`dd if=afile of=/dev/null`
`sudo systemctl set-property <user_slice_name>.slice BlockIOReadBandWidth="<root dir mounted path> 1M"`限制根目录硬盘的读写速度，这个操作同样会在`/etc/systemd/system.control`目录创建配置文件，`systemctl deamon-reload`之后在`/sys/fs/cgroup/blkio/user.slice/user<number>.slice`目录下的文件会被写入带宽限制。

## Understanding pam_limits and ulimit
pam_limits模式是Pluggable authentication Modules(可插入身份验证模块系统)的一部分。它可以使得在用户或者组上设置的限制为非易失性的。可以通过编辑`/etc/security/limits.d`目录，`/etc/security/limits.conf`文件中的注释和示例展示了其使用方法。