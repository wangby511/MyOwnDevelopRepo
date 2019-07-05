//
//  main.cpp
//  20190704
//
//  Created by 王博远 on 2019/7/4.
//  Copyright © 2019年 王博远. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

void perlocateDown(vector<int> &arr, int n,int i){
    while(true){
        int largerChild = i;
        if(2 * i + 1 < n && arr[2 * i + 1] > arr[i])largerChild = 2 * i + 1;
        if(2 * i + 2 < n && arr[2 * i + 2] > arr[largerChild])largerChild = 2 * i + 2;
        if(largerChild == i)break;
        swap(arr[i],arr[largerChild]);
        i = largerChild;
    }
}

void buildHeap(vector<int> &arr, int n) {
    for(int i = n/2;i >= 0;i--){
        perlocateDown(arr, n, i);
    }
}

void heapSort(vector<int> &arr, int n) {
    buildHeap(arr, n);
    int k = n;
    while (k > 1) {
        swap(arr[0],arr[k - 1]);
        --k;
        perlocateDown(arr, k, 0);
    }
}

// use : heapSort(arr, arr.size());
// int test() {
//     vector<int> arr,arr2;
//     srand(time(0));
//     for(int i = 0; i < 100;i++){
//         int x = rand() % 1000;
//         arr.push_back(x);
//         arr2.push_back(x);
//         cout<<x<<" ";
//     }
//     cout<<endl;
//     heapSort(arr, arr.size());
    
//     sort(arr2.begin(),arr2.end());
//     for(int i = 0; i < 100;i++){
//         if(arr[i] != arr2[i]){
//             cout<<"FALSE!"<<endl;
//             return 0;
//         }
//     }
//     cout<<"TRUE"<<endl;
//     return 0;
// }
    
// int main(){
//     test();
//     return 0;
// }
