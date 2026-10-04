class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char ch : s) {
            if (ch == '(') {
                low++;
                high++;
            }
            else if (ch == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' as ')'
                high++;  // '*' as '('
            }

            if (high < 0)
                return false;

            low = max(0, low);
        }

        return low == 0;
    }
};