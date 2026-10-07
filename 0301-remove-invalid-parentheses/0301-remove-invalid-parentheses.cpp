class Solution {
public:

    void solve(string &s, int index,
               int leftRemove, int rightRemove,
               int open, string current,
               vector<string>& ans) {

        // Base case
        if (index == s.length()) {

            if (leftRemove == 0 &&
                rightRemove == 0 &&
                open == 0) {

                ans.push_back(current);
            }

            return;
        }

        char ch = s[index];

        // Case 1: '('
        if (ch == '(') {

            // Remove '('
            if (leftRemove > 0) {
                solve(s, index + 1,
                      leftRemove - 1,
                      rightRemove,
                      open,
                      current,
                      ans);
            }

            // Keep '('
            solve(s, index + 1,
                  leftRemove,
                  rightRemove,
                  open + 1,
                  current + ch,
                  ans);
        }

        // Case 2: ')'
        else if (ch == ')') {

            // Remove ')'
            if (rightRemove > 0) {
                solve(s, index + 1,
                      leftRemove,
                      rightRemove - 1,
                      open,
                      current,
                      ans);
            }

            // Keep ')' only if '(' is available
            if (open > 0) {
                solve(s, index + 1,
                      leftRemove,
                      rightRemove,
                      open - 1,
                      current + ch,
                      ans);
            }
        }

        // Case 3: letter
        else {
            solve(s, index + 1,
                  leftRemove,
                  rightRemove,
                  open,
                  current + ch,
                  ans);
        }
    }

    // Calculate minimum removals
    void calculateRemovals(string &s,
                           int &leftRemove,
                           int &rightRemove) {

        for (char ch : s) {

            if (ch == '(') {
                leftRemove++;
            }

            else if (ch == ')') {

                if (leftRemove > 0) {
                    leftRemove--;
                }
                else {
                    rightRemove++;
                }
            }
        }
    }

public:

    vector<string> removeInvalidParentheses(string s) {

        int leftRemove = 0;
        int rightRemove = 0;

        // Find minimum removals required
        calculateRemovals(s, leftRemove, rightRemove);

        vector<string> ans;

        solve(s, 0,
              leftRemove,
              rightRemove,
              0,
              "",
              ans);

        // Remove duplicate answers
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};