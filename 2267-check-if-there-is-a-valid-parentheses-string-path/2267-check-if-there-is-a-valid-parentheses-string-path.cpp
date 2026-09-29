class Solution {
public:
    int m, n;
    int dp[101][101][101];

    bool solve(int i, int j, int balance,
               vector<vector<char>>& grid) {

        // Invalid balance
        if (balance < 0) return false;

        // Remaining cells are not enough to close brackets
        int remaining = (m - 1 - i) + (n - 1 - j);
        if (balance > remaining) return false;

        // Destination reached
        if (i == m - 1 && j == n - 1) {
            return balance == 0;
        }

        int &ans = dp[i][j][balance];

        if (ans != -1) return ans;

        ans = 0;

        // Move right
        if (j + 1 < n) {
            int newBalance = balance +
                (grid[i][j + 1] == '(' ? 1 : -1);

            if (solve(i, j + 1, newBalance, grid)) {
                return ans = 1;
            }
        }

        // Move down
        if (i + 1 < m) {
            int newBalance = balance +
                (grid[i + 1][j] == '(' ? 1 : -1);

            if (solve(i + 1, j, newBalance, grid)) {
                return ans = 1;
            }
        }

        return ans;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if ((m + n) % 2 == 0) return false;

        memset(dp, -1, sizeof(dp));

        int balance = (grid[0][0] == '(' ? 1 : -1);

        return solve(0, 0, balance, grid);
    }
};