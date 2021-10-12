/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 方法二：递归
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return head;
        
        head->next = removeElements(head->next, val);
        return head->val == val ? head->next : head;
    }
};

 /*
 // 方法一：
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return head;
        
        ListNode* dynHead = new ListNode(-1);
        dynHead->next = head;
        ListNode* p = head;
        ListNode* prev = dynHead;
        while (p != nullptr)
        {
            if (p->val == val)
            {
                prev->next = p->next;
                //free(p);
                p = prev->next;
            }
            else
            {
                prev = p;
                p = p->next;
            }
        }

        return dynHead->next;
    }
};
*/