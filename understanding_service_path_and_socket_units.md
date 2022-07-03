# Understanding Service Path and Socket Units
## review
系统管理员经常会修改现有的单元或者创建新的单元。  
- understanding service units
- understanding socket units
- understanding path units

## understanding service units
服务单元相当于sysv系统上的初始脚本。用来配置各种服务。例如shell、web服务器、邮件服务器等后台程序。  
`man systemd.directives`给出了各个单元参数的目录。  
### service file
[Unit]单元：
- description：描述信息
- After：在某些其他的事情发生之前，我们不希望此服务启动。
- Docmentation：服务文档
- ConditionPathExists：检查文件是否存在，如果以`!`开头则检查是否不存在此文件。
- Wants=：服务的依赖项
- 
要了解单元文件中[Unit]部分可以放置那些内容可以使用命令`man systemd.unit`  

[Service]单元包含只能放在service单元文件中的参数:
- Type:可以在`man systemd.service`中看到集中不同的服务类型.如forking类型,意味着第一个启动的进程将产生子进程.父进程在设置了适当的通信渠道之后会退出,子进程将继续作为主要的服务进程.父进程结束时,systemd service manager会认为该服务已完全启动.
- Environment：设置影响服务行为的环境变量.
- Execstart=,ExecStop=,and ExecReload=:这三行指向了服务的启动可执行文件，并指定命令参数以启动、停止和重新加载服务。
- PrivateTmp：许多服务需要写入一些临时文件，如果为true时，服务会写入私有的`/tmp/Directory`目录,其他人无法访问.
- Restart=：如果服务停止或者中断，可能需要自动重启。这种情况下使用`on-abort`参数,如果服务由于不干净的信号崩溃,systemd会自动重新启动它.
- ExecStartPre=:启动服务之前执行的命令
- KillMode=：停止服务时，是杀掉所有相关进程还是只杀死主服务进程
- RestartPreventExitStatus=：如果收到某个退出码，可以防止服务重启。
- RunTimeDirectory= and RuntimeDirectoryMode=:这两个指令在`/run/Directory`目录下创建运行时目录，然后设置该目录的权限。
- AmbientCapabilities= and CapabilityBoundingSet = ：
[Install]单元:  
- Wantedby=：控制启用或者禁用单元时发生的事。
- Alias=：通过别名控制服务。

## Understanding Socket units
Socket file位于`/lib/systemd/system`目录。socket 单元替代了就得inetd和Xinetd Superserve守护进程。任何socket服务都会从同名的service服务中获取支持。所以socket单元文件中没有设置可执行文件。
### socket file
[Unit]单元：
- Before = ：这告诉systemd在开始此socket之前需要的服务
- Confilicts= ：如果启用了此socket，则不允许此服务参数运行。
[Socket]单元：
- Listenstream=：监听端口号
- Accept= ：该服务将对传入的链接产生一个新的实例。

## understanding path unnits
path单元使systemd监视某个文件货目录以查看其何时发生更改。当systemd检测到文件或者目录发生更改时，将激活指定的服务。
[Unit]单元：
- Description = ：
- PartOf=: 要执行的服务
[Path]单元:
- Pathexists = :监控的文件或者目录
[Install]单元:
- Wantedby=：控制启用或者禁用单元时发生的事。