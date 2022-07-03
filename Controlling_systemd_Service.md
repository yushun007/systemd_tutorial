# Controlling Systemd Service
## Review
- Verifying the status of a service 验证服务状态
- Starting Stopping and reloading service
- Enabling and disabling service 开启和不开启服务
- Killing a service
- Masking service 屏蔽服务
## Verifying the status of a service 验证服务状态
- `systemctl is-enabled <service>`命令可以验证服务是否开启
- `systemctl is-active <service>`命令可以验证服务是否激活
- `systemctl status <service>`同时查看是否开启和激活

## Starting Stopping and reloading services
- `systemctl start <service>`命令激活一个服务(这里可以激活一个被禁用的服务)
- `systemctl stop <service>`命令停止一个服务
- `systemctl reload <service>`命令重新激活一个服务(当修改了一个服务的配置文件之后需要重新激活这个服务)
TODO：添加一个自定义个的例子，分别通过systemd命令启动和shell命令启动停止和重启服务，然后查看状态。

## Enabling and disabling services
- `sudo systemctl enable <service>`命令启用一个服务，使其在系统启动时自动激活
    - 当启用一个服务时，我们将在`/etc/systemd/system/multi-user.target.wants/`中创建一个服务链接指向我们开启的服务.注意：此目录正是我们在[Install]单元中看到的目录。启用之后，并不会立即激活服务，仍然需要手动激活或者重启计算机。或者使用`--now`参数启用之后立即激活服务.
- `sudo systemctl disable <service>`命令禁用一个服务,使其在系统启动时不激活
    - 操作与启用命令相反。会删除符号链接，如果有参数`--now`则立即杀死服务。
- `sudo systemctl kill <service>`命令杀死一个服务，此命令和`kill`一样默认发送15或者SIGTERM信号，如果需要发送其他信号使用参数`-s`发送其他信号.

## Msking a service
- `sudo systemctl mask <service>`屏蔽一个服务使其永远无法激活。
- `sudo systemctl unmask <service>`解除屏蔽