
class Solution {
public:
    static const int MOD = 1e9 + 7;

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto update = [&](auto&& self, int node, int start,
                          int end, int l, int r,
                          long long val) -> void {
            if (r < start || end < l) return;

            if (l <= start && end <= r) {
                sq[node] = (sq[node]
                    + 2LL * val % MOD * sum[node] % MOD
                    + (end - start + 1LL) * val % MOD * val % MOD)
                    % MOD;

                sum[node] = (sum[node]
                    + (end - start + 1LL) * val) % MOD;

                lazy[node] = (lazy[node] + val) % MOD;
                return;
            }

            int mid = start + (end - start) / 2;
            int left = node * 2;
            int right = left + 1;

            if (lazy[node] != 0) {
                long long v = lazy[node];

                sq[left] = (sq[left]
                    + 2LL * v % MOD * sum[left] % MOD
                    + (mid - start + 1LL) * v % MOD * v % MOD)
                    % MOD;

                sum[left] = (sum[left]
                    + (mid - start + 1LL) * v) % MOD;

                lazy[left] = (lazy[left] + v) % MOD;

                sq[right] = (sq[right]
                    + 2LL * v % MOD * sum[right] % MOD
                    + (end - mid) * v % MOD * v % MOD)
                    % MOD;

                sum[right] = (sum[right]
                    + (end - mid) * v) % MOD;

                lazy[right] = (lazy[right] + v) % MOD;

                lazy[node] = 0;
            }

            self(self, left, start, mid, l, r, val);
            self(self, right, mid + 1, end, l, r, val);

            sum[node] = (sum[left] + sum[right]) % MOD;
            sq[node] = (sq[left] + sq[right]) % MOD;
        };

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int p = last[x];

            update(update, 1, 0, n - 1, p + 1, i, 1);

            ans = (ans + sq[1]) % MOD;
            last[x] = i;
        }

        return ans;
    }
};
