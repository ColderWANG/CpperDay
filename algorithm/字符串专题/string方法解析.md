# hot.3
## 滑动窗口法
滑动窗口可以看作是一个队列，要把队列的**左边的元素**移出就行了，直到满足题目要求！   
通过 unordered_set 来存放值  

```
模板
unordered_set<value> lookup;
int max;
int left;
for 字符串遍历
    while lookup.find(s[i]) != lookup.end()
        lookup.erase(s[left])          注意这里是删除左边的元素，即移除队首
        left++;
    maxstr = max(maxstr,i-left+1)
    在 set 中插入当前字符

```