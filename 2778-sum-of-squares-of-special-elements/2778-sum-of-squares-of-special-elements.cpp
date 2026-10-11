class Solution {
public:
    int sumOfSquares(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int i = 1;
        
        while(i <= n){
           if( n % i ==0){
            ans += nums[i-1] * nums[i-1];
            i++;
           }
           else{
            i++;
           }
        }
        return ans;
    }
};