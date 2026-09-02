class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int odd = 0;
        int even = 0;
        for(int x : nums1){
            if(x % 2 == 0){
                even++;
            }
            else {
                odd++;
            }
        }
        if(even == 0 || odd == 0){
            return true;
        }
        return true;
    }
};