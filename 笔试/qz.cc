#include <iostream>
#include <vector>

using namespace std;

//算法类，从小到大排序
class Solution{
public:
    /* 冒泡排序 时间复杂度O(n^2)*/
    void BubbleSort(vector<int> &nums) {
        int len = nums.size();
        /* 从后面开始遍历，k 表示内循环一次冒泡该放的位置 */
        for(int k = len - 1; k >= 0; k--) { 
            int i = 0, j = 0;
            /* 内循环，从前开始，把大的泡泡往后放 */
            while(j <= k) {
                if(nums[i] > nums[j])swapXOR(nums,i,j);
                i = j;
                ++j;
            }
        }
    }
    /* 快速排序 时间复杂度O(logn) */
    /* 在 nums[l,r]  范围进行排序*/
    void QuickSort(vector<int>& nums, int l, int r) {
        /* 子数组长度为 1 时终止递归 */
        if (l >= r) return;
        /* 哨兵划分操作（以 nums[l] 作为基准数）*/
        int i = l, j = r;                             //闭区间
        while (i < j) {
            while (i < j && nums[j] >= nums[l]) j--;  //右指针往左移，遇到比哨兵小的停止
            while (i < j && nums[i] <= nums[l]) i++;  //左指针往右移，遇到比哨兵大的停止
            swapXOR(nums,i,j);                        //这个时候 i 比 j 大 ，所以交换
        }
        swapXOR(nums,i,l);
        /* 递归左（右）子数组执行哨兵划分 */
        QuickSort(nums, l, i - 1);
        QuickSort(nums, i + 1, r);
    }
    /* 归并排序 时间复杂度O(logn) */
    /* 在 nums[l,r]  范围进行排序*/
    void MergeSort(int l, int r, vector<int>& nums, vector<int>& tmp) {
        /* 向下递归 */
        if(l >= r)return;
        int mid = l+(r-l)/2;
        MergeSort(l, mid,nums,tmp);
        MergeSort(mid+1,r,nums,tmp);
        /* 向上合并 */
        int i = l, j = mid + 1;
        for(int k = l; k <= r; ++k) {
            tmp[k] = nums[k];                       //复制原数组
        }
        for(int k = l; k <= r; k++) {
            if( i == mid+1)                         //左子数组已经合并完，添加右边数组
                nums[k] = tmp[j++];
            else if(j == r+1 || tmp[i] <= tmp[j])   //右子数组已经合并完或左小于右，添加左边数组
                nums[k] = tmp[i++];
            else
                nums[k] = tmp[j++];                 //这个情况是 tmp[i] > tmp[j]的情况
        }
    }
private:
    //异或实现快速交换
    void swapXOR(vector<int> &arr, int i, int j) {
    if(i == j) return; // 若无法保证swapXOR被调用时满足 i != j，则需有此句，否则i == j时此数将变为0
    arr[i] = arr[i] ^ arr[j]; // a = a ^ b，也可写成 arr[i] ^= arr[j];
    arr[j] = arr[i] ^ arr[j]; // b = (a ^ b) ^ b = a ^ (b ^ b) = a ^ 0 = a， 也可写成 arr[j] ^= arr[i];
    arr[i] = arr[i] ^ arr[j]; // a = (a ^ b) ^ a = (a ^ a) ^ b = 0 ^ b = b， 也可写成 arr[i] ^= arr[j];
    }
};

int main(){
    vector<int> nums = {1,0,1,4,8,4,6,2};
    Solution s;
    vector<int> t(nums.size());
    s.MergeSort(0,nums.size() - 1,nums,t);  //归并排序
    //s.QuickSort(nums,0,nums.size()-1);      //快速排序
    //s.BubbleSort(nums);                       //冒泡排序
    for(auto n : nums) {
        cout << n << ' ';
    }
    return 0;
}