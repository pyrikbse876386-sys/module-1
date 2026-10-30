
class Solution {
    struct Node {
        int node, dist, cnt;

        bool operator>(const Node& other) const {
            return dist > other.dist;
        }
    };

public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {

        vector<vector<pair<int, int>>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));

        priority_queue<Node, vector<Node>, greater<Node>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();

            int u = curr.node;
            int d = curr.dist;
            int cnt = curr.cnt;

            if (d != dist[u][cnt]) {
                continue;
            }

            if (u == n - 1) {
                return d;
            }

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;

                int newCnt;

                if (labels[u] == labels[v]) {
                    newCnt = cnt + 1;
                } else {
                    newCnt = 1;
                }

                if (newCnt > k) {
                    continue;
                }

                int newDist = d + w;

                if (newDist < dist[v][newCnt]) {
                    dist[v][newCnt] = newDist;
                    pq.push({v, newDist, newCnt});
                }
            }
        }

        return -1;
    }
};
