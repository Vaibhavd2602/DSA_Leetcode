class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // Minimum odd hai
        if (mn % 2 == 1)
            return true;

        // Minimum even hai, ab koi odd hua to false
        for (int x : nums1) {
            if (x % 2 == 1)
                return false;
        }

        return true;
    }
};