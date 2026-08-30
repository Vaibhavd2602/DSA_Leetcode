class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find positions of minimum and maximum
        for (int i = 0; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // min and max ko left-right order mein rakho
        int left = min(minIndex, maxIndex);
        int right = max(minIndex, maxIndex);

        // 1. Dono ko left se remove karo
        int option1 = right + 1;

        // 2. Dono ko right se remove karo
        int option2 = n - left;

        // 3. Left se ek aur right se ek
        int option3 = (left + 1) + (n - right);

        return min({option1, option2, option3});
    }
};