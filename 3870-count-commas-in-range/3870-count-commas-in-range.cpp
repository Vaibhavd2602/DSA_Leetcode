class Solution {
public:
    int countCommas(int n) {
        int ans = 0;
        if(n < 1000){
            return ans;
        }
       for(int i = 1000 ; i <= n; i++ ){
               ans = ans + 1;
       }
       return ans;        
    }
};