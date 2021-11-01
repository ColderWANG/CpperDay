- [互斥量](#互斥量)
  - [std::mutex 类](#stdmutex-类)
  - [std::lock_guard 类模板](#stdlock_guard-类模板)
- [死锁](#死锁)
  - [std::lock 函数模板](#stdlock-函数模板)
  - [std::lock_guard 的 std::adopt_lock 参数](#stdlock_guard-的-stdadopt_lock-参数)


### 互斥量
#### std::mutex 类
是一个类对象，理解成一把锁，通过 lock() 成员函数锁定，多个线程同时用时只有一个能成功返回，其他线程会卡在 lock() 内部不断尝试。**步骤**：先用 lock() 锁住数据，操作数据，再用 unlock() 解锁数据。

#### std::lock_guard 类模板
一个 lock 必须对应一个 unlock ，而 lock_guard 可以防止这种情况，同时取代 lock() 和 unlock() ，不能**和其同时出现**。在 lock_guard 构造函数里执行了 lock ，在析构函数里执行 unlock，所以应在需要被保护的函数里创建对象。**巧用局部变量的生命周期**      
```cpp
//调用展示
std::mutex my_mutex
std::lock_guard<std::mutex> stguard(my_mutex);  //以下两行不能出现
//my_mutex.lock()
//my_mutex.unlock()
```    
如果线程共享数据在一个大函数内，可以通过{}来**隔离作用域**。


### 死锁
死锁问题由两个互斥量才能产生。   
假如有两个锁，金锁和银锁   
线程1：先锁金锁，再去锁银锁。  
线程2：先锁银锁，再去锁金锁。  
两个线程经过第一步的时候没问题，在第二步的时候就僵持住了，后面程序无法进行。
> 解决方案：只要互斥量上锁顺序一致，就不会产生死锁

#### std::lock 函数模板
一次锁住两个或两个以上的互斥量（至少两个，多了不限，少了不行），直接解决了因为 lock 顺序导致的死锁问题。    
**特点**会同时锁住两个互斥量，如果只锁一个另一个没锁成功，则会立即释放第一个锁。    
**但是**还会有一个不方便的地方，用这个函数还需要**手动 unlock**。

#### std::lock_guard 的 std::adopt_lock 参数
为了解决上述问题，可以搭配 std::lock 函数和 std::lock_guard 类模板
```cpp 
std::mutex my_mutex1,my_mutex2;   //创建互斥量
std::lock(my_mutex1,my_mutex2);   //用 lock 函数同时锁住两个互斥量
std::lock_guard<std::mutex> sbguard1(my_mutex1,std::adopt_lock);
std::lock_guard<std::mutex> sbguard2(my_mutex2,std::adopt_lock);
//std::adopt_lock 参数避免了用了 lock 后对互斥量再锁定。
```