#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
class MinStack {
public:
    /** initialize your data structure here. */
    int size = 0;
    typedef struct node{
        int val;
        node *p_nt = nullptr;
        node *p_fa = nullptr;
        node *p_lastsmall = nullptr;
    }*Node;
    Node head = nullptr;
    Node end = nullptr;
    Node minn = nullptr;
    MinStack() {    
        head = new node;
        end = head;
        minn = head;
    }
    void push(int x) {
        Node n = new node;
        n->val = x;
        n->p_fa = end;
        end->p_nt = n;
        if(!size)minn = n;
        else {
            //对第三条链表进行梳理
            if(x <= minn->val){
                n->p_lastsmall = minn;
                minn = n;
            }
        }
        end = n;
        size++;
    }
    
    void pop() {
        if(size){
            Node temp;
            temp = end;
            if(temp == minn){
                minn = temp->p_lastsmall;
            }
            end->p_fa->p_nt = nullptr;
            end = end->p_fa;
            delete temp;
            size--;
        }
    }
    
    int top() {
        return end->val;
    }
    
    int min() {
        return minn->val;
    }
};

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    if(pushed.empty() || popped.empty())return true;
    int push_ = 0, pop_ = 0, n;
    while(pop_ < popped.size()){
        n = popped[pop_];
        while(pushed[push_] != n){
            push_++;
            if(push_ >= pushed.size())return false;
        }
        if(push_ > 0){
            pushed.erase(pushed.begin() + push_);
            push_--;
        }
        pop_++;
    }
    if(push_ == 0)return true;
    else return false;
}
char firstUniqChar(string s) {
    if(s.empty())return ' ';
    string::iterator ans = s.begin();
    sort(s.begin(),s.end());
    for(; ans < s.end() - 1; ans++){
        if(*ans != *(ans + 1))break;
    }
    if(s.size() > 1 && *ans == *(ans - 1))return ' ';
    else return *ans;
}

int maxValue(vector<vector<int>>& grid) {
    if(grid.empty())return 0;
    int i = 0, j = 0;
    int maxv = grid[i][j];
    //循环，第一层循环把所有点通过最大值连接，建立哈希表，确定每个点的最大val
    unordered_map<int,int> m;
    for(i = 0; i < grid.size(); i++){
        for(j = 0; j < grid[0].size(); j++){
            if(i == 0 && j == 0)m[0] = maxv;
            else if(i == 0 && j != 0){
                maxv = grid[i][j] + m[j - 1];
                m[j] = maxv;
            }
            else if(j == 0 && i != 0){
                maxv = grid[i][j] + m[grid.size()*(i-1)];
                m[grid[0].size()*i] = maxv;
            }
            else {
                maxv = max(grid[i][j] + m[j+grid.size()*i - 1], grid[i][j] + m[j+grid.size()*(i-1)]);
                m[j+grid[0].size()*i] = maxv;
            }
        }
    }
    return m[grid[0].size()-1 + grid[0].size()*(grid.size()-1)];
}
int lengthOfLongestSubstring(string s) {
    string ss = "";
    int maxlen = 0;
    for(auto c : s){
        int index = ss.rfind(c);
        if(index == string::npos)ss.push_back(c);
        else {
            int l = ss.length();
            if(l > maxlen)maxlen = l;
            ss.erase(0,index + 1);
            ss.push_back(c);
        }
    }
    if(ss.length() > maxlen)maxlen = ss.length();
    return maxlen;
}
int main(){
    // vector<vector<int>> g;
    // vector<int> a = {1,2,5};
    // vector<int> b = {3,2,1};
    //vector<int> c = {4,2,1};
    // g.push_back(a);
    // g.push_back(b);
    //g.push_back(c);
    string s = "asdfasffgoiv";
    int ans;
    ans = lengthOfLongestSubstring(s);

    cout << ans << endl;
}
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */