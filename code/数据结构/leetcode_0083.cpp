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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        ListNode* newHead = deleteDuplicates(head->next);
        if (head->val == head->next->val)
        {
            ListNode* del = head->next;
            head->next = head->next->next;
            delete del;
        }
        return head;
    }
};

/*
 // 方法一：迭代
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        ListNode* prev = head;
        ListNode* cur = head->next;
        while (cur != nullptr)
        {
            if (prev->val == cur->val)
            {
                ListNode* tmp = cur;
                prev->next = cur->next;
                delete tmp;  // 这里不能用free
                cur = prev->next;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
        return head;
    }
};
*/