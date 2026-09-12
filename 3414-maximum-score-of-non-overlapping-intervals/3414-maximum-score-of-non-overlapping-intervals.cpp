class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> v;

        for (int i = 0; i < n; i++) {
            v.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(v.begin(), v.end());

        // next[i] = first interval whose start > v[i].end
        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            int l = i + 1, r = n;

            while (l < r) {
                int mid = l + (r - l) / 2;

                if (v[mid][0] > v[i][1])
                    r = mid;
                else
                    l = mid + 1;
            }

            next[i] = l;
        }

        // dp[i][k] = best answer from i onwards,
        // selecting at most k intervals
        vector<vector<pair<long long, vector<int>>>> dp(
            n + 1,
            vector<pair<long long, vector<int>>>(5, {0, {}})
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Don't take
                dp[i][k] = dp[i + 1][k];

                // Take
                long long score =
                    v[i][2] + dp[next[i]][k - 1].first;

                vector<int> ans =
                    dp[next[i]][k - 1].second;

                ans.push_back(v[i][3]);

                sort(ans.begin(), ans.end());

                if (score > dp[i][k].first) {
                    dp[i][k] = {score, ans};
                }
                else if (score == dp[i][k].first) {

                    vector<int> cur = dp[i][k].second;
                    sort(cur.begin(), cur.end());

                    if (ans < cur) {
                        dp[i][k] = {score, ans};
                    }
                }
            }
        }

        return dp[0][4].second;
    }
};