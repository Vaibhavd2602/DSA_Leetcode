class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> ans(m);

        // last[j] = last index in word1
        // where word2[j] can be matched
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Build last[]
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        // Only one mismatch is allowed
        bool mismatchUsed = false;

        i = 0;
        j = 0;

        while (i < n && j < m) {

            // Normal matching
            if (word1[i] == word2[j]) {
                ans[j] = i;
                j++;
            }

            // Use this index as the one mismatch
            else if (!mismatchUsed &&
                     (j == m - 1 || i < last[j + 1])) {

                ans[j] = i;
                mismatchUsed = true;
                j++;
            }

            i++;
        }

        // Could not find enough indices
        if (j != m)
            return {};

        return ans;
    }
};