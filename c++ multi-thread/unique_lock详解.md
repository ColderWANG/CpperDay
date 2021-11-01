
### unique_lock
#### unique_lock 取代 lock_guard
1. unique_lock 是一个类模板，工作中一般用 lock_guard(推荐使用)，取代了 mutex 的 lock 和 unlock。
2. unique_lock 比 lock_guard 灵活很多，但是效率上差一点，内存多一点。
#### unique_lock 成员函数
1. lock() 函数， 和 mutex 的不一样，无需自己 unlock
2. unlock() 函数
3. try_lock() 函数, 尝试给互斥量加速哦，如果拿不到锁，则返回 false，拿到返回 true，这个函数不会阻塞。
4. release() 函数，返回管理的 mutex 对象指针，并释放所有权。

### unique_lock 的第二个参数
#### std::adopt_lock
表示这个互斥量已经被 lock 了，不需要进行 lock ，只需要保证 unlock。（必须要把互斥量提前 lock 否则会报异常）
#### std::try_to_lock
尝试用 mutex 的 lock() 去锁定这个互斥量，但是如果没锁定成功，也会立即返回，并不会阻塞。**注意**用这个参数前提是此线程之前并未对这个互斥量进行 lock，否则会 lock 两次，报错。  
用这个参数好处是另外一个线程再延时的时候，此线程无需进行等待。
```cpp
std::unique_lock<std::mutex> sbguard1(my_mutex1, std::try_to_lock);
if(sbguard1.owns_lock())
{
    //拿到了锁
}
else
{
    //没拿到锁
}
```

#### std::defer_lock
 前提时此线程不能自己先 lock。  
 初始化了一个没有对 mutex 加锁的对象 ，以便调用 unique_lock 的成员函数。
 ```cpp
std::unique_lock<std::mutex> sbguard1(my_mutex1, std::defer_lock); //没有加锁的 my_mutex1
sbguard1.lock(); //不用自己 unlock 
//处理共享数据

sbguard1.unlock();
//处理非共享数据

sbguard1.lock();
//处理共享数据

 ```

 ### unique_lock 所有者的传递
 unique_lock 管理一个 mutex 的指针，