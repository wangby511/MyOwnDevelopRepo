//
//  main.cpp
//  20190920Tencent
//
//  Created by 王博远 on 2019/9/19.
//  Copyright © 2019年 王博远. All rights reserved.
//
//
//作者：++offer&&offer++
//链接：https://www.nowcoder.com/discuss/271458?type=all&order=time&pos=&page=1
//来源：牛客网

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <set>
#include <queue>
#include <climits>
#include <unordered_set>
#include <map>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <initializer_list>
#include <typeinfo>
#include <map>
#include <iomanip>
using namespace std;
typedef long long LL;
const int M = 1e9+7;
#define _for(i,l,r) for(LL i=(l);i<(r);i++)
int dir[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
vector<LL> data;

long find_minn(vector<long> u){
    long res = -1e9;
    for(auto x:u){
        if(x > res)res = x;
    }
    return res;
}
int main1(){
    int n1,n2;cin>>n1>>n2;
    int maxx1 = -1e9,maxx1_2 = -1e9;
    int minn1 = 1e9,minn1_2 = 1e9;
    for(int i = 0;i < n1;i++){
        int t;cin>>t;
        if(t > maxx1){
            maxx1_2 = maxx1;
            maxx1 = t;
        }else if(t > maxx1_2){
            maxx1_2 = t;
        }
        if(t < minn1){
            minn1_2 = minn1;
            minn1 = t;
        }else if(t < minn1_2){
            minn1_2 = t;
        }
    }
    int maxx2 = -1e9,minn2 = 1e9;
    for(int i = 0;i < n2;i++){
        int t;cin>>t;
        if(t > maxx2){
            maxx2 = t;
        }
        if(t < minn2){
            minn2 = t;
        }
    }
    vector<long> u1 = {maxx1_2 * maxx2, minn1_2 * minn2 , maxx1_2 * minn2, maxx1 * maxx2};
    long u = find_minn(u1);
    cout<<u<<endl;
    return 0;
}
int main2(){
    int n;cin>>n;
    int res = 0;
    vector<int> arr(n,0);
    for(int i = 0;i < n;i++){
        cin>>arr[i];
        arr[i] = abs(arr[i]);
    }
    sort(arr.begin(),arr.end());
    for(int i = 0;i < n;i++){
        int left = 0,right = i - 1;
        while(left < right){
            int mid = left+ (right - left)/2;
            
            if(arr[mid] * 1.0 < 0.5 * arr[i])left = mid + 1;
            else right = mid;
        }
        res += max(abs(i - 1 - left + 1),0);
    }
    cout<<res<<endl;
    return 0;
}
int main3(){
    int n,k;cin>>n>>k;
    vector<pair<int,int>> arr;
    priority_queue<int,vector<int>,greater<int>> qu;
    for(int i = 0;i < n;i++){
        int t1,t2;
        cin>>t1>>t2;
        arr.push_back({t1,t2});
    }
    sort(arr.begin(),arr.end(),[](pair<int,int> &a, pair<int,int> &b){
        return a.second < b.second;
    });
    long long sum = 0;
    for(int j = n - 1; j >= n - k;j--){
        qu.push(arr[j].first);
        sum += arr[j].first;
    }
    long long maxx = sum * arr[n - k].second;
    for(int j = n - k - 1;j >= 0;j--){
        int x = qu.top();
        qu.pop();
        qu.push(arr[j].first);
        sum += arr[j].first - x;
        long long u = sum * arr[j].second;
        if(u > maxx)maxx = u;
    }
    cout<<maxx<<endl;
    return 0;
}
int main4(){
    int N;cin>>N;
    for(int i = 0;i < N;i++){
        int k;cin>>k;
        string a,b;cin>>a>>b;
        char op;cin>>op;
    }
    return 0;
}
struct TrieNode {
    TrieNode* child[26];
    bool isWord;
    string word;
    TrieNode(){
        isWord = false;
        for(int i = 0;i < 26;i++)child[i] = NULL;
    }
};
void insert(string word,TrieNode* root) {
    TrieNode* p = root;
    for(char c:word){
        int i = c - 'a';
        if(!p->child[i]){
            p->child[i] = new TrieNode();
        }
        p = p->child[i];
    }
    p -> isWord = true;
    p -> word = word;
}
void dfs(TrieNode* p, string banned, string &ans){
    if(!p || ans != "")return;
    if(p->isWord){
        int banned_len = banned.size();
        int word_len = p->word.size();
        if(banned_len <= word_len && p->word.substr(0, banned_len) == banned){
            return;
        }
        ans = p->word;
    }
    for(int i = 0;i < 26;i++){
        dfs(p->child[i], banned, ans);
    }
}
string query(TrieNode* root, string prefix, string suffix) {
    TrieNode* p = root;
    for(char c:prefix){
        int i = c - 'a';
        if(!p->child[i])return "-1";
        else p = p->child[i];
    }
    string ans = "";
    dfs(p, suffix, ans);
    return (ans == "")?"-1":ans;
}
int main5(){
    TrieNode* root = new TrieNode();
    int n,k;
    cin>>n>>k;
    for(int i = 0;i < n;i++){
        string x;cin>>x;
        insert(x, root);
    }
    for(int i = 0;i < k;i++){
        string q1,q2;
        cin>>q1>>q2;
        cout<< query(root, q1, q2) << endl;
    }
    return 0;
}
int main() {
    // insert code here...
//    main5();
    cout << "Hello, World! END\n";
//    cout<<fixed<<setprecision(5)<<dp[n][m]<<endl;
    return 0;
}
//5 4
//aaab
//aab
//aa
//aabb
//a
//a c
//aa aab
//aaa aaab
//a aaa
