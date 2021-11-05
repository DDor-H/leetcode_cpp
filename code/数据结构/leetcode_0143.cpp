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

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        ListNode* mid = findMiddle(head);
        ListNode* l1 = head;
        ListNode* l2 = mid->next;
        mid->next = nullptr;
        l2 = reverseList(l2);
        mergeList(l1, l2);
    }

    ListNode* findMiddle(ListNode* node)
    {
        ListNode* slow = node;
        ListNode* fast = node;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode* reverseList(ListNode* node)
    {
        ListNode* prev = nullptr;
        ListNode* p = node;
        while (p != nullptr)
        {
            ListNode* tmp = p->next;
            p->next = prev;
            prev = p;
            p = tmp;
        }
        return prev;
    }
    void mergeList(ListNode* p1, ListNode* p2)
    {
        ListNode* l1;
        ListNode* l2;
        while (p1 != nullptr && p2 != nullptr)
        {
            l1 = p1->next;
            l2 = p2->next;

            p1->next = p2;
            p2->next = l1;

            p1 = l1;
            p2 = l2;
        }
    }
};

    


 /*
 // 使用数组辅助
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;
        vector<ListNode*> v;
        ListNode* node = head;
        while (node != nullptr)
        {
            v.push_back(node);
            node = node->next;
        }
        ListNode* dummy = new ListNode(0);
        ListNode* tmp = dummy;
        for (int i = 0; i < (v.size() + 1) / 2; ++i)
        {
            tmp->next = v[i];
            tmp = tmp->next;
            if (i == v.size() - i - 1)
                continue;
            tmp->next = v[v.size() - i - 1];
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        head = dummy->next;
    }
};
*/