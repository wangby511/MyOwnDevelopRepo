//
//  main.cpp
//  20190921ByteDance
//
//  Created by 王博远 on 2019/9/21.
//  Copyright © 2019年 王博远. All rights reserved.
//
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
int main1(){
    int n;cin>>n;
    vector<char> arr(n,0);
    for(int i = 0;i < n;i++)cin>>arr[i];
    vector<int> dist(n,M);
    int prev = -M;
    for(int i = 0;i < n;i++){
        if(arr[i] == 'O'){
            prev = i;
            dist[i] = 0;
        }
        else dist[i] = min(dist[i],i - prev);
    }
    prev = M;
    for(int i = n - 1;i >= 0;i--){
        if(arr[i] == 'O')prev = i;
        else dist[i] = min(dist[i],abs(i - prev));
    }
    for(int x:dist)cout<<x<<" ";cout<<endl;
    
    return 0;
}
int main2(){
    int N;cin>>N;
    for(int i = 0;i < N;i++){
        int n,m,sum = 0;cin>>n>>m;
        vector<int> arr(n,0),res(n,0);
        for(int i = 0;i < n;i++)cin>>arr[i];
        priority_queue<int> pq;
        for(int i = 0;i < n;i++){
            if(m - sum < arr[i]){
                int temp = sum;
                vector<int> poped;
                while(!pq.empty() && m - arr[i] < temp){
                    int x = pq.top();
                    temp -= x;
                    poped.push_back(x);
                    pq.pop();
                }
                res[i] = poped.size();
                for(int x:poped)pq.push(x);
            }
            sum += arr[i];
            pq.push(arr[i]);
        }
        for(int x:res)cout<<x<<" ";cout<<endl;
    }
    return 0;
}
vector<int> glres;
void dfs(int i,vector<int>& degree,map<int,vector<int>>& topo,vector<int> &visited){
    visited[i] = 1;
    glres.push_back(i);
    for(int x:topo[i]){
        if(--degree[x] == 0 && visited[x] == 0){
            dfs(x,degree,topo,visited);
        }
    }
}
int main3(){
    map<int,vector<int>> topo;
    string t;
    int n = 0;
    while(getline(cin,t)){
        if(!t.size())break;
        char person = t[0];
        int p = person - '0';
        n = max(n,p);
        for(int i = 2;i < t.size();i += 2){
            topo[t[i] - '0'].push_back(p);
        }
    }
    vector<int> degree(n + 1,0);
    for(auto &it:topo){
        sort(it.second.begin(),it.second.end());
        for(int x:it.second)degree[x]++;
    }
    queue<int> qu;
    vector<int> visited(n + 1,0);
    for(int i = 1;i <= n;i++){
        if(degree[i] == 0 && visited[i] == 0){
            dfs(i,degree,topo,visited);
        }
    }
    bool all = true;
    for(int i = 1;all && i <= n;i++){
        if(visited[i] == 0)all = false;
    }
    if(!all)cout<<"-1"<<endl;
    else {
        for(int i = 0;i < glres.size();i++){
            cout<<glres[i];
            if(i != glres.size() - 1)cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}
int main4(){
    int a,b;
//    cin>>a>>b;
    a = 2;b = 4;
    LL res = 1;
    map<LL,int> len;
    len[a + b]++;
    for(LL m = 1;m <= a;m++){
        LL k = a / m;
        for(LL n = 1;n <= b;n++){
            if(len.count(m + n) != 0)continue;
            LL left = b - k * n;
            if(left >= 0 && left <= n){
                cout<<m + n<<","<<m<<","<<n<<endl;
                len[m + n]++;
                res++;
            }
        }
        
    }
//    for(LL len = 1;len < a + b;len++){
//        bool thislen = false;
//        for(LL m = 1;!thislen && len - m > 0;m++){
//            LL n = len - m;
//            LL k = a / m;
//            LL left = b - k * n;
//            if(left <= n && left >= 0){
//                cout<<len<<","<<m<<","<<n<<endl;
//                thislen = true;
//                res++;
//            }
//        }
//    }
    cout<<res<<endl;
    return 0;
}
int main5(){
    LL a,b;
    cin>>a>>b;
    LL res = 1;
    for(LL len = 1;len < a + b;len++){
        bool thislen = false;
        for(LL m = 1;!thislen && len - m > 0;m++){
            LL n = len - m;
            LL k = a / m;
            LL left = b - k * n;
            if(left >= 0 && left <= n){
                thislen = true;
                res++;
            }
        }
    }
    cout<<res<<endl;
    return 0;
}
int main() {
    // insert code here...
    main4();
    cout << "Hello, World!\n";
    return 0;
}
