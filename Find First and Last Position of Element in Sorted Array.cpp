//
//  Find First and Last Position of Element in Sorted Array.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/9/18.
//  Copyright © 2018 Zhao Wei. All rights reserved.
//

/*
 Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
 
 Your algorithm's runtime complexity must be in the order of O(log n).
 
 If the target is not found in the array, return [-1, -1].
 
 Example 1:
 
 Input: nums = [5,7,7,8,8,10], target = 8
 Output: [3,4]
 Example 2:
 
 Input: nums = [5,7,7,8,8,10], target = 6
 Output: [-1,-1]
 */

///@author  Zhao Wei
///@date    October 9th, 2018
///@version 1.0

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    ///@brief   在非降序的可能有重复元素的有序数组中，找出指定值的范围。
    ///@param   nums    有序数组
    ///@param   target  目标值
    ///@return  返回用下标表示的目标值范围，如果目标值不存在，则返回[-1, -1]。
    ///@note    1. 变形的二分查找。通过两遍二分查找来找到目标元素的边界。
    //          2. 第一遍二分查找来找目标值的左边界，通过循环条件l < r且如果nums[mid] >= target，则r = m（而非r = m-1）来保证如果目标值存在，则必先找到左边界；
    //          3. 第二遍二分查找找右边界，通过将右边界的初始值置为nums.size()，来使得mid = (l + r) / 2保持在左边界的右侧，而不和左边界冲突。同样，它也要求nums[mid] > target时，r = m（而非nums[mid] >= target，这里注意和2的区别）。
    //          4. 时间复杂度为O(logn)，空间复杂度为O(1)，其中n为数组长度。
    ///         5. refer to: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/discuss/14699/Clean-iterative-solution-with-two-binary-searches-(with-explanation)
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> rslt(2, -1);
        if (nums.empty())   return rslt;
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[mid] < target) l = mid + 1;
            else    r = mid;
        }
        if (nums[l] != target)  return rslt;
        rslt[0] = l;
        r = nums.size();    //为了使第二次二分查找的范围不和已经找到的左边界冲突，需要将r多设1。亦可用mid = (l + r) / 2 + 1和r = mid - 1, l = mid替代
//        r = nums.size() - 1;
        while (l < r) {
//            int mid = (l + r) / 2 + 1;
            int mid = (l + r) / 2;
            if (nums[mid] > target) r = mid; //r = mid - 1;
            else    l = mid + 1; //l = mid;
        }
        //rslt[1] = l;
        rslt[1] = l - 1;
        return rslt;
    }
};

int main() {
    int a[12] = {1, 1, 2, 3, 3, 5, 5, 5, 6, 7, 8, 8};
    vector<int> nums(a, a+12);
    Solution slt;
    vector<int> rslt = slt.searchRange(nums, 5);
    cout << rslt[0] << " " << rslt[1] << endl;
    return 0;
}
