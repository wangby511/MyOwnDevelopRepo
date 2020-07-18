//
//  main.cpp
//  20180402
//
//  Created by 王博远 on 2018/4/2.
//  Copyright © 2018年 王博远. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;
int wangyiyouxi1(){
    int w[26];
    for(int i = 0;i < 26;i++){
        cin>>w[i];
    }
    string str;cin>>str;
    int ans = 0,res = 0;
    for(int i = 0;i < str.size();i++){
        ans += w[str[i] - 'a'];
        if(ans > 100){
            res++;
            ans = w[str[i] - 'a'];
        }
    }
    cout<<res + 1<<" "<<ans<<endl;
    return 0;
}
//5 5 5 5 5 5 5 5 5
int wangyigame2(){
    map<int,int> cnt;
    int t;
    while(cin >> t){
        cnt[t]++;
        //cout<<cnt[t]<<endl;
    }
    int res = 0;
    vector<int> ans(cnt.size() + 1,0);
    int k = 1;
    int prev = -1;
    for(auto iter = cnt.begin();iter!= cnt.end();iter++,k++){
        int temp = iter->second * iter->first;
        //cout<<temp<<endl;
        if(k == 1){
            ans[k] = temp;
        } else {
            int c = (prev + 1 == iter->first)?0:temp;
            ans[k] = max(ans[k - 2] + temp, ans[k - 1] + c);
        }
        prev = iter->first;
    }
    return ans[cnt.size()];
}

int yangyiyouxi3(){
    map<int,int> cnt;
    int t;
    int res = 0;
    int n;cin>>n;
    while(n--){
        cin >> t;
        //diff.push_back(t);
        cnt[t]++;
    }
    for(auto iter = cnt.begin();iter!= cnt.end();iter++){
        int a = iter->first,b = iter->second;
        while(b > 0){
            b -= (a + 1);
            res += (a + 1);
        }
    }
    cout<<res<<endl;
    return 0;
}
int safe = 0;
void dfs(map<pair<int,int>,int>& grid,int i,int j,int m,int n){
    if(i < 0 || i >= m)return;
    if(j < 0 || j >= n)return;
    
    if(grid[make_pair(i, j)] == 0 || grid[make_pair(i, j)] == 2)return;
    if(grid[make_pair(i, j)] == 1){
        safe++;
        grid[make_pair(i, j)] = 2;
    }
    dfs(grid,i + 1,j,m,n);
    dfs(grid,i - 1,j,m,n);
    dfs(grid,i,j + 1,m,n);
    dfs(grid,i,j - 1,m,n);
}

int wangyiyouxi4(){
    int n,m,a,b,cnt = 0;
    cin>>n>>m>>a>>b;
    map<pair<int,int>,int> grid;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            int c;cin>>c;
            if(c == 1){
                grid[make_pair(i, j)] = 1;
                cnt++;
            }
        }
    }
    if(grid[make_pair(a, b)] == 0){
        cout<<0<<endl;
        return 0;
    }
    grid[make_pair(a, b)] = 0;
    
    for(int i = 0;i < m;i++){
        if(grid[make_pair(0, i)] != 0)dfs(grid,0,i,m,n);
    }
    cout<<cnt - safe - 1<<endl;
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
void quickSort(int a[], int left, int right){
    if(left > right)return;
    int i = left,j = right,temp = a[left];

    while (i != j){
        while(i < j && a[j]>= temp)j--;
        while(i < j && a[i]<= temp)i++; // 从左向右找第一个大于等于x的数
        
        if(i < j){
            int x = a[i];a[i] = a[j];a[j] = x;
        }
    }
    a[left] = a[i];
    a[i] = temp;
    quickSort(a, left, i - 1);
    quickSort(a, i + 1, right);
}
int main(){
//    uint64_t size=1024*1024*1024*1024L;
//    char* a = new char(size);
//    char c = 'f';
//    *(a+1)='a';
//    cout<<sizeof(a)<<endl;
//    cout<<sizeof(c)<<endl;
//    cout<<sizeof(size)<<endl;
//    cout<<size<<endl;
    int a[] = {4,7,1,9,0,3,2,8,6,5};
    quickSort(a, 0, 9);
    for(int i = 0;i < 10;i++){
        cout << a[i] <<" ";
    }
    cout<<endl;
    unordered_map<int,int> umap;
    umap[1] = 3;
    umap[2] = 4;
    umap[3] = 6;
    cout<<sizeof(umap)<<endl;
}
    

