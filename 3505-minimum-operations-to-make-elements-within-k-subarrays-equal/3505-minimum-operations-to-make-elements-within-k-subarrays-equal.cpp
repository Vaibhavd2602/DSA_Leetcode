class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }

            // Balance the two sets
            if (low.size() > high.size() + 1) {
                int v = *low.rbegin();
                low.erase(low.find(v));
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            }

            if (low.size() < high.size()) {
                int v = *high.begin();
                high.erase(high.find(v));
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            // Balance
            if (low.size() > high.size() + 1) {
                int v = *low.rbegin();
                low.erase(low.find(v));
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            }

            if (low.size() < high.size()) {
                int v = *high.begin();
                high.erase(high.find(v));
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        vector<long long> cost(n - x + 1);

        // Calculate sliding window costs
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                long long median = *low.rbegin();

                long long leftCost =
                    median * low.size() - sumLow;

                long long rightCost =
                    sumHigh - median * high.size();

                cost[i - x + 1] = leftCost + rightCost;
            }
        }

        // Dynamic Programming
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        dp[0][0] = 0;

        for (int j = 0; j <= k; j++) {
            for (int i = 0; i <= n; i++) {

                if (i > 0) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j][i - 1]
                    );
                }

                if (j > 0 && i >= x &&
                    dp[j - 1][i - x] != INF) {

                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};