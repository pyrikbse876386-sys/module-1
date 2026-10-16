class Solution {
public:
    static const int MOD = 1e9 + 7;

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        unordered_map<int, int> last;

        function<void(int, int, int)> push = [&](int node, int l, int r) {
            if (lazy[node] == 0) return;

            long long v = lazy[node];
            long long len = r - l + 1;

            sq[node] = (sq[node] + 2 * v * sum[node] + v * v * len) % MOD;
            sum[node] = (sum[node] + v * len) % MOD;

            if (l != r) {
                lazy[node * 2] = (lazy[node * 2] + v) % MOD;
                lazy[node * 2 + 1] = (lazy[node * 2 + 1] + v) % MOD;
            }

            lazy[node] = 0;
        };

        function<void(int, int, int, int, int)> update =
        [&](int node, int l, int r, int ql, int qr) {
            push(node, l, r);

            if (r < ql || l > qr) return;

            if (ql <= l && r <= qr) {
                lazy[node] = 1;
                push(node, l, r);
                return;
            }

            int mid = l + (r - l) / 2;

            update(node * 2, l, mid, ql, qr);
            update(node * 2 + 1, mid + 1, r, ql, qr);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int l = 0;

            if (last.count(nums[i])) {
                l = last[nums[i]] + 1;
            }

            update(1, 0, n - 1, l, i);

            last[nums[i]] = i;

            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};