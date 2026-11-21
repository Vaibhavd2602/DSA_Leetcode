
class Solution {
public:
    vector<int> answer;
    vector<vector<int>> adj, finalTree;
    vector<int> newParent;

    int last[26];

    void dfs1(int u, string &s) {

        int c = s[u] - 'a';

        int old = last[c];

        // Find closest ancestor with same character
        if (last[c] != -1) {
            newParent[u] = last[c];
        }

        last[c] = u;

        for (int v : adj[u]) {
            dfs1(v, s);
        }

        // Backtracking
        last[c] = old;
    }

    int dfs2(int u) {

        int size = 1;

        for (int v : finalTree[u]) {
            size += dfs2(v);
        }

        answer[u] = size;

        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {

        int n = parent.size();

        adj.resize(n);
        finalTree.resize(n);
        answer.resize(n);
        newParent = parent;

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        // Initialize last array
        fill(last, last + 26, -1);

        // Find new parents
        dfs1(0, s);

        // Build final tree
        for (int i = 1; i < n; i++) {
            finalTree[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        dfs2(0);

        return answer;
    }
};
