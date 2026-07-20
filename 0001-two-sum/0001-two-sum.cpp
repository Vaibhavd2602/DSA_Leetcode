class Solution {
public:
  //Most Optimal Solution
    vector<int> twoSum(vector<int>& nums, int target) {
         map<int, int > mp;
         for(int i = 0 ; i < nums.size(); i++){
            int num = nums[i];
            int moreneeded = target - num;
            if(mp.find(moreneeded) != mp.end()){
                return {mp[moreneeded] , i};
            }mp[num] = i;
         }
         return {-1,-1};
    }   
};