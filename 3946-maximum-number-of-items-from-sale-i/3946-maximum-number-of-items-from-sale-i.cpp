
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> dp(budget + 1, 0);

        int minPrice = INT_MAX;

        for (int i = 0; i < n; i++) {
            minPrice = min(minPrice, items[i][1]);
        }

        for (int i = 0; i < n; i++) {

            int factor = items[i][0];
            int price = items[i][1];

            int freeItems = 0;

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % factor == 0) {
                    freeItems++;
                }
            }

            for (int j = budget; j >= price; j--) {
                dp[j] = max(dp[j],
                            dp[j - price] + freeItems + 1);
            }
        }

        int ans = 0;

        for (int i = 0; i <= budget; i++) {
            ans = max(ans,
                      dp[i] + (budget - i) / minPrice);
        }

        return ans;
    }
};
