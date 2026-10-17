
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<int> sortedNums = nums;

        auto digitSum = [](int x) {
            int sum = 0;
            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }
            return sum;
        };

        sort(sortedNums.begin(), sortedNums.end(),
             [&](int a, int b) {
                 int sumA = digitSum(a);
                 int sumB = digitSum(b);

                 if (sumA == sumB) {
                     return a < b;
                 }

                 return sumA < sumB;
             });

        unordered_map<int, int> position;

        for (int i = 0; i < n; i++) {
            position[sortedNums[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || position[nums[i]] == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = position[nums[j]];
                cycleSize++;
            }

            swaps += cycleSize - 1;
        }

        return swaps;
    }
};
