//
//  NormalBinarySearch.cpp
//  20210717
//
//  Created by 王博远 on 2021/7/17.
//  Copyright © 2021年 王博远. All rights reserved.
//
#include <vector>
using namespace std;

/**
 Leetcode 34
 */

// Find the first index which satisfies nums[index] >= target
// It could also return index n, which n == nums.size()
int lower_bound(vector<int>& nums, int target) {
    int left = 0,right = (int)nums.size();
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < target)left = mid + 1;
        else right = mid;
    }
    return left;
}

int search_left(vector<int>& nums, int target) {
    int left = 0,right = (int)nums.size();
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < target)left = mid + 1;
        else right = mid;
    }
    return (left < nums.size() && nums[left] == target)?left:-1;
}

// Find the first index which satisfies nums[index] > target
// It could also return index n, which n == nums.size()
int upper_bound(vector<int>& nums, int target) {
    int left = 0,right = (int)nums.size();
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] <= target)left = mid + 1;
        else right = mid;
    }
    return left;
}

int search_right(vector<int>& nums, int target) {
    int left = 0,right = (int)nums.size();
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] <= target)left = mid + 1;
        else right = mid;
    }
    return (right - 1 >= 0 && nums[right - 1] == target)?right - 1:-1;
}

vector<int> searchRange(vector<int>& nums, int target) {
    // if(!nums.size()) return {-1,-1};
    return {search_left(nums, target), search_right(nums, target)};
}


