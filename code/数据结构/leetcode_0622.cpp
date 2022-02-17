class MyCircularQueue {
private:
    vector<int> queueArr;
    int front, rear;
    int capacity = 0;
public:
    MyCircularQueue(int k) {
        queueArr = vector<int>(k + 1); // 多留一个空闲单位
        front = rear = 0;
        capacity = k + 1;
    }
    
    bool enQueue(int value) {
        if (isFull())
            return false;
        queueArr[rear] = value;
        rear = (rear + 1) % capacity;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty())
            return false;
        front = (front + 1) % capacity;
        return true;
    }
    
    int Front() {
        if (isEmpty())
            return -1;
        return queueArr[front];
    }
    
    int Rear() {
        if (isEmpty())
            return -1;
        return queueArr[(rear + capacity - 1 ) % capacity];
    }
    
    bool isEmpty() {
        if (rear == front)
            return true;
        return false;
    }
    
    bool isFull() {
        if ((rear + 1) % capacity == front)
            return true;
        return false;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */