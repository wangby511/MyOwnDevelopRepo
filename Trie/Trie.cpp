//
//  main.cpp
//  20191018Trie
//
//  Created by 王博远 on 2019/10/18.
//  Copyright © 2019年 王博远. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <map>
#include <unordered_map>
using namespace std;

struct FileNode {
    map<string,FileNode*> subfolder;
    bool isEnd;
    string name;
    FileNode(string s){
        name = s;
        isEnd = false;
        subfolder.clear();
    }
};

struct TrieNode {
    TrieNode* child[26];
    int count;
    bool isWord;
    string word;
    TrieNode(){
        count = 0;
        isWord = false;
        for(int i = 0;i < 26;i++)child[i] = NULL;
    }
};
void getAllWordsHelper(TrieNode* root,vector<string>& res){
    if(!root)return;
    if(root->isWord){
        res.push_back(root->word);
    }
    for(int i = 0;i < 26;i++){
        getAllWordsHelper(root->child[i],res);
    }
}
vector<string> getAllWords(TrieNode* root){
    vector<string> res;
    getAllWordsHelper(root,res);
    return res;
}
string getRandomWord(TrieNode* root){
    if(!root)return "";
    int total = root->count;
    int cnt = 0;
    int index = 0;
    if( root->isWord == true && root->count == 1)return root->word;
    index = rand() % root->count;
    if( root->isWord == true && index + 1 == root->count)return root->word;
    
    TrieNode* next = NULL;
    for(int i = 0;i < 26;i++){
        if(!root->child[i])continue;
        cnt += root->child[i]->count;
        if(cnt > index){
            char x = 'a' + i;
            next = root->child[i];
            break;
        }
    }
    if(!next)return "";
    return getRandomWord(next);
}
void insertWord(TrieNode* root,string word){
    TrieNode* p = root;
    for(int i = 0;i < word.size();i++){
        int x = word[i] - 'a';
        if(p->child[x] == NULL){
            p->child[x] = new TrieNode();
        }
        p->count++;
        p = p->child[x];
    }
    p->count++;
    p->word = word;
    p->isWord = true;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    TrieNode* root = new TrieNode();
    srand(time(NULL));
    vector<string> words = {
        "cast",
        "basic",
        "art",
        "apple",
        "dashing",
        "daring",
        "doll",
        "dying",
        "care",
        "case",
        "aedyzlaxx",
        "aedyzlaxy",
        "aedyzlaxyz",
        "aedyzlaxt",
        "aedyz",
        "aed",
        "a",
//        "apple",
//        "app"
    };
    for(string s:words)insertWord(root, s);

//    vector<string> ans = getAllWords(root);
//    for(string s:ans)cout<<s<<endl;
//    cout<<root->count<<endl;
    int averageTimes = 10000;
    unordered_map<string,int> select;
    int n = words.size() * averageTimes;
    for(int i = 0;i < n;i++){
        select[getRandomWord(root)]++;
    }
    cout<<"Test for GeRrandom():"<<endl;
    for(auto it:select){
        cout<<it.first<<":"<<it.second<<endl;
    }
    return 0;
}
