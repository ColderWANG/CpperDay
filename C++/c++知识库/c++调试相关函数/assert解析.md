```cpp
#include <assert.h> //c++中可以不用手动包含此头文件
void assert(int expression);
```

assert 的作用是计算表达式，如果值为 false，会向 stderr 打印一条出错信息，然后通过调用 abort 来终止程序运行。
缺点：频繁调用会影响程序性能，所以少用，assert 是用来避免显而易见的错误的，而不是处理异常（读取图像后可用）。