
class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n);
        vector<vector<int>> up(17, vector<int>(n));
        int timer = 0;

        function<void(int,int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[0][u] = p;

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
            tout[u] = timer;
        };

        // Euler tour and ancestors
        dfs(0, 0);

        for (int j = 1; j < 17; j++)
            for (int i = 0; i < n; i++)
                up[j][i] = up[j-1][up[j-1][i]];

        auto lca = [&](int a, int b) {
            if (depth[a] < depth[b]) swap(a, b);

            int diff = depth[a] - depth[b];
            for (int j = 0; j < 17; j++)
                if (diff & (1 << j)) a = up[j][a];

            if (a == b) return a;

            for (int j = 16; j >= 0; j--) {
                if (up[j][a] != up[j][b]) {
                    a = up[j][a];
                    b = up[j][b];
                }
            }
            return up[0][a];
        };

        vector<int> bit(n + 1, 0);

        auto add = [&](int idx, int val) {
            for (idx++; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto prefix = [&](int idx) {
            int res = 0;
            for (idx++; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        vector<int> mask(n);
        for (int i = 0; i < n; i++) {
            mask[i] = 1 << (s[i] - 'a');
            add(tin[i], mask[i]);
            add(tout[i], mask[i]);
        }

        // Each subtree's character XOR
        // A point update toggles both Euler boundaries.
        // For path queries, use root-prefix XORs.
        vector<bool> ans;

        for (string &q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                add(tin[u], mask[u]);
                add(tout[u], mask[u]);

                s[u] = c;
                mask[u] = 1 << (c - 'a');

                add(tin[u], mask[u]);
                add(tout[u], mask[u]);
            } else {
                ss >> v;
                int w = lca(u, v);

                int pu = prefix(tin[u]);
                int pv = prefix(tin[v]);
                int pw = prefix(tin[w]);

                int pathMask = pu ^ pv ^ mask[w];

                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};
