# Understanding systemd timers

## review
- Comparing systemd timers with cron
- Understading timer options
- Creating timers

## Comparing systemd timers with cron
cron存在于类Unix操作系统中，而systemd只存在于linux中。

## Viewing timer information
- `systemctl list-unit-files -t timer`查看timer单元。
- `systemctl list-timers`显示了6个字段

## Understanding timer options
[Timer]:
    - OnbootSec = :启动后的时间
    - OnUnitInactiveSec = :单元激活后的时间
    - Unit = ：运行的单元

## Creating timers
创建一个计时器需要两个阶段，第一个阶段是创建计时器启动的服务，另一个是创建计时器。  
这里有个需要注意的地方，在为root用户创建计时器时需要使用`sudo`权限，然后执行`systemctl edit --full --force <unit>`,如果是为用户权限创建则要使用`systemctl edit --user --full --force <unit>`同时在[Install]单元的`WantedBy`字段中需要包含`default.taget`配置

