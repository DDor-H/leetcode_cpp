class MyQueue {
private:
    stack<int> st1;
    stack<int> st2;
public:
    MyQueue() {
        st1 = stack<int>();
        st2 = stack<int>();
    }
    
    void push(int x) {
        st1.push(x);
    }
    
    int pop() {
        int tmp = -1;
        if (st2.empty())
        {
            while (!st1.empty())
            {
                tmp = st1.top();
                st1.pop();
                st2.push(tmp);
            }
        }

        tmp = st2.top();
        st2.pop();
        return tmp;
    }
    
    int peek() {
        if (st2.empty())
        {
            int tmp = -1;
            while (!st1.empty())
            {
                tmp = st1.top();
                st1.pop();
                st2.push(tmp);
            }
        }
        return st2.top();
    }
    
    bool empty() {
        return st2.empty() && st1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */