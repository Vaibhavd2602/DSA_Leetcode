class Solution {
public:
    int n;
    vector<int> suffix;
    int dp[105][105];

    int solve(int i, int M) {
        // No piles left
        if (i >= n)
            return 0;

        // Can take all remaining piles
        if (i + 2 * M >= n)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        // Take X piles
        for (int X = 1; X <= 2 * M; X++) {
            int opponent = solve(i + X, max(M, X));

            int current = suffix[i] - opponent;

            ans = max(ans, current);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        suffix.resize(n + 1, 0);

        // suffix[i] = sum of piles from i to n-1
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        memset(dp, -1, sizeof(dp));

        return solve(0, 1);
    }
};