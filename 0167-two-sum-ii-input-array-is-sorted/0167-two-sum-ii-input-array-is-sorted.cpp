class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        vector<int> index;

        while(left < right){
            int sum = numbers[left] + numbers[right];
            if(sum == target){
                index.push_back(left + 1);  // Leetcode Two Sum II expects 1-based index
                index.push_back(right + 1);
                return index;
            }
            else if(sum < target){
                left++;   // sum chhota hai → left bada karo
            }
            else{
                right--;  // sum bada hai → right chhota karo
            }
        }

        return index;  // agar solution na mile
    }
};
