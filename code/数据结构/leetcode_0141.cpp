/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


 // 方法二：hash表法
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return false;
        unordered_map<ListNode*, int> um;
        while (head != NULL)
        {
            if (um.count(head) > 0)
                return true;
            um.insert(make_pair(head, 1));
            head = head->next;
        }
        return false;
    }
};


 /*
 // 方法一：前后指针法
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return false;
        ListNode *slow = head;
        ListNode *fast = head->next;

        while (slow != fast)
        {
            if (fast == NULL || fast->next == NULL)
                return false;
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
*/