/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

/*
// 方法一：回溯+map
class Solution {
private:
    unordered_map<Node*, Node*> catchMap;
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL)
            return NULL;
        if (!catchMap.count(head))
        {
            Node* headNew = new Node(head->val);
            catchMap[head] = headNew;

            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        return catchMap[head];
    }
};
*/

// 方法儿：三次循环，迭代方式
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL)
            return NULL;
        
        for (Node* node = head; node != NULL; node = node->next->next)
        {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }
        for (Node* node = head; node != NULL; node = node->next->next)
        {
            Node* nodeNew = node->next;
            // 注意这块的node->random->next，需要找到新链表的新节点
            nodeNew->random = (node->random != NULL) ? node->random->next : NULL; 
        }
        Node* headNew = head->next;
        for (Node* node = head; node != NULL; node = node->next)
        {
            Node* nodeNew = node->next;
            node->next = nodeNew->next;
            nodeNew->next = (nodeNew->next != NULL) ? nodeNew->next->next : NULL;
        }

        return headNew;
    }
};