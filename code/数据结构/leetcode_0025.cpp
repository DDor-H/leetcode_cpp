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
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail)
    {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail)
        {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }


    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 1)
            return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* p = dummy;
        while (p->next != nullptr)
        {
            ListNode* start = p->next;
            ListNode* end = start;
            for (int i = 0; i < k - 1; ++i)
            {
                end = end->next;
                if (!end)
                    return dummy->next;
            }

            ListNode* nex = end->next;
            tie(start, end) = myReverse(start, end);
            p->next = start;
            end->next = nex;
            p = end;
        }
        return dummy->next;
    }
};