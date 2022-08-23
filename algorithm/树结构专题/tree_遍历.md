### 二叉树

```cpp
struct TreeNode {
     int val; 
     TreeNode *left; TreeNode *right; 
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};
```
#### 二叉树的一些性质
二叉树的节点 n 和其深度 d 的计算公式是：
$$ n = 2^d-1 $$
所以求根到叶子结点的路径的空间复杂度最差为O(d) = O(logn)
二叉树的数组形式，索引为 i 的左子节点是 i*2 + 1，索引为 i 的父节点是 (i-1)/2 ;

### 二叉数先序遍历
搜索次序为父左右
#### 方法一：堆实现
> 时间复杂度O(n),空间复杂度O(n)

由于堆 stack 的先入后出特性，可以把父节点压入堆中，通过循环取出一个节点然后压入这个节点的左右子节点，**先压右节点**，再**压左节点**。

#### 方法二：Morris 先序遍历 ✨
> 时间复杂度O(n),空间复杂度O(1)

是基于双指针的实现，一个指针指向当前，另一个指向上一个指针。特性是有左子树的节点只到达 1 次，流程是
1. 如果 Cur 没有左孩子，Cur 向右移动。
2. 如果 Cur 有左孩子，找到 Cur 左子树最右的节点，记作mostright。
   >2.1 如果 mostright 的 right 指向空，让其指向 Cur，Cur向左移动。
   >2.2 如果 mostright 的 right 指向 Cur，让其指向空，Cur向右移动。
