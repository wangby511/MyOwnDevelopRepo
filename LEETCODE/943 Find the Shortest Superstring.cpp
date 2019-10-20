class Solution {
public:
    int findsuffixprefix(string a,string b){
        int res = 0;
        for(int i = 1; i <= b.size() && i <= a.size();i++){
            if(b.substr(0,i) == a.substr(a.size() - i,i))res = max(res,i);
        }
        return res;
    }
    string shortestSuperstring(vector<string>& A) {
        map<pair<int,int>,int> common;
        int n = A.size();
        string total = "";
        for(int i = 0;i < n;i++){
            for(int h = 0;h < A[i].size();h++)total += "xx";
            for(int j = 0;j < n;j++){
                common[{i,j}] = findsuffixprefix(A[i],A[j]);
            }
        }
        string dp[1<<n][n];
        // memset(dp,0,sizeof(dp));
        for(int i = 0;i < (1<<n);i++){
            for(int j = 0;j < n;j++){
                dp[i][j] = total;
            }
        }
        for(int i = 0;i < n;i++){
            dp[1 << i][i] = A[i];
        }
        for(int i = 1;i < (1<<n);i++){
            for(int j = 0;j < n;j++){
                if((i & (1 << j)) == 0)continue;
                for(int k = 0;k < n;k++){
                    if(k == j || (i & (1 << k)) == 0)continue;
                    int prev = i & (~(1 << j));
                    if(dp[prev][k].size() + int(A[j].size()) - common[{k,j}] < dp[i][j].size()){
                        dp[i][j] = dp[prev][k] + A[j].substr(common[{k,j}],int(A[j].size()) - common[{k,j}]);
                    }
                }
                
            }
        }
        string res = total;
        for(int i = 0;i < n;i++){
            if(dp[(1 << n) - 1][i].size() < res.size())res = dp[(1 << n) - 1][i];
            //2019 10 12
        }
        return res;
    }
};