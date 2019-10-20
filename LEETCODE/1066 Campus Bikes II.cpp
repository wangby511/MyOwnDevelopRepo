class Solution {
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int nw = workers.size(),nb = bikes.size();
        int res = INT_MAX;
        // int dp[1 << nb][1 + nw];
        // memset(dp,0,sizeof(dp));
        vector<vector<int>> dp(1 << nb,vector<int> (1 + nw,1e7));
        dp[0][0] = 0;
        for(int s = 1;s < (1 << nb);s++){
            for(int i = 1;i <= nw;i++){
                for(int j = 0;j < nb;j++){
                    if(((s & (1 << j)) == 0))continue;
                    int prev = (~(1 << j)) & s;
                    int x = abs(workers[i - 1][0] - bikes[j][0]) + abs(workers[i - 1][1] - bikes[j][1]);
                    dp[s][i] = min(dp[s][i],dp[prev][i - 1] + x);
                }
            }
        }
        for(int s = 0;s < (1 << nb);s++){
            res = min(res,dp[s][nw]);
        }
        return res;
    }
// OCT 12 2019
//     [[0,0],  [1,0],  [2,0],  [3,0],  [4,0],  [5,0],  [6,0],  [7,0]]
//     [[0,999],[1,999],[2,999],[3,999],[4,999],[5,999],[6,999],[7,999],[8,999]]
};