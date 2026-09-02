class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int maxprofit = 0;
        int i = 0;
        for(int j = 1 ; j < n ; j++ ){
            int curr = prices[j] - prices[i];
            if(curr < 0){
                i++;
            }
            else{
            maxprofit += curr;
            i++;
            }
        }
        return maxprofit;        
    }
};