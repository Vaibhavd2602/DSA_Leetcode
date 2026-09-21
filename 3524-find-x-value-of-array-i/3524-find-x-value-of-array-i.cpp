class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k);
        vector<long long> dp(k);

        for (int num : nums) {
            vector<long long> newDp(k);

            int numMod = num % k;

            // Current element se ek naya subarray
            newDp[numMod] = 1;

            // Previous subarrays ko current number ke saath extend karo
            for (int i = 0; i < k; i++) {
                int newMod = (1LL * i * numMod) % k;
                newDp[newMod] += dp[i];
            }

            // Current ending wale saare subarrays ko answer mein add karo
            for (int i = 0; i < k; i++) {
                ans[i] += newDp[i];
            }

            dp = newDp;
        }

        return ans;
    }
};