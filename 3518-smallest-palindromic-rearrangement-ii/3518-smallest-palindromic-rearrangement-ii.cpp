class Solution {
public:
    static const int LIMIT = 1000001;

    // nCr capped at LIMIT
    long long comb(int n, int r) {
        if (r > n) return 0;
        r = min(r, n - r);

        long long ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans >= LIMIT) return LIMIT;
        }
        return min(ans, (long long)LIMIT);
    }

    // Count distinct permutations
    long long countWays(vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ways = 1;
        int rem = total;

        for (int x : cnt) {
            if (x == 0) continue;

            ways *= comb(rem, x);
            if (ways >= LIMIT) return LIMIT;

            rem -= x;
        }

        return ways;
    }

    // Changed function name
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2)
                mid.push_back(char('a' + i));
        }

        if (countWays(half) < k)
            return "";

        string left = "";
        int len = s.size() / 2;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};