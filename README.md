- [笔记目录](#笔记目录)
- [Vscode Git](#vscode-git)
  - [vscode git配置](#vscode-git配置)
    - [ssh配置](#ssh配置)
    - [vscode 源代码管理配置](#vscode-源代码管理配置)
    - [配置可能遇到的问题](#配置可能遇到的问题)
  - [vscode Github推拉流](#vscode-github推拉流)
  - [Git学习](#git学习)
    - [基本查看指令](#基本查看指令)
    - [remote 远程仓处理](#remote-远程仓处理)
    - [branch 分支处理](#branch-分支处理)
----------------------------
# 笔记目录
- [C++](./C++/)
- [深入理解计算机系统（原书第三版）](./深入理解计算机系统/)
  - 1.操作系统-有符号数到无符号数隐式转化引出的错误
- [C++STL及泛型编程-侯捷著](./C++STL及泛型编程-侯捷著/)
  - 1.C++STL体系结构基础介绍

# Vscode Git
## vscode git配置
### ssh配置
>首先进行 git 用户设置。
>```
>git config  --global user.name ColderWANG
>git config  --global user.email 371774232@qq.com
>```
>SSH 协议是 HTTPS 以外，访问 GitHub 的另一协议。SSH 协议使用公钥、私钥认证，而不是使用密码认证。也就是说，使用 SSH 协议可以省去每次输密码的过程。
可以分为两步：
>1. 本地生成密钥对。
>2. 设置 github 的公钥。

>输入 `ssh-keygen` 生成密钥对，过程回车默认即可。生成的位置在 `~/.ssh` ，公钥为 `id_rsa.pub` ,私钥为 `id_rsa`。     
>接下来就是将公钥存到 GitHub：
>1. 登陆你的 github 帐户。然后 `Account Settings` -> 左栏点击 `SSH Keys` -> 点击 `Add SSH key`。
>2. 然后你复制上面的公钥内容，粘贴进“Key”文本域内。 title 域随意。点击 `Add key`。
>3. 使用 `ssh -T git@github.com` 测试一下连接

### vscode 源代码管理配置
>1. 点击 vscode 中的源代码管理，在本地指定文件夹下初始化本地仓库，在指定文件夹下面会得到 .git 文件夹
>2. 添加远程存储库,在弹出的命令行中依次输入 Github 中项目的 ssh 连接网址和名称 （origin）。![avatar](./picture/add_remote.png)
>3. 通过 git config 确认配置情况。![avatar](./picture/git_config.png)

### 配置可能遇到的问题
>1. ssh 超时解决方案：在.ssh文件夹下新建config文件。输入    
>```Host github.com  
>User 371774232@qq.com  
>Hostname ssh.github.com  
>PreferredAuthentications publickey  
>IdentityFile ~/.ssh/id_rsa  
>Port 443
>```

## vscode Github推拉流
>* 拉流：在源代码管理处选取拉去自，在如下弹出的命令行中可以选择 `origin` 及分支。![avatar](./picture/git_pull.png)
>* 推流：更改文件后，在源代码管理中可以看到更改，先点击提交，并写入提交信息，再选取推送至。

## Git学习

### 基本查看指令
1. 查看配置
   ```
   查看 git
   git config

   查看 remote
   git remote -v

   列出 branch
   git branch
   ```


### remote 远程仓处理
1. 连接远程仓
   ```
   git remote add <name> <url> //name 为默认origin
   ```
2. 删除远程仓
   ```
   git remote remove <name> 
   ```

### branch 分支处理
1. 删除分支
   ```
   删除本地分支
   git branch -D branchname
   
   删除远程分支
   git push origin --delete branchname
   ```

2. 新建分支
  ```
  git branch branchname
  ```
3. 切换分支
  ```
  git checkout branchname
  ```