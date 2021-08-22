// 方法一：暴力解法 O(n^2)
vector<int> twoSum(vector<int>& nums, int target) 
{
    int i, j;
    for(i = 0; i < nums.size() - 1; i++)
    {
        for(j = i + 1; j < nums.size(); j++)
        {
            if (nums[i] + nums[j] == target)
            {
                vector<int> v;
                v.push_back(i);
                v.push_back(j);
                return v;
            }
        }
    }
    return {i, j};
}
 
 // 方法二：hash表法  O(n)
 vector<int> twoSum(vector<int>& nums, int target) 
{
	int i;
	int another = -1;
	map<int, int> m;
	m.insert(make_pair(nums[0], 0));
    for (i = 1; i < nums.size(); ++i)
    {
        another = target - nums[i];
        if (m.count(another) == 1 && m[another] != i)
            return {m[another], i};
        else
            m.insert(make_pair(nums[i], i));
    }
}
