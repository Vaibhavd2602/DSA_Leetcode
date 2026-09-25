class Solution {
public:
    set<string> parse(string &s, int &i) {
        set<string> res;
        set<string> cur = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == '{') {
                i++;
                auto temp = parse(s, i);
                i++;
                set<string> next;

                for (auto &a : cur) {
                    for (auto &b : temp) {
                        next.insert(a + b);
                    }
                }
                cur = next;
            }
            else if (s[i] == ',') {
                res.insert(cur.begin(), cur.end());
                cur = {""};
                i++;
            }
            else {
                string ch(1, s[i]);
                set<string> next;

                for (auto &a : cur) {
                    next.insert(a + ch);
                }

                cur = next;
                i++;
            }
        }

        res.insert(cur.begin(), cur.end());
        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        auto ans = parse(expression, i);
        return vector<string>(ans.begin(), ans.end());
    }
};