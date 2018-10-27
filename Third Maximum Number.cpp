//
//  Third Maximum Number.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/27/18.
//  Copyright © 2018 Zhao Wei. All rights reserved.
//

///@author  Zhao Wei
///@date    October 27, 2018
///@version 1.0

///@file
/*
 Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).
 
 Example 1:
 Input: [3, 2, 1]
 
 Output: 1
 
 Explanation: The third maximum is 1.
 Example 2:
 Input: [1, 2]
 
 Output: 2
 
 Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
 Example 3:
 Input: [2, 2, 3, 1]
 
 Output: 1
 
 Explanation: Note that the third maximum here means the third maximum distinct number.
 Both numbers with value 2 are both considered as second maximum.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    ///@brief   给定一个整型变量组成的数组，找到数组中第三大的元素，如果有重复元素排在前面，比如{1, 2, 2, 3}，则认为1是第三大的元素；如果该元素不存在，则返回最大的元素。
    ///@param   nums    整型变量数组
    ///@return  返回数组中第三大的不同元素，如果不存在，则返回最大元素。
    ///@note    1. 枚举。
    //          2. 第一遍循环找到最大的元素；第二遍循环找到第二大的元素；第三遍循环找到第三大的元素。
    //          3. 时间复杂度为O(n)，空间复杂度为O(n)。其中n为数组长度。
    int thirdMax(vector<int>& nums) {
        if (nums.empty())   return 0;
        int rslt = nums.front();
        if (nums.size() == 1)   return rslt;
        int m1 = INT_MIN, m2 = INT_MIN, m3 = INT_MIN;
        bool assign_flg = false;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > m1)   m1 = nums[i];
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > m2 && m1 > nums[i])    m2 = nums[i];
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] >= m3 && m2 > nums[i]) {    // 注意，这里的判定条件也应该是>=，而非>，因为如果第三大的数就是INT_MIN，那么>会跳过，不会给m3赋值。
                assign_flg = true;  // 注意，如果第三大的数就是INT_MIN，则就应该返回INT_MIN。
                m3 = nums[i];
            }
        }
        
        rslt = assign_flg ? m3 : m1;
        return rslt;
    }
};

int main() {
    int iarr[10] =  {1, 2, INT_MIN};
    vector<int> nums(iarr, iarr+3);
    Solution slt;
    int rslt = slt.thirdMax(nums);
    cout << "The third maximum of nums is " << rslt << "." << endl;
    return 0;
}
