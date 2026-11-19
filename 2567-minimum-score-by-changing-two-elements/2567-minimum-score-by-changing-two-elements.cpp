class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.size();

        int ans = INT_MAX;

        // Case 1: Change first two elements
        ans = min(ans, nums[n - 1] - nums[2]);

        // Case 2: Change last two elements
        ans = min(ans, nums[n - 3] - nums[0]);

        // Case 3: Change one element from each side
        ans = min(ans, nums[n - 2] - nums[1]);

        return ans;
    }
};
