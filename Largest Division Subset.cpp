//
//  Largest Division Subset.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/21/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Largest Division Subset
///@author  Wei Zhao
///@date    2016.09.21
///@version 1.0

/*
 Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.
 
 If there are multiple solutions, return any subset is fine.
 
 Example 1:
 
 nums: [1,2,3]
 
 Result: [1,2] (of course, [1,3] will also be ok)
 Example 2:
 
 nums: [1,2,4,8]
 
 Result: [1,2,4,8]
 */

#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Solution {
public:
    ///@brief   calculate the largest mutual divisible subset
    ///@param   nums    array of integers
    ///@return  the largest mutual divisible subset
    ///@note    1. dynamic programming
    //          2. if T[n] is the length of the largest divisible subset and a[n] is the largest number, so the recurrence is
    //             T[n+1] = a[n+1] % a[i] == 0, 0 <= i <= n ? 1 + T[i] : 1
    //          3. use another array "parent" to store the elements' index of largest divisible subset
    //          4. https://discuss.leetcode.com/topic/49456/c-solution-with-explanations/2
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<int> parents(nums.size(), 0);    // the largest divisible subset's index in the nums
        vector<int> T(nums.size(), 0);  //  the length of the largest divisible subset
        
        int max_len = 0;    //  the max len
        int max_len_indx = 0;   //  the index of largest element in the largest divisible subset
        
        sort(nums.begin(), nums.end());
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i; j >= 0; j--) {
                if (nums[i] % nums[j] == 0 && T[i] < T[j] + 1) {
                    T[i] = T[j] + 1;    //  update the length of the largest divisible subset
                    parents[i] = j;     //  update the parents of the current element
                    if (T[i] > max_len) {   //  update the max_len and max_len_index
                        max_len = T[i];
                        max_len_indx = i;
                    }
                }
            }
        }
        
        vector<int> rslt;
        for (int i = 0; i < max_len; i++) {
            rslt.push_back(nums[max_len_indx]);
            max_len_indx = parents[max_len_indx];
        }
        reverse(rslt.begin(), rslt.end());  //  because we find the element increasingly, so we should reverse it from end to head.
        return rslt;
    }
};

int main() {
    Solution slt;
    vector<int> nums = {1, 2, 4, 8};
    vector<int> rslt = slt.largestDivisibleSubset(nums);
    reverse(nums.begin(), nums.end());
    return 0;
}









































