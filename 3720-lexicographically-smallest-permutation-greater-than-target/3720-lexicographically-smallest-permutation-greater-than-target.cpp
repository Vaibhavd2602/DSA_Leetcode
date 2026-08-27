class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        string ans;

        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';

            // Equal character available
            if (freq[x] > 0) {
                ans += target[i];
                freq[x]--;
                continue;
            }

            // Try a character greater than target[i]
            for (int c = x + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    ans += char('a' + c);
                    freq[c]--;

                    // Remaining characters in sorted order
                    for (int j = 0; j < 26; j++) {
                        while (freq[j] > 0) {
                            ans += char('a' + j);
                            freq[j]--;
                        }
                    }

                    return ans;
                }
            }

            // No greater character at current position.
            // Backtrack.
            while (!ans.empty()) {
                int last = ans.back() - 'a';
                ans.pop_back();
                freq[last]++;

                int pos = ans.size();
                int need = target[pos] - 'a';

                for (int c = need + 1; c < 26; c++) {
                    if (freq[c] > 0) {
                        ans += char('a' + c);
                        freq[c]--;

                        // Fill remaining characters
                        for (int j = 0; j < 26; j++) {
                            while (freq[j] > 0) {
                                ans += char('a' + j);
                                freq[j]--;
                            }
                        }

                        return ans;
                    }
                }
            }

            return "";
        }

        // s permutation == target
        // Need strictly greater, so backtrack.
        while (!ans.empty()) {
            int last = ans.back() - 'a';
            ans.pop_back();
            freq[last]++;

            int pos = ans.size();
            int need = target[pos] - 'a';

            for (int c = need + 1; c < 26; c++) {
                if (freq[c] > 0) {
                    ans += char('a' + c);
                    freq[c]--;

                    for (int j = 0; j < 26; j++) {
                        while (freq[j] > 0) {
                            ans += char('a' + j);
                            freq[j]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};