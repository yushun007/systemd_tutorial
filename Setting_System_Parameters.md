# Setting System Parameters
## overview
使用systemd实用程序来设置过去必须通过编辑配置文件或创建符号链接来设置的某些参数。
- Setting the locale parameter
- Setting time and zone parameters
- Setting the hostname and machine information

## Setting the local parameter
语言环境是一组参数，它们定义了对用户可能很重要的内容。用户的首选语言，字符编码，货币格式等。
- `localctl`查看默认语言环境设置
- `localectl list-locales`查看系统支持的语言环境
- `sudo localctl set-locale <local>`设置语言环境
- `sudo localctl set-keymap <local>`设置键盘位
- `sudo localctl set-x11-keymap <local>`设置键盘位
这些设置都是`systemd-localed.service`在工作.

## Setting time and timezone parameter
- `timedatectl`查看时间
- `timedatectl list-tiemzones`显示所有可用的时区
- `timedatectl set-timezone <timezone>`设置时区


## setting the hostname and machine information
- `cat /etc/hostname`查看主机名
- `hostnamectl`查看主机名
- `sudo hostnamectl set-hostname "<hostname>"`设置主机名