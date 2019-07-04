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

void quickSort(vector<int>& arr,int left,int right){
    int i,j,pivot;
    if(left >= right){
        return;
    }
    i = left;
    j = right;
    pivot = arr[left];
    while (i < j) {
        while (i < j && arr[j] >= pivot) j--;
        while (i < j && arr[i] <= pivot) i++;
        if(i < j){
            swap(arr[i], arr[j]);
            //not swap(arr[i++], arr[j--]);
        }
        
    }
    swap(arr[left],arr[i]);
    
    quickSort(arr, left, j - 1);
    quickSort(arr, j + 1, right);
}

void quickSort2(vector<int>& arr,int left,int right){
    int i,j,pivot;
    if(left >= right){
        return;
    }
    i = left;
    j = right;
    pivot = arr[left];
    while (i < j) {
        while (i < j && arr[j] > pivot) j--;
        if(i < j)arr[i++] = arr[j];
        while (i < j && arr[i] <= pivot) i++;
        if(i < j)arr[j--] = arr[i];
    }
    arr[j] = pivot;
    
    quickSort2(arr, left, j - 1);
    quickSort2(arr, j + 1, right);
}