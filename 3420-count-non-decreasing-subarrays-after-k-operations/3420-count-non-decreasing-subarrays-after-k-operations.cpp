
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 1;

        while ((1 << LOG) <= n) LOG++;

        vector<int> nxt(n, n);
        vector<int> st;

        // Step 1: Next Greater Element
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.back()] <= nums[i]) {
                st.pop_back();
            }

            if (!st.empty()) {
                nxt[i] = st.back();
            }

            st.push_back(i);
        }

        // Prefix Sum
        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Step 2: Binary Lifting
        vector<vector<int>> up(LOG, vector<int>(n, n));
        vector<vector<long long>> cost(LOG, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            cost[0][i] =
                1LL * nums[i] * (nxt[i] - i - 1)
                - (pref[nxt[i]] - pref[i + 1]);
        }

        for (int b = 1; b < LOG; b++) {
            for (int i = 0; i < n; i++) {
                int mid = up[b - 1][i];

                if (mid < n && up[b - 1][mid] < n) {
                    up[b][i] = up[b - 1][mid];

                    cost[b][i] =
                        cost[b - 1][i] + cost[b - 1][mid];
                }
            }
        }

        // Step 3: Calculate operations needed
        auto getCost = [&](int l, int r) -> long long {
            long long ans = 0;
            int p = l;

            for (int b = LOG - 1; b >= 0; b--) {
                int next = up[b][p];

                if (next <= r) {
                    ans += cost[b][p];
                    p = next;
                }
            }

            // Remaining partial segment
            ans += 1LL * nums[p] * (r - p)
                   - (pref[r + 1] - pref[p + 1]);

            return ans;
        };

        // Step 4: Sliding Window
        long long answer = 0;
        int left = 0;

        for (int right = 0; right < n; right++) {

            while (left <= right && getCost(left, right) > k) {
                left++;
            }

            answer += right - left + 1;
        }

        return answer;
    }
};
