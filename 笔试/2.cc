#include<bits/stdc++.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    void reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        while(head){
            ListNode* tmp = head->next;
            head->next = pre;
            pre = head;
            head = tmp;
        }
    }
    void reorderList(ListNode* head) {
        ListNode *fast = head, *low = head;
        while(fast->next && fast->next->next){
            low = low->next;
            fast = fast->next->next;
        }
        reverseList(low->next);
        //合并
        fast = low->next;
        low->next = nullptr;
        low = head;
        while(low && fast){
            ListNode *tmp1 = low->next, *tmp2 = fast->next;
            low->next = fast;
            fast->next = tmp1;
            low = tmp1;
            fast = tmp2;
        }
    }
};
int main(){
    ListNode* h = new ListNode(1);
    h->next = new ListNode(2);
    h->next->next = new ListNode(3);
    h->next->next->next = new ListNode(4);
    Solution s;
    s.reorderList(h);
    return 0;
}