class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
         
        int ans = 0;
        int median = nums[n/2];
        for(int x : nums){
            ans += abs(x - median);
        }
        return ans;
    }
};