class Solution {
public:
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& suspicious) {
        suspicious[node] = true;

        for (int nei : adj[node]) {
            if (!suspicious[nei]) {
                dfs(nei, adj, suspicious);
            }
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);

        // Build graph
        for (auto &edge : invocations) {
            adj[edge[0]].push_back(edge[1]);
        }

        // Mark suspicious methods
        vector<bool> suspicious(n, false);
        dfs(k, adj, suspicious);

        // Check if any outside method invokes a suspicious method
        for (auto &edge : invocations) {
            int u = edge[0];
            int v = edge[1];

            if (!suspicious[u] && suspicious[v]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Return remaining methods
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};