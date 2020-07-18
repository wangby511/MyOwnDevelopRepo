//
//  main.cpp
//  20191019Yelp
//
//  Created by 王博远 on 2019/10/19.
//  Copyright © 2019年 王博远. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
using namespace std;

// 2019 10 19 YELP NEW GRAD OA
// https://www.1point3acres.com/bbs/thread-549789-1-1.html
int YELP_OA1() {
    // active business id
    map<int,map<string,int>> event;
    event[3]["ads"] = 7;
    event[2]["ads"] = 8;
    event[1]["ads"] = 5;
    event[2]["page_views"] = 11;
    event[3]["page_views"] = 12;
    event[3]["photo_views"] = 10;
    event[2]["reviews"] = 7;
    map<string,int> cnt;
    map<string,double> avg;
    avg["ads"] += 7;cnt["ads"]++;
    avg["ads"] += 8;cnt["ads"]++;
    avg["ads"] += 5;cnt["ads"]++;
    avg["page_views"] += 11;cnt["page_views"]++;
    avg["page_views"] += 12;cnt["page_views"]++;
    avg["photo_views"] += 10;cnt["photo_views"]++;
    avg["reviews"] += 7;cnt["reviews"]++;
    for(auto& it:avg){
        it.second = it.second / cnt[it.first];
    }
//    for(auto it:avg){
//        cout<<it.first<<":"<<it.second<<endl;
//    }
    vector<int> res;
    for(auto it:event){
        int satisfy = 0;
        for(auto itt:it.second){
            string type = itt.first;
            if(itt.second >= avg[type]){
                satisfy++;
            }
        }
        if(satisfy >= 2){
            res.push_back(it.first);
        }
    }
//    for(int x:res)cout<<x<<" ";cout<<endl;
    return 0;
}

vector<int> computeLPSArray(string pat){
    int len = 0;
    vector<int> lps(pat.size(), 0);
    
    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        }else{
            if (len != 0) {
                len = lps[len - 1];
            }else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

//https://byshen.github.io/2018/08/18/kmp/
vector<int> computeLPSArray2(string s){
    int j = 0;
    vector<int> next(s.size(), 0);
    
    for (int i = 1; i < s.size(); ++i) {
        while (j > 0 && s[i] != s[j]) j = next[j - 1];
        if (s[i] == s[j]) { j++; }
        next[i] = j;
    }
    return next;
}

void KMPSearch(string pat, string txt){
    int pat_len = pat.size();
    int txt_len = txt.size();

    vector<int> next = computeLPSArray2(pat);
    
    cout<<"next arr:"<<endl;
    for(int x:next)cout<<x<<" ";cout<<endl;
    
    
    cout<<"KMPSearch Part: "<<endl;
    int i = 0,j = 0;
    while (i < txt_len) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        
        if (j == pat_len) {
            cout<<"Found pattern at index "<<i - j<<endl;
            j = next[j - 1];
        }
        
        else if (i < txt_len && pat[j] != txt[i]) {
            
            if (j != 0)
                j = next[j - 1];
            else
                i = i + 1;
        }
    }
}

int main() {
//    KMPSearch("AAAA", "AAAAABAAAABA");
//    KMPSearch("ABABCABAB", "ABABDABACDABABCABAB");
    KMPSearch("ABABCABAB", "ABABCABABCABAB");
    return 0;
}
