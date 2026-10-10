
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;

        vector<long long> diff(n);
        long long total = 0;
        long long high = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            high = max(high, diff[i]);
        }

        if (total <= k) return 0;

        long long low = 0;

        while (low < high) {
            long long mid = low + (high - low) / 2;
            long long operations = 0;

            for (int i = 0; i < n; i++) {
                if (diff[i] > mid) {
                    operations += diff[i] - mid;
                }
            }

            if (operations <= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        long long ans = 0;
        long long operations = 0;

        for (int i = 0; i < n; i++) {
            if (diff[i] > low) {
                operations += diff[i] - low;
                diff[i] = low;
            }
            ans += diff[i] * diff[i];
        }

        long long remaining = k - operations;

        for (int i = 0; i < n && remaining > 0; i++) {
            if (diff[i] == low && diff[i] > 0) {
                ans -= diff[i] * diff[i];
                diff[i]--;
                ans += diff[i] * diff[i];
                remaining--;
            }
        }

        return ans;
    }
};

