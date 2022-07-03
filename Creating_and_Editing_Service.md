# Creating and editing Services
## Review
- Editing an existing service
- Creating a new service
- Changing the default systemd editor
- Creating a new container service with podman

## Editing an existing service
服务的加载目录是`/lib/systemd/system/`目录，我们可以在此目录下修改创建服务，但是如果系统升级可能会覆盖我们的服务。所以我们应该在`/etc/systemd/system/`目录下创建和编辑服务文件。
- `sudo systemctl edit <service>`此命令会在`/etc/systemd/system/<service>.<unit>.d/`目录下创建一个`override.conf`文件,然后将需要修改的部分添加到此文件中.
## Creating a partial edit to the [Service] section
- `systemd-analyze sercurity <service>`查看服务的安全设置。
- 修改`protectHome=`选项可以设置服务对`/root /home /run/user`等目录的写入。修改`protectSystem=`设置会设置服务对`/dev /proc /sys/`目录的写入权限。

## Creating a full edit
- `systemctl edit --full <service>`修改或者删除已有的配置

## Creating a new service
- `systemctl edit --force --full <service>`会在`/etc/systemd/system`目录创建一个服务文件。

## Changing the default systemd edit
- `sudo EDITOR=vim systemctl edit --fall <service>`也就是改变系统默认编辑器。临时改变
- 永久改变`.bashrc`文件中添加`SYSTEMD_EDITOR=vim`然后`sudo visudo`添加一行`Defaults env_keeps += "SYSTEMD_EDITOR"`