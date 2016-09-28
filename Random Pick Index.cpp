//
//  Random Pick Index.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/26/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Random Pick Index
///@author  Wei Zhao
///@date    2016.09.26
///@version 1.0

/*
 Given an array of integers with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 
 Note:
 The array size can be very large. Solution that uses too much extra space will not pass the judge.
 
 Example:
 
 int[] nums = new int[] {1,2,3,3,3};
 Solution solution = new Solution(nums);
 
 // pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 solution.pick(3);
 
 // pick(1) should return 0. Since in the array only nums[0] is equal to 1.
 solution.pick(1);
 Show Company Tags
 Show Tags
 Show Similar Problems

 */

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Solution_wa {
private:
    vector<int> num;
public:
    //@note wa
    /*
     on the large test data, wa
     */
    Solution(vector<int> nums) {
        num = nums;
        sort(num.begin(), num.end());
    }
    
    ///@note    use th STL API lower_bount and upper_bound function
    //          I can't use sort(), because the problem requests the original index!!!
    int pick(int target) {
        vector<int>::iterator start = lower_bound(num.begin(), num.end(), target);  //  the first appearance of the target
        vector<int>::iterator end = upper_bound(num.begin(), num.end(), target); //  the first appearance of the element larger than target
        int len = end - start;
        int start_indx = start - num.begin();
        return (rand() % len) + start_indx;
    }
};

///@note    1. reservoir smapling
//          2. http://www.geeksforgeeks.org/reservoir-sampling/
//          3. https://en.wikipedia.org/wiki/Reservoir_sampling
class Solution {
    private:
    vector<int> nums;
    public:
    Solution(vector<int> nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int rslt = 0;
        for (int i = 0, cnt = 1; i < nums.size(); i++) {
            if (nums[i] == target && (rand() % cnt++) == 0) rslt = i;
        }
        return rslt;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */

int main() {
    vector<int> nums = {1,2,3,3,3};
    Solution slt(nums);
    for (int i = 0; i < 10; i++)
        int rslt = slt.pick(3);
    return 0;
}






































