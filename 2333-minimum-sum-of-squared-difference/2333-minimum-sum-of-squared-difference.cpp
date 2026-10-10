class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        int n = nums1.size();
        long long k = 1LL * k1 + k2;

        vector<int> diff(n);
        int maxDiff = 0;
        long long total = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diff[i]);
            total += diff[i];
        }

        if (total <= k)
            return 0;

        int low = 0, high = maxDiff;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long ops = 0;

            for (int d : diff) {
                ops += max(0, d - mid);
            }

            if (ops <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long used = 0;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            if (diff[i] > level) {
                used += diff[i] - level;
                diff[i] = level;  // Fix: update the difference
            }
            ans += 1LL * diff[i] * diff[i];
        }

        long long remaining = k - used;

        for (int i = 0; i < n && remaining > 0; i++) {
            if (diff[i] == level && diff[i] > 0) {
                ans -= 1LL * diff[i] * diff[i];
                diff[i]--;
                ans += 1LL * diff[i] * diff[i];
                remaining--;
            }
        }

        return ans;
    }
};
