
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n), newAdj(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> last(26, -1);

        // Find closest ancestor with same character
        function<void(int)> dfs1 = [&](int u) {
            int c = s[u] - 'a';

            int old = last[c];

            if (old != -1) {
                newAdj[old].push_back(u);
            } 
            else if (parent[u] != -1) {
                newAdj[parent[u]].push_back(u);
            }

            last[c] = u;

            for (int v : adj[u]) {
                dfs1(v);
            }

            last[c] = old;
        };

        dfs1(0);

        vector<int> ans(n, 0);

        // Calculate subtree sizes
        function<int(int)> dfs2 = [&](int u) {
            int size = 1;

            for (int v : newAdj[u]) {
                size += dfs2(v);
            }

            ans[u] = size;
            return size;
        };

        dfs2(0);

        return ans;
    }
};
