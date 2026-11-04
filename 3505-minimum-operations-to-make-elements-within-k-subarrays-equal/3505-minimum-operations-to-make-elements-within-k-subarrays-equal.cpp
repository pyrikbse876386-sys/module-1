
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {

        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        // Balance the two halves
        auto balance = [&]() {

            int need = (x + 1) / 2;

            while ((int)low.size() > need) {
                int val = *low.rbegin();

                low.erase(prev(low.end()));
                sumLow -= val;

                high.insert(val);
                sumHigh += val;
            }

            while ((int)low.size() < need && !high.empty()) {
                int val = *high.begin();

                high.erase(high.begin());
                sumHigh -= val;

                low.insert(val);
                sumLow += val;
            }
        };

        // Insert an element
        auto add = [&](int val) {

            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }

            balance();
        };

        // Remove an element
        auto remove = [&](int val) {

            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            balance();
        };

        vector<long long> cost;

        // Sliding window
        for (int i = 0; i < n; i++) {

            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {

                long long median = *low.rbegin();

                long long operations =
                    median * low.size() - sumLow
                    + sumHigh - median * high.size();

                cost.push_back(operations);
            }
        }

        // Dynamic Programming
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= k; j++) {

                // Skip current position
                dp[i][j] = dp[i - 1][j];

                // Select a window of size x
                if (i >= x) {

                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
