
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares;

        for (int x : nums) {
            squares.push_back(1LL * x * x);
        }

        sort(squares.begin(), squares.end());

        long long ans = 0;
        int half = n / 2;

        for (int i = 0; i < half; i++) {
            ans -= squares[i];
        }

        for (int i = half; i < n; i++) {
            ans += squares[i];
        }

        return ans;
    }
};

