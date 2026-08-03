class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {
        vector<bool> prime(n + 1, true);
        vector<vector<int>> ans;

        if (n < 2)
            return ans;

        prime[0] = prime[1] = false;

        // Sieve of Eratosthenes
        for (int i = 2; i * i <= n; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    prime[j] = false;
                }
            }
        }

        // Find prime pairs
        for (int i = 2; i <= n / 2; i++) {
            if (prime[i] && prime[n - i]) {
                ans.push_back({i, n - i});
            }
        }

        return ans;
    }
};