#include <iostream>
#include <vector>
#include <algorithm>
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
int main(){
    string a = "leetcode";
    char ans = firstUniqChar(a);
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