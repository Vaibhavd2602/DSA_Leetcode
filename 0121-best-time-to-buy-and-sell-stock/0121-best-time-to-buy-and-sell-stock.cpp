class Solution {
public:
    int maxProfit(vector<int>& prices) {
       int maxProfit = 0;
       int profit = prices[0];
       for (int i = 1 ; i < prices.size() ; i++){
            int current = prices[i] - profit;
            if(current  < 0 ){
               profit = prices[i];
            }
            maxProfit = max(current , maxProfit);
       }
       return maxProfit;
    }
};