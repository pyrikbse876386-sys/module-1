class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        // Sort logs according to time
        sort(logs.begin(), logs.end(),
             [](vector<int>& a, vector<int>& b) {
                 return a[1] < b[1];
             });

        int m = queries.size();

        vector<pair<int,int>> q;

        for(int i = 0; i < m; i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(m);
        unordered_map<int,int> mp;

        int left = 0, right = 0;
        int count = 0;

        for(auto [time, idx] : q) {

            // Add logs up to current query time
            while(right < logs.size() &&
                  logs[right][1] <= time) {

                int id = logs[right][0];

                if(mp[id] == 0) {
                    count++;
                }

                mp[id]++;
                right++;
            }

            // Remove logs outside the time window
            while(left < right &&
                  logs[left][1] < time - x) {

                int id = logs[left][0];

                mp[id]--;

                if(mp[id] == 0) {
                    count--;
                }

                left++;
            }

            ans[idx] = n - count;
        }

        return ans;
    }
};