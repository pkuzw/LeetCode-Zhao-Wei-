//
//  Combination Sum IV.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/21/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Combination Sum IV
///@author  Wei Zhao
///@date    2016.09.21
///@version 1.0

#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

/*
 Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.
 
 Example:
 
 nums = [1, 2, 3]
 target = 4
 
 The possible combination ways are:
 (1, 1, 1, 1)
 (1, 1, 2)
 (1, 2, 1)
 (1, 3)
 (2, 1, 1)
 (2, 2)
 (3, 1)
 
 Note that different sequences are counted as different combinations.
 
 Therefore the output is 7.
*/

class Solution_tle {
public:
    ///@brief   calculate all the combinations which sum is equal to the target
    ///@param   nums    candidates array
    ///@param   target  sum of the combination is equal to it
    ///@return  the number of these combinations
    ///@note    1. recurrence
    //          2. Time limit eceeded.
    int combinationSum4(vector<int>& nums, int target) {
        if (!target)    return 1;
        int rslt = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (target - nums[i] >= 0)
                rslt += combinationSum4(nums, target - nums[i]);
        }
        return rslt;
    }
};

class Solution {
private:
    vector<int> dp; //  store the number of combinations which sum's equal to target
public:
    ///@note   1. dynamic programming
    //         2. use an array to store the intermediate values have been calculated
    //         3. https://discuss.leetcode.com/topic/52302/1ms-java-dp-solution-with-detailed-explanation/2
    int combinationSum4(vector<int>& nums, int target) {
        for (int i = 0; i <= target; i++)   dp.push_back(-1);
        dp[0] = 1;
        return helper(nums, target);
    }
    
    ///@brief   reccursive function
    ///@param   nums    array of integers
    ///@param   target  sum of array elements
    ///@return  the number of combinations
    int helper(vector<int>& nums, int target) {
        if (dp[target] != -1)   return dp[target];
        int rslt = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (target - nums[i] >= 0) {
                rslt += helper(nums, target - nums[i]);
            }
        }
        dp[target] = rslt;
        return rslt;
    }
};

class Solution_bottom_up {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> comb_count(target + 1, 0);
        comb_count[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int j = 0; j < nums.size(); j++) {
                if (i - nums[j] >= 0) {
                    comb_count[i] += comb_count[i - nums[j]];
                }
            }
        }
        return comb_count[target];
    }
};

int main() {
    vector<int> nums = {3, 2, 1};
    Solution slt;
    int target = 4;
    int rslt = slt.combinationSum4(nums, target);
    
    Solution_bottom_up sbu;
    int r = sbu.combinationSum4(nums, target);
    return 0;
}








































