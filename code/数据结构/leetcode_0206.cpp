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


 // 递归：
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
            
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};

/*
 // 迭代二：
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
            
        ListNode* prev = nullptr;
        ListNode* cur = head;

        while (cur != nullptr)
        {
            ListNode* curNext = cur->next;
            cur->next = prev;
            prev = cur;
            cur = curNext;
        }
        return prev;
    }
};

 /*
 // 迭代一：
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* res = new ListNode(-1);
        ListNode* p = head;
        ListNode* q = head->next;

        while (q != nullptr)
        {
            p->next = res->next;
            res->next = p;
            p = q;
            q = q->next;
        }
        p->next = res->next;
        res->next = p;

        return res->next;
    }
};
*/