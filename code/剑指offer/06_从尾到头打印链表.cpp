/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


 // 递归
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        if (head == NULL)
            return res;
        
        _reversePrint(head, res);
        return res;
    }

    void _reversePrint(ListNode* head, vector<int>& res)
    {
        if (head == NULL)
            return;
        _reversePrint(head->next, res);
        res.push_back(head->val);
    }
};


/*
 // 使用栈
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        if (head == NULL)
            return res;
        stack<int> stk;
        while (head != NULL)
        {
            stk.push(head->val);
            head = head->next;
        }
        while(!stk.empty())
        {
            res.push_back(stk.top());
            stk.pop();
        }
        return res;
    }
};


/*
 // 交换数组
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        if (head == NULL)
            return res;
        while (head != NULL)
        {
            res.push_back(head->val);
            head = head->next;
        }
        int i = 0, j = res.size() - 1;
        while(i < j)
        {
            int tmp = res[i];
            res[i] = res[j];
            res[j] = tmp;
            ++i;
            --j;
        }
        return res;
    }
};
*/