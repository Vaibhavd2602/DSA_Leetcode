class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> gain(n,1);

        for(int i = 0; i < n; i++){
            int f = items[i][0];
            for(int j = 0; j < n; j++){
                if(i !=j && items[j][0] % f==0){
                    gain[i]++;
                }
            }
        }
         vector<int> dp(budget+1,0);
        for(int i = 0 ; i < n; i++){
            int cost = items[i][1];
            for(int b = budget; b >=cost; b--){
                 dp[b] = max(dp[b] , dp[b - cost] + gain[i]);
            }
        }
        for(int i = 0; i < n; i++ ){
            int cost = items[i][1];
            for(int b = cost ; b <= budget; b++){
                dp[b] = max(dp[b] , dp[b - cost] +1 );
            }
        }
        return *max_element(dp.begin(),dp.end());
    }
};