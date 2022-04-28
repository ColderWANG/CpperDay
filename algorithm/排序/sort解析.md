## sort自定义比较函数
bool cmp(const Type &a, const Type &b);    
如果是想升序，那么就定义当a<b的时候返回true。   
如果是想降序，那么就定义当a>b的时候返回true。    

通常可以用lambda表达式定义比较函数。