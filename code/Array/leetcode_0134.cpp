class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int i = 0;
        while (i < n)
        {
            int gasNum = 0, costNum = 0;
            int cnt = 0;
            while (cnt < n) // 走过cnt个
            {
                int j = (i + cnt) % n;
                gasNum += gas[j];
                costNum += cost[j];
                if (gasNum < costNum)
                    break;
                ++cnt;
            }

            if (cnt == n)
                return i;
            else
                i += cnt + 1;
        }
        return -1;
    }
};