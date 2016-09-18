//
//  Wiggle Subsequence.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/17/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Wiggle Subsequence
///@author  Wei Zhao
///@date    2016.09.17
///@version 1.0

/*
 A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.
 
 For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.
 
 Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.
 
 Examples:
 Input: [1,7,4,9,2,5]
 Output: 6
 The entire sequence is a wiggle sequence.
 
 Input: [1,17,5,10,13,15,10,5,16,8]
 Output: 7
 There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].
 
 Input: [1,2,3,4,5,6,7,8,9]
 Output: 2
 Follow up:
 Can you do it in O(n) time?
 */

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    ///@brief   get the longest wiggle subsequence length of an integer array
    ///@param   nums    array
    ///@return  the longest length
    ///@note    https://discuss.leetcode.com/topic/51946/very-simple-java-solution-with-detail-explanation
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2)    return nums.size();
        int k = 0;
        int rslt = 2;
        while (k < nums.size() - 1 && nums[k] == nums[k+1]) {
            k++;
        }
        if (k == nums.size() - 1)   return 1;
        
        bool increase = nums[k+1] > nums[k];
        for (int i = k + 1; i < nums.size() - 1; i++) {
            if (increase && nums[i+1] < nums[i]) {
                increase = !increase;
                nums[rslt] = nums[i+1];
                rslt++;
            }
            else if (!increase && nums[i+1] > nums[i]){
                increase = !increase;
                nums[rslt] = nums[i+1];
                rslt++;
            }
        }
        return rslt;
    }
};

int main() {
    vector<int> nums;
    int n[6] = {1,7,4,9,2,5};
    for (int i = 0; i != 6; i++) {
        nums.push_back(n[i]);
    }
    Solution slt;
    int rslt = slt.wiggleMaxLength(nums);
    
    return 0;
}
