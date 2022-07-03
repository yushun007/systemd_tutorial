# Understanding Cgroups version 1
## Understanding the purpose of cgroups
使用cgroups，管理员可以：
    - 通过进程或者用户管理资源
    - 跟踪用户在多用户系统上的资源使用情况，已提供准确的计量
    - 更容易彼此隔离运行进程。这不仅可以提高安全性，还可以个更好实现容器化技术
    - 由于更好的资源管理和进程隔离，可以运行更多的虚拟机和容器
    - 白名单和黑名单硬件设备
    - 设置网络流量构建
## understanding the structure of cgroups version 1
几个术语：
    - cgoups：两种含义，我们最关心的是一个cgroups是一个进程集。每个cgoups进程都绑定到cgroups文件系统中定义的限制和参数。
    - service：systemd进程组，由不同的单元配置文件配置。
    - scopes：scope是有某些外部手段启动的进程。虚拟机、容器、用户会话是scope的实例。
    - slices：slices不包含任何进程。相反这是一组分层组织的单位。一个slices管理在socpes或者service中运行的进程，四个默认slices如下：
        - -.slice:这是root slice，他是整个slice层次结构的根。通常不包含任何其他单位。但是可以使用他为整个切片树创建默认设置
        - system.slice:默认情况，systemd启动的系统服务将转到此处
        - users.slice:默认情况下，用户模式服务将进入此处。隐式的为每位用户分配一个slice
        - machine-slice:虚拟机和容器的服务将在此处。
`systemd-cgls`命令展示了系统上运行的CGroups层次列表
## understanding the cgroup filesystem
在任何运行Cgroup的系统上，都可以在`/sys/fs/`看到虚拟文件系统