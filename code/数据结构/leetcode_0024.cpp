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

// 迭代
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* res = new ListNode(0, head);
        ListNode* temp = res;
        while (temp->next != nullptr && temp->next->next != nullptr)
        {
            ListNode* p = temp->next;
            ListNode* q = temp->next->next;
            temp->next = q;
            p->next = q->next;
            q->next = p;
            temp = temp->next->next;
        }

        return res->next;
    }
};

/*
 // 递归
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* back = swapPairs(head->next->next);
        ListNode* tmp = head->next;
        tmp->next = head;
        head->next = back;
        return tmp;
    }
};
*/