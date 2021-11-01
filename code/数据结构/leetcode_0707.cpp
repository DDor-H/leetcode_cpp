
// 单链表
class ListNode1 {
public:
    int val = 0;
    ListNode1* next;
    ListNode1(int v, ListNode1* n = nullptr) : val(v), next(n)
    {}
};


class MyLinkedList {
public:
    ListNode1* root;
    int size;
public:
    MyLinkedList() {
        root = nullptr;
        size = 0;
    }
    
    int get(int index) {
        int i = 0;
        ListNode1* p = root;
        while (p != nullptr)
        {
            if (i++ == index)
                return p->val;
            p = p->next;
        }
        return -1;
    }
    
    void addAtHead(int val) {
        ListNode1* head = new ListNode1(val);
        if (root == nullptr)
            root  = head;
        else
        {
            head->next = root;
            root = head;
        }
        ++size;
    }
    
    void addAtTail(int val) {
        ListNode1* tail = new ListNode1(val);
        if (root == nullptr)
            root  = tail;
        else
        {
            ListNode1* p = root;
            while (p->next != nullptr)
                p = p->next;
            p->next = tail;
        }
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size)
            return;
        if (index <= 0)
        {
            addAtHead(val);
            return;
        }
        if (index == size)
        {
            addAtTail(val);
            return;
        }

        ListNode1* p = root;
        while (index-- > 1)
            p = p->next;
        ListNode1* q = new ListNode1(val);
        q->next = p->next;
        p->next = q;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        if (index >= size || index < 0)
            return;
        if (size == 1)
        {
            delete root;
            root = nullptr;
            --size;
            return;
        }
        if (index == 0)
        {
            ListNode1* p = root;
            root = p->next;
            delete p;
            --size;
            return;
        }
        ListNode1* p = root;
        ListNode1* prev = nullptr;
        while (p != nullptr && index-- > 0)
        {
            prev = p;
            p = p->next;
        }
        if (p != nullptr)
        {
            prev->next = p->next;
            delete p;
            --size;
        }
    }
};

/*
// 双链表
class ListNode1 {
public:
    int val = 0;
    ListNode1* next;
    ListNode1* prev;
    ListNode1(int v, ListNode1* n = nullptr, ListNode1* p = nullptr) : val(v), next(n), prev(p)
    {}
};


class MyLinkedList {
public:
    ListNode1* root;
    ListNode1* tail;
    int size;
public:
    MyLinkedList() {
        root = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    int get(int index) {
        int i = 0;
        ListNode1* p = root;
        while (p != nullptr)
        {
            if (i++ == index)
                return p->val;
            p = p->next;
        }
        return -1;
    }
    
    void addAtHead(int val) {
        ListNode1* head = new ListNode1(val);
        if (root == nullptr)
            root = tail = head;
        else
        {
            head->next = root;
            root->prev = head;
            root = head;
        }
        ++size;
    }
    
    void addAtTail(int val) {
        ListNode1* rhead = new ListNode1(val);
        if (tail == nullptr)
            root = tail = rhead;
        else
        {
            tail->next = rhead;
            rhead->prev = tail;
            tail = rhead;
        }
        ++size;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size)
            return;
        if (index <= 0)
        {
            addAtHead(val);
            return;
        }
        if (index == size)
        {
            addAtTail(val);
            return;
        }

        ListNode1* p = root;
        while (index-- > 0)
            p = p->next;
        ListNode1* q = new ListNode1(val);
        q->next = p;
        q->prev = p->prev;
        q->next->prev = q;
        q->prev->next = q;
        ++size;
    }
    
    void deleteAtIndex(int index) {
        if (index >= size || index < 0)
            return;
        if (size == 1)
        {
            delete root;
            root = tail = nullptr;
            --size;
            return;
        }
        if (index == 0)
        {
            ListNode1* p = root;
            root = p->next;
            root->prev = nullptr;
            delete p;
            --size;
            return;
        }
        if (index == size - 1)
        {
            ListNode1* p = tail;
            tail = p->prev;
            tail->next = nullptr;
            delete p;
            --size;
            return;
        }
        ListNode1* p = root;
        while (index-- > 0)
            p = p->next;
        p->next->prev = p->prev;
        p->prev->next = p->next;
        delete p;
        --size;
    }
};
*/

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */