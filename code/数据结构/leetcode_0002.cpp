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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ret;
        ListNode* l;
        ret = new ListNode(0);
        l = ret;
        int temp = 0;
        bool flag = false;
        while(l1 != nullptr && l2 != nullptr)
        {
            l->next = new ListNode(l1->val + l2->val);
            l = l->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        while(l1)
        {
            l->next = new ListNode(l1->val);
            l = l->next;
            l1 = l1->next;
        }

        while(l2)
        {
            l->next = new ListNode(l2->val);
            l = l->next;
            l2 = l2->next;
        }

        l = ret->next;

        while(l)
        {
            if (l->val > 9)
            {
                l->val -= 10;
                if(l->next == nullptr)
                {
                    l->next = new ListNode(0);
                }
                l->next->val += 1;
            }
            l = l->next;
        }

        return ret->next;
    }
};