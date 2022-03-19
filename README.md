- [笔记目录](#笔记目录)
- [Vscode](#vscode)
  - [推荐插件](#推荐插件)
- [Vscode Git](#vscode-git)
  - [vscode git配置](#vscode-git配置)
    - [ssh配置](#ssh配置)
    - [vscode 源代码管理配置](#vscode-源代码管理配置)
    - [配置可能遇到的问题](#配置可能遇到的问题)
  - [vscode Github推拉流](#vscode-github推拉流)
  - [Git学习](#git学习)
    - [git linux下遇到的一些问题](#git-linux下遇到的一些问题)
    - [基本查看指令](#基本查看指令)
    - [remote 远程仓处理](#remote-远程仓处理)
    - [branch 分支处理](#branch-分支处理)
    - [git 推流流程](#git-推流流程)
    - [git 跟踪与取消跟踪](#git-跟踪与取消跟踪)
  - [Git CLI学习](#git-cli学习)
    - [安装与登录](#安装与登录)
----------------------------
# 笔记目录
- [C++](./C++/)
- [深入理解计算机系统（原书第三版）](./深入理解计算机系统/)
  - 1.操作系统-有符号数到无符号数隐式转化引出的错误
- [C++STL及泛型编程-侯捷著](./C++STL及泛型编程-侯捷著/)
  - 1.C++STL体系结构基础介绍
# Vscode
## 推荐插件

1. Code Runner
2. filesize
3. MarkDown All in one
4. Path Intellisense
5. Bracket Pair Colorizer
6. Project Manager
7. vscode-mindmap
8. draw.io

# Vscode Git
## vscode git配置
### ssh配置
首先进行 git 用户设置。
```
git config  --global user.name ColderWANG
git config  --global user.email 371774232@qq.com
```
SSH 协议是 HTTPS 以外，访问 GitHub 的另一协议。SSH 协议使用公钥、私钥认证，而不是使用密码认证。也就是说，使用 SSH 协议可以省去每次输密码的过程。
可以分为两步：
1. 本地生成密钥对。
2. 设置 github 的公钥。

输入 `ssh-keygen` 生成密钥对，过程回车默认即可。生成的位置在 `~/.ssh` ，公钥为 `id_rsa.pub` ,私钥为 `id_rsa`。     
接下来就是将公钥存到 GitHub：
1. 登陆你的 github 帐户。然后 `Account Settings` -> 左栏点击 `SSH Keys` -> 点击 `Add SSH key`。
2. 然后你复制上面的公钥内容，粘贴进“Key”文本域内。 title 域随意。点击 `Add key`。
3. 使用 `ssh -T git@github.com` 测试一下连接

### vscode 源代码管理配置
1. 点击 vscode 中的源代码管理，在本地指定文件夹下初始化本地仓库，在指定文件夹下面会得到 .git 文件夹
2. 添加远程存储库,在弹出的命令行中依次输入 Github 中项目的 ssh 连接网址和名称 （origin）。![avatar](./picture/add_remote.png)
3. 通过 git config 确认配置情况。![avatar](./picture/git_config.png)

### 配置可能遇到的问题
1. ssh 超时解决方案：在.ssh文件夹下新建config文件。输入    
```Host github.com  
User 371774232@qq.com  
Hostname ssh.github.com  
PreferredAuthentications publickey  
IdentityFile ~/.ssh/id_rsa  
Port 443
```

2. 找不到 github 的host。通过 https://www.ipaddress.com/ 上查询github.com和github.global.ssl.fastly.net最快的ip
```
sudo vim /etc/hosts
末尾输入
140.82.112.4 github.com
```

## vscode Github推拉流
* 拉流：在源代码管理处选取拉去自，在如下弹出的命令行中可以选择 `origin` 及分支。![avatar](./picture/git_pull.png)
* 推流：更改文件后，在源代码管理中可以看到更改，先点击提交，并写入提交信息，再选取推送至。

## Git学习
### git linux下遇到的一些问题
1. 下载或推送慢，需要修改hosts，去 https://www.ipaddress.com/ 上查询github.com和github.global.ssl.fastly.net最快的ip
```
sudo vim /etc/hosts
末尾输入 (2022.3.16有效)
140.82.112.4    github.com
199.232.69.194  github.global.ssl.fastly.net
185.199.108.153 githubstatus.com
140.82.112.5    api.github.com
```
2. git push 卡在 writing project 这，速度很慢，因为http.postBuffer默认上限为1M,上面的命令是把git的配置里http.postBuffer的变量改大为500M
```
git config --global http.postBuffer 524288000
```
3. 文件大,上传慢,把远程仓库的上传由原来的HTTPS改为SSH上传 (似乎并没有好转,并没有http快)
```
git remote set-url origin [你的ssh地址]

vim /etc/ssh/ssh_config
搜索 GSSAPIAuthentication 找到该配置项
配置禁用 GSSAPI 校验：默认使用 # 号注释掉了
保存退出
```
   


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

### git 推流流程
1. 查看文件更改
  ```
  git status -s   -s是简短输出
  ```
2. 针对更改添加到暂存库
  ```
  git add [file1] [file2]   添加指定文件
  git add [dir]             添加指定目录下更改文件
  git .                     添加当前目录下所有更改文件
  ```
3. 提交暂存库到本地仓库 
  ```
  git commit -m [message] 
  git commit [file1] [file2] -m [message]  提交指定文件
  git commit -am [message]                 添加提交一键操作
  ```          
4. 推流
  ```
  git push [远程主机名] [本地分支名]:[远程分支名]   
  git push [远程主机名] [本地分支名]                若远程分支和本地分支名相同则可以这样
  git push -u [远程主机名] [本地分支名]:[远程分支名]   -u 参数是指定之后 push 的默认设置，即之后采用 git push 即可
  ```

### git 跟踪与取消跟踪
1. 如果已经 push 过一次，即在版本库中存在此文件，需要删除
  ```
  git rm --cached file
  git rm --cached -r folder
  ```
2. 创建 .gitignore 文件，修改
  ```
  过滤操作（取消追踪）
  /mtk/ 过滤整个文件夹
  *.zip 过滤所有.zip文件
  /mtk/do.c 过滤某个具体文件

  添加操作（追踪）区别就是多个感叹号
  !*.zip    
  !/mtk/one.txt
  ```
3. 提交并推送


## Git CLI学习
### 安装与登录
安装gh
输入：
```
gh auth login
```