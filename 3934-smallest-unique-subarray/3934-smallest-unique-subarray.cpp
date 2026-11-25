class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {   // use the method name from LeetCode's starter code
        typedef unsigned long long ull;
        int n = nums.size();
        const ull MOD = (1ULL << 61) - 1;

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        ull B = rng() % (MOD - 1000000) + 1000000;

        auto mul = [&](ull a, ull b) {
            __uint128_t t = (__uint128_t)a * b;
            ull r = (ull)(t & MOD) + (ull)(t >> 61);
            if (r >= MOD) r -= MOD;
            return r;
        };

        vector<ull> h(n + 1, 0), p(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = mul(h[i], B) + nums[i];
            if (h[i + 1] >= MOD) h[i + 1] -= MOD;
            p[i + 1] = mul(p[i], B);
        }

        auto hasUnique = [&](int L) {
            vector<ull> v;
            v.reserve(n - L + 1);
            for (int i = 0; i + L <= n; i++) {
                ull x = h[i + L] + MOD - mul(h[i], p[L]);
                if (x >= MOD) x -= MOD;
                v.push_back(x);
            }
            sort(v.begin(), v.end());
            int m = v.size();
            for (int j = 0; j < m; j++) {
                bool leftDiff  = (j == 0)     || v[j] != v[j - 1];
                bool rightDiff = (j == m - 1) || v[j] != v[j + 1];
                if (leftDiff && rightDiff) return true;
            }
            return false;
        };

        int lo = 1, hi = n;              // length n is always unique
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (hasUnique(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};