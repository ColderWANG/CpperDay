# 5种IO模型
1. 阻塞IO
2. 非阻塞IO
3. IO多路复用
4. 信号驱动IO
5. 异步IO

# IO多路复用

## select

```cpp
int select(
    int nfds.    //监视的fd_set 的最大 fd + 1
    fd_set *readfds,
    fd_set *writeset,
    fd_set *exceptfds,
    struct timeval *timeout //null 阻塞， 0 非阻塞， 大于0 是固定等待时间
)
```

select 存在的问题： 
1. 每次执行 select，需要将整个fd_set 从用户空间拷贝到内核空间，select 结束要再次拷贝到用户空间
2. select 只知道有多少事件发生以及哪个集合是否有就绪事件，不知道哪个具体 fd 就绪，需要遍历 fd_set
3. fd_set 监听的数量不能超过1024

## poll
```cpp
struct pollfd{
    int fd;             //要监听的fd
    short int events;   //要监听的事件类型：读、写、异常
    short int revents;  //实际发生的事件类型
}
int poll(
    struct poffd *fds, //pollfd 数组
    nfds_t nfds,       //数组元素个数
    int timeout        //超时时间
)

```
区别：
poll 突破了 select 监听数量限制，但是监听的数量越多，性能越差，其他问题并没有解决。

## epoll
```cpp
struct eventpoll{
    //...
    struct rb_root rbt; //一颗红黑树，记录要监听的fd
    struct list_head rdlist;  //一个链表，记录就绪的fd
    //...
}
//创建 eventpoll 结构体，返回句柄 epfd
int epoll_create(int size);
int epoll_ctl(
    int epfd, // epoll 实例的句柄
    int op,   // 操作 ,ADD、MOD、DEL
    int fd,   //要处理的 fd
    struct epoll_event *event   //要监听的读写异常事件
)
int epoll_wait(
    int epfd,
    struct epoll_event *events,   //空 event  数组，用于接受就绪的 fd
    int maxevents,                //events 数组最大长度
    int timeout                   
)
```
优点：
1. 只拷贝一次所有的事件 fd 到内核空间，从内核空间拷贝回用户空间的只有就绪事件的 fd，大大减少了拷贝次数和拷贝数量
2. epoll 监听的 fd 过多不会影响性能
3. 直接得到就绪事件的 fd 

## 事件通知机制 ET 和 LT
LT有惊群现象，假设有n个不同进程检测 epoll ，没处理完会放回链表继续触发，可能唤醒了许多进程同时处理，如果有两个进程就可以结束事件，就没必要唤醒其他进程，造成性能浪费。

# 信号驱动IO
信号驱动IO 是与内核建立 SIGIO 的信号关联并设置回调，当内核有 FD 就绪时，会发出 SIGIO 信号通知用户，期间用户应用可以执行其他业务，无需阻塞等待。返回的是就绪事件，还需要用户去内核空间读取或写入数据。
缺点：
当有大量IO操作时，信号较多，SIGIO处理函数不能及时处理可能会导致信号队列溢出，而且内核空间与用户空间的频繁信号交互性能也较低

# 异步IO
整个过程是非阻塞的，用户调用 aio_read，返回的是**完成事件**，并通知用户进程，用户直接通过信号处理函数处理数据，缺点是高并发情况下内核任务太重，得由用户编码实现任务数量控制。
