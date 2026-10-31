
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][0] = entered while moving right
        // dp[i][j][1] = entered while moving down
        vector<vector<vector<long long>>> dp(
            m, vector<vector<long long>>(n, vector<long long>(2, 0))
        );

        // Starting point
        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // First cell: choose right or down
                if (i == 0 && j == 0) {
                    if (j + 1 < n) {
                        if (grid[0][1] == 0)
                            dp[0][1][0] = 1;
                        else if (i + 1 < m)
                            dp[1][1][1] = 1;
                    }

                    if (i + 1 < m) {
                        if (grid[1][0] == 0)
                            dp[1][0][1] = 1;
                        else if (j + 1 < n)
                            dp[1][1][0] = 1;
                    }
                    continue;
                }

                long long right = dp[i][j][0];
                long long down = dp[i][j][1];

                // Empty cell: move right and down
                if (grid[i][j] == 0) {

                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + right + down) % MOD;
                    }

                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + right + down) % MOD;
                    }
                }

                // Mirror: right becomes down, down becomes right
                else {
                    if (i + 1 < m) {
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + right) % MOD;
                    }

                    if (j + 1 < n) {
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + down) % MOD;
                    }
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};
