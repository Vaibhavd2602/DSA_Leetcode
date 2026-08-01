class Solution {
public:
    int calculate(string s) {
        long res = 0;         // current result
        long num = 0;         // current number being built
        int sign = 1;         // current sign: 1 or -1
        stack<int> st;        // stack stores previous res and sign (pushed as res, then sign)

        for (int i = 0; i < (int)s.size(); ++i) {
            char c = s[i];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else {
                if (c == '+') {
                    res += sign * num;
                    num = 0;
                    sign = 1;
                } else if (c == '-') {
                    res += sign * num;
                    num = 0;
                    sign = -1;
                } else if (c == '(') {
                    // push current context, then reset for inside parentheses
                    st.push((int)res);
                    st.push(sign);
                    res = 0;
                    sign = 1;
                    num = 0;
                } else if (c == ')') {
                    res += sign * num;
                    num = 0;
                    int prevSign = st.top(); st.pop();
                    int prevRes  = st.top(); st.pop();
                    res = prevRes + prevSign * res;
                } // skip spaces automatically
            }
        }
        res += sign * num; // add last number
        return (int)res;
    }
};
