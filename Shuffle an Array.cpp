//
//  Shuffle an Array.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/22/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Shuffle an Array
///@author  Wei Zhao
///@date    2016.09.22
///@version 1.0

/*
 Shuffle a set of numbers without duplicates.
 
 Example:
 
 // Init an array with set 1, 2, and 3.
 int[] nums = {1,2,3};
 Solution solution = new Solution(nums);
 
 // Shuffle the array [1,2,3] and return its result. Any permutation of [1,2,3] must equally likely to be returned.
 solution.shuffle();
 
 // Resets the array back to its original configuration [1,2,3].
 solution.reset();
 
 // Returns the random shuffling of array [1,2,3].
 solution.shuffle();
 */

#include <vector>
#include <cstdlib>

using namespace std;



///@note    1. random function
///         2. use extra memory to store the original vector for reset
class Solution {
private:
    vector<int> orig_nums;
public:
    Solution(vector<int> nums) {
        orig_nums = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return orig_nums;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> shf_nums;
        vector<int> nums = orig_nums;
    
        while (!nums.empty()) {
            int i = rand() % (int)nums.size();
            shf_nums.push_back(nums[i]);
            nums.erase(find(nums.begin(), nums.end(), nums[i]));
        }
        return shf_nums;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */

int main() {
    vector<int> nums = {1, 2, 3, 4};
    Solution slt(nums);
    vector<int> shuffle_nums = slt.shuffle();
    vector<int> original_nums = slt.reset();
    
}
