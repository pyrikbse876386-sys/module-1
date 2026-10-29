
class Solution {
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> tin, tout, depth;
    vector<int> bit;
    string chars;
    int timer = 0;
    int LOG;

    // Fenwick Tree: XOR update
    void update(int i, int val, int n) {
        while (i <= n) {
            bit[i] ^= val;
            i += i & -i;
        }
    }

    // Prefix XOR query
    int queryBIT(int i) {
        int ans = 0;

        while (i > 0) {
            ans ^= bit[i];
            i -= i & -i;
        }

        return ans;
    }

    // Range XOR update
    void rangeUpdate(int l, int r, int val, int n) {
        update(l, val, n);
        update(r + 1, val, n);
    }

    // DFS: Euler Tour + parent information
    void dfs(int u, int parent) {
        tin[u] = ++timer;

        up[u][0] = parent;

        for (int j = 1; j < LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int v : adj[u]) {
            if (v == parent) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    // Lowest Common Ancestor
    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[u][j];
            }
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

    // Character to bitmask
    int getMask(char c) {
        return 1 << (c - 'a');
    }

    // At most one bit should be set
    bool isPalindrome(int mask) {
        return (mask & (mask - 1)) == 0;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, vector<int>());
        chars = s;

        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);

        LOG = 1;
        while ((1 << LOG) <= n) {
            LOG++;
        }

        up.assign(n, vector<int>(LOG, 0));
        bit.assign(n + 2, 0);

        // Build tree
        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Root the tree at node 0
        dfs(0, 0);

        // Initialize root-to-node prefix masks.
        // Each node's character affects its entire subtree.
        for (int u = 0; u < n; u++) {
            rangeUpdate(
                tin[u],
                tout[u],
                getMask(chars[u]),
                n
            );
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);

            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta =
                    getMask(chars[u]) ^ getMask(c);

                rangeUpdate(tin[u], tout[u], delta, n);

                chars[u] = c;
            }
            else {
                int v;
                ss >> v;

                int w = lca(u, v);

                int maskU = queryBIT(tin[u]);
                int maskV = queryBIT(tin[v]);

                int mask =
                    maskU ^ maskV ^ getMask(chars[w]);

                ans.push_back(isPalindrome(mask));
            }
        }

        return ans;
    }
};