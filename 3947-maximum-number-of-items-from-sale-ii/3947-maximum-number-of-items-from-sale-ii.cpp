
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {

        int n = items.size();

        
        int maxFactor = 0;

        for (auto &it : items) {
            maxFactor = max(maxFactor, it[0]);
        }

       
        vector<int> freq(maxFactor + 1, 0);

        for (auto &it : items) {
            freq[it[0]]++;
        }

       
        for (int i = 1; i <= maxFactor; i++) {

            for (int j = 2 * i; j <= maxFactor; j += i) {
                freq[i] += freq[j];
            }
        }

     
        int minPrice = INT_MAX;

        for (auto &it : items) {
            minPrice = min(minPrice, it[1]);
        }

     
        vector<pair<int, int>> v;

        for (auto &it : items) {

            int factor = it[0];
            int price = it[1];

            int gain = freq[factor] - 1;

            v.push_back({price, gain});
        }

        
        sort(v.begin(), v.end());

        long long ans = 0;
        long long remaining = budget;

        
        for (auto &it : v) {

            int price = it.first;
            int gain = it.second;

            if (price >= 2LL * minPrice) {
                break;
            }

            long long take = min(
                remaining / price,
                (long long)gain
            );

            ans += take * 2;
            remaining -= take * price;
        }

       
        ans += remaining / minPrice;

        return (int)ans;
    }
};
