## KMP
主串与模式串匹配的算法
i,j初始化为0
1. 如果A[i+1] == B[j+1],i++,j++继续匹配
2. A[i+1] != B[j+1],回溯 j 到next[j]，直到A[i+1] == B[j+1]
   如果j移到0还没有成功匹配，则忽略j，增加i，直到A[i+1]==B[j+1]
3. 当j == m时，输出位置，继续匹配

## next数组构建
对于i属于[2,m]
求出B[1]~B[i]的最长公共前后缀的长度


## 代码模板
```cpp
//KMP 实现字符串匹配
//getnext遍历一次计算 next数组
//j 表示 最长公共前后缀的位置，j == -1 说明没有公共前后缀，j != -1也就是 j >= 0时，
void getNext(int* next, const string& s){
    int j = -1;
    next[0] = j;
    for(int i = 1; i < s.size(); ++i){
        while(j >= 0 && s[i] != s[j+1])j = next[j];
        if(s[i] == s[j+1])j++;     //这里之前 j指向要和i匹配的
        next[i] = j;              
    }
}
int strStr(string haystack, string needle){
    if(needle.size() == 0)return 0;
    int next[needle.size()];
    getNext(next,needle);
    int j = -1;           //因为 next 数组里记录的起始位置为 -1
    for(int i = 0; i < haystack.size(); ++i){
        while(j >= 0 && haystack[i] != needle[j+1])j = next[j];//当前字符不匹配就回溯j
        if(haystack[i] == needle[j+1])j++;
        if(j == (needle.size()-1))return i+1-needle.size();   //主串与模式串匹配成功
    }
    return -1;
}

```