class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        unordered_set<int> pairs;

        // Store all possible pair XOR
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                pairs.insert(nums[i] ^ nums[j]);
            }
        }

        unordered_set<int> ans;

        // Pair XOR with third element
        for(auto x : pairs) {
            for(auto num : nums) {
                ans.insert(x ^ num);
            }
        }

        return ans.size();
    }
};