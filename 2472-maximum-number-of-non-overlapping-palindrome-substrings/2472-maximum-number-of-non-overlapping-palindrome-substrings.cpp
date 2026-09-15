class Solution {
public:
    int maxPalindromes(string s, int k) {

        int n = s.size();

        vector<vector<bool>> pal(n, vector<bool>(n, false));

        // Palindrome check
        for(int len = 1; len <= n; len++) {

            for(int i = 0; i + len - 1 < n; i++) {

                int j = i + len - 1;

                if(len == 1) {
                    pal[i][j] = true;
                }

                else if(len == 2) {
                    pal[i][j] = (s[i] == s[j]);
                }

                else {
                    pal[i][j] = (s[i] == s[j] && pal[i + 1][j - 1]);
                }
            }
        }

        vector<int> dp(n + 1, 0);

        for(int i = 1; i <= n; i++) {

            // Don't take s[i-1]
            dp[i] = dp[i - 1];

            // Try every palindrome ending at i-1
            for(int j = 0; j <= i - k; j++) {

                if(pal[j][i - 1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};