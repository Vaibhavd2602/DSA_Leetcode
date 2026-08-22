class Solution {
public:
    bool checkDivisibility(int n) {
        int ans = 0;
        int sum = 0;
        int original = n;
        int product = 1;
        while(n !=0){
        int digit = n % 10;
          sum += digit;
          product *= digit;

          n = n / 10;
        }
        ans = sum + product;
        return  original % ans == 0;
    }
};