
class ProductOfNumbers {
public:
    vector<int> prefix;

    ProductOfNumbers() {
        prefix.push_back(1);
    }

    void add(int num) {

        // Agar zero aaya toh reset
        if(num == 0) {
            prefix.clear();
            prefix.push_back(1);
        }
        else {
            int last = prefix.back();
            prefix.push_back(last * num);
        }
    }

    int getProduct(int k) {

        // Agar k current prefix size se bada hai
        // toh last k numbers mein zero present hai
        if(k >= prefix.size()) {
            return 0;
        }

        int n = prefix.size();

        return prefix[n - 1] / prefix[n - k - 1];
    }
};
