
class Solution {
public:
    using ll = long long;

    const ll MOD1 = 1000000007;
    const ll MOD2 = 1000000009;
    const ll BASE = 131;

    vector<ll> h1, h2, p1, p2;

    ll getHash(int l, int r) {
        ll x = (h1[r + 1] -
                h1[l] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;

        ll y = (h2[r + 1] -
                h2[l] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;

        return (x << 32) | y;
    }

    bool check(int len, int n) {
        unordered_map<ll, int> mp;

        for (int i = 0; i + len <= n; i++) {
            mp[getHash(i, i + len - 1)]++;
        }

        for (auto &it : mp) {
            if (it.second == 1)
                return true;
        }

        return false;
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);

        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * BASE + nums[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE + nums[i]) % MOD2;

            p1[i + 1] = p1[i] * BASE % MOD1;
            p2[i + 1] = p2[i] * BASE % MOD2;
        }

        int low = 1, high = n;
        int ans = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(mid, n)) {
                ans = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
