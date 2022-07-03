# Understanding shutdown and reboot commands
## overview
- Shutting down with systemctl
- Halting with systemctl
- Rebooting with systemctl
- Using shutdown instead of systemctl

## shutting down with systemdctl
- `systemctl poweroff`断电关机
## Halting with systemctl
- `systemctl halt`停止机器但是不断电

## Rebooting with systemctl
- `systemctl reboot`重启

# running a job before shutting down
添加一个service，在service中添加`Before=poweroff.target halt.target shutdown.target`使得其在这三个目标之前运行。