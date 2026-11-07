
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        // {weight, server_index}
        priority_queue<pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>> available;

        // {free_time, weight, server_index}
        priority_queue<tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>> busy;

        int n = servers.size();
        int m = tasks.size();

        vector<int> ans(m);

        for(int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        long long currentTime = 0;

        for(int i = 0; i < m; i++) {

            currentTime = max(currentTime, (long long)i);

            // Release all servers that have completed their tasks
            while(!busy.empty() &&
                  get<0>(busy.top()) <= currentTime) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, jump to the earliest free time
            if(available.empty()) {

                currentTime = get<0>(busy.top());

                // Release all servers becoming free at this time
                while(!busy.empty() &&
                      get<0>(busy.top()) <= currentTime) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Select server with minimum weight and index
            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;

            // Assign task and calculate its completion time
            busy.push({
                currentTime + tasks[i],
                weight,
                index
            });
        }

        return ans;
    }
};
