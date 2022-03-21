#include <iostream>
#include <vector>
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


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
//输入当前对应的两个节点，得到当前n的 random 索引
void random_get(Node* n,Node* dupn, vector<int> &vec){
    Node* tempn = n->random;
    int index = 0;
    if(tempn == nullptr)vec.push_back(-1);
    else{
        while(tempn != n && tempn != nullptr){
            index++;
            tempn = tempn->next;
        }
        if(tempn == n)
            vec.push_back(vec.size() - index); 
        else 
            vec.push_back(-index - 1);   //randon在节点后方，存入距离null距离 - 1；
    }
}
Node* copyRandomList(Node* head) {
    if(head == nullptr)return nullptr;
    //建立一个数组存储 random 的地址
    vector<int> random_vec;
    Node *duphead = new Node(head->val);
    random_get(head,duphead,random_vec);
    Node *n = head->next, *dupn = duphead;
    while(n != nullptr){
        Node *t = new Node(n->val);
        dupn->next = t;
        random_get(n,dupn->next,random_vec);
        n = n->next;
        dupn = dupn->next;
    }
    //再来一遍循环连接 random 链表
    dupn = duphead;
    for(int i = 0; i < random_vec.size(); i++){
        Node* p = duphead;
        int count = 0, index = random_vec[i];
        if(index < 0){
            if(index == -1){
                dupn = dupn->next;
                continue;
            }
            else index = random_vec.size() + index + 1;
        }
        while(count != index){
            p = p->next;
            count++;
        }
        dupn->random = p;
        dupn = dupn->next;
    }
    return duphead;
}


int main(){

    Node * head = new Node(7);
    Node * n2 = new Node(13);
    Node * n3 = new Node(11);
    Node * n4 = new Node(10);
    Node * n5 = new Node(1);
    head ->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    head->random = nullptr;
    n2->random = head;
    n3->random = n5;
    n4->random = n3;
    n5->random = head;

    Node *copyhead = copyRandomList(head);

}
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */