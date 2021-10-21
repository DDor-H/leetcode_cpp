
class MyHashMap {
private:
    vector<list<pair<int, int>>> vm;
    static const int base = 769;
    static int hash(int key)
    {
        return key % base;
    }

public:
    MyHashMap(): vm(base) {}
    
    void put(int key, int value) {
        int h = hash(key);
        for (auto it = vm[h].begin(); it != vm[h].end(); ++it)
        {
            if (it->first == key)
            {
                it->second = value;
                return;
            }
        }
        vm[h].push_back(make_pair(key, value));
    }
    
    int get(int key) {
        int h = hash(key);
        for (auto it = vm[h].begin(); it != vm[h].end(); ++it)
        {
            if (it->first == key)
                return it->second;
        }
        return -1;
    }
    
    void remove(int key) {
        int h = hash(key);
        for (auto it = vm[h].begin(); it != vm[h].end(); ++it)
        {
            if (it->first == key)
            {
                vm[h].erase(it);
                return;
            }
        }
    }
};

/*
class MyHashMap {
private:
    vector<vector<int>> vm;
public:
    MyHashMap() {
        vm = vector<vector<int>>();
    }
    
    void put(int key, int value) {
        int i = 0;
        for (; i < vm.size(); ++i)
        {
            if (vm[i][0] == key)
            {
                vm[i][1] = value;
                return;
            }
        }
        vm.push_back({key, value});
    }
    
    int get(int key) {
        for (int i = 0; i < vm.size(); ++i)
        {
            if (vm[i][0] == key)
                return vm[i][1];
        }
        return -1;
    }
    
    void remove(int key) {
        for (auto it = vm.begin(); it != vm.end(); ++it)
        {
            if ((*it)[0] == key)
            {
                vm.erase(it);
                return;
            }
        }
    }
};
*/

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */