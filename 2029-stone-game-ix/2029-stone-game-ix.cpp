class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // If there are no 1 or 2 remainder stones,
        // Alice cannot make a safe first move.
        if (cnt[1] == 0 && cnt[2] == 0) {
            return false;
        }

        // If number of 0-remainder stones is even,
        // Alice wins when both 1 and 2 are available.
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // If number of 0-remainder stones is odd,
        // Alice needs the counts of 1 and 2 to differ by more than 2.
        return abs(cnt[1] - cnt[2]) > 2;
    }
};