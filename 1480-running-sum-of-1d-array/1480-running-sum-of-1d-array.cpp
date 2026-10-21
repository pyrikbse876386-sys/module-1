class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int size=nums.size();
        vector<int> ans;
        int running_sum=0;
        for(int i=0;i<size;i++){
            running_sum=running_sum+nums[i];
            ans.push_back(running_sum);
        }
        return ans;
    }
};