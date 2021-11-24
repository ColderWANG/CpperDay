在连续数组 vector 或者字符 string 中插入或删除某个数据时，需要更新迭代器。
### 剑指offer.05 替换空格
```cpp
输入：s = "We are happy."
输出："We%20are%20happy."

class Solution {
public:
    string replaceSpace(string s) {
        string ss = "20";
        auto i = s.begin();
        while(i!= s.end()){
            if(*i == ' '){
                *i = '%';
                i = s.insert(++i,ss.begin(),ss.end());     //经过插入步骤后若使用原来的i则会出现错误,更新则不会
            }
            else i++;
        }
        return s;
    }
};
假设字符串后面有足够的内存 
```

