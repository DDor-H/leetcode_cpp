/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 双指针2
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        
        ListNode* pA = headA;
        ListNode* pB = headB;
        while (pA != pB)
        {
            pA = pA == NULL ? headB : pA->next;
            pB = pB == NULL ? headA : pB->next;
        }
        return pA;
    }
};

/*
// 双指针
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        
        ListNode* pA = headA;
        ListNode* pB = headB;
        int lenA = 0;
        int lenB = 0;
        while (pA != NULL)
        {
            ++lenA;
            pA = pA->next;
        }
        while (pB != NULL)
        {
            ++lenB;
            pB = pB->next;
        }
        if (lenA < lenB)
        {
            pA = headB;
            pB = headA;
        }

        for (int i = 0; i < abs(lenA - lenB); ++i)
            pA = pA->next;

        while (pA != NULL && pB != NULL)
        {
            if (pA == pB)
                return pA;
            pA = pA->next;
            pB = pB->next;
        }
        return NULL;
    }
};


 /*
 // hash表
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == NULL || headB == NULL)
            return NULL;
        unordered_set<ListNode*> set;
        ListNode* pA = headA;
        ListNode* pB = headB;
        while (pA != NULL || pB != NULL)
        {
            if (pA != NULL)
            {
                if (set.count(pA) == 0)
                {
                    set.insert(pA);
                    pA = pA->next;
                }
                else
                    return pA;
            }
            if (pB != NULL)
            {
                if (set.count(pB) == 0)
                {
                    set.insert(pB);
                    pB = pB->next;
                }
                else
                    return pB;
            }
        }
        return NULL;
    }
};
*/