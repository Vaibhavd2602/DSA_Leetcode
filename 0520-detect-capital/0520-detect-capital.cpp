class Solution {
public:
    bool detectCapitalUse(string word) {
       int uppercase = 0;

        for (char character : word) {
            if (isupper(character)) {
                uppercase++;
            }
        }

        return uppercase == word.length() ||
               uppercase == 0 ||
               (uppercase == 1 && isupper(word[0]));
    }
};