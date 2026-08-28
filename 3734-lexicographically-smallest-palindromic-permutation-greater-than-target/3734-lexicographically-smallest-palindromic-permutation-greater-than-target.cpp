class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        // A palindrome can have at most one odd frequency
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        // Remove the middle character
        if (n % 2) {
            cnt[mid - 'a']--;
        }

        /*
            cnt now contains characters that will be
            divided equally between left and right.
        */

        // Try to make left half equal to target's left half
        vector<int> rem = cnt;

        bool possible = true;

        for (int i = 0; i < n / 2; i++) {
            int x = target[i] - 'a';

            if (rem[x] < 2) {
                possible = false;
                break;
            }

            rem[x] -= 2;
        }

        if (possible) {

            string left = target.substr(0, n / 2);

            string right = left;
            reverse(right.begin(), right.end());

            string candidate;

            if (n % 2) {
                candidate = left + string(1, mid) + right;
            } else {
                candidate = left + right;
            }

            // Same left half, but right half may make it greater
            if (candidate > target) {
                return candidate;
            }
        }

        /*
            We couldn't get an answer with the same
            left half.

            Now find the rightmost position where we can
            increase target[i].
        */

        rem = cnt;

        // First consume target's left half
        for (int i = 0; i < n / 2; i++) {
            int x = target[i] - 'a';

            if (rem[x] >= 2) {
                rem[x] -= 2;
            } else {
                // Can't match this prefix
                // We will handle this through backtracking
                break;
            }
        }

        /*
            Easier and safer construction:

            Start from the rightmost position of the
            left half and try increasing it.
        */

        for (int pos = n / 2 - 1; pos >= 0; pos--) {

            // Rebuild available counts for prefix [0, pos)
            vector<int> available = cnt;

            bool prefixPossible = true;

            for (int i = 0; i < pos; i++) {

                int x = target[i] - 'a';

                if (available[x] < 2) {
                    prefixPossible = false;
                    break;
                }

                available[x] -= 2;
            }

            if (!prefixPossible)
                continue;

            int current = target[pos] - 'a';

            // Try the smallest character greater than target[pos]
            for (int c = current + 1; c < 26; c++) {

                if (available[c] < 2)
                    continue;

                available[c] -= 2;

                string left = target.substr(0, pos);

                left += char('a' + c);

                // Fill remaining positions with smallest chars
                for (int k = pos + 1; k < n / 2; k++) {

                    for (int x = 0; x < 26; x++) {

                        if (available[x] >= 2) {
                            left += char('a' + x);
                            available[x] -= 2;
                            break;
                        }
                    }
                }

                string right = left;
                reverse(right.begin(), right.end());

                string ans;

                if (n % 2) {
                    ans = left + string(1, mid) + right;
                } else {
                    ans = left + right;
                }

                if (ans > target) {
                    return ans;
                }

                available[c] += 2;
            }
        }

        return "";
    }
};