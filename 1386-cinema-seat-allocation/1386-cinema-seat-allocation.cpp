class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats as a bitmask for each row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            // We only care about seats 2 to 9
            if (s >= 2 && s <= 9) {
                mp[row] |= (1 << s);
            }
        }

        long long ans = 2LL * n;

        for (auto &[row, mask] : mp) {
            int groups = 0;

            // Left block: 2,3,4,5
            bool left = true;
            for (int s = 2; s <= 5; s++) {
                if (mask & (1 << s)) {
                    left = false;
                    break;
                }
            }

            // Right block: 6,7,8,9
            bool right = true;
            for (int s = 6; s <= 9; s++) {
                if (mask & (1 << s)) {
                    right = false;
                    break;
                }
            }

            // Middle block: 4,5,6,7
            bool middle = true;
            for (int s = 4; s <= 7; s++) {
                if (mask & (1 << s)) {
                    middle = false;
                    break;
                }
            }

            if (left && right) {
                // Can place two groups
                groups = 2;
            }
            else if (left || middle || right) {
                // Can place one group
                groups = 1;
            }

            // This row was already counted as 2 in 2*n
            ans -= 2;
            ans += groups;
        }

        return (int)ans;
    }
};