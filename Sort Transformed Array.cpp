//
//  Sort Transformed Array.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/23.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Sort Transformed Array
///@author  zhao wei
///@date    2016.08.23
///@version 1.0

#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
public:
    ///@brief   给定一组排好序的整数，在给定a, b, c的情况下，计算f(x) = ax^2 + bx + c的函数值，使其函数值在O(n)的时间复杂度内按照升序排列
    ///@param   nums    整数数组
    ///@param   a, b, c 二次函数参数
    ///@return  返回升序排列的函数值数组
    ///@note    1. 先通过二分查找，以对称轴x = -b/2a为中心，向两侧扩展，找到距离其最近或最远（根据a值确定）的整数；
    //          2. 求出其对应的函数值即可；
    //          3. 时间按复杂度为O(n)，空间复杂度为O(1)。
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        double axis = (double)b / ((-2) * (double)a);
        int nearest_indx = nums.size() - 1;
        for (int i = 0; i != nums.size(); i++) {
            if (axis > (double)nums[i]) continue;
            else if (axis == (double)nums[i]) {
                nearest_indx = i;
                break;
            }
            else {
                nearest_indx = double(abs(nums[i] - axis)) < double(abs(nums[i-1] - axis)) ? i : i - 1;
                break;
            }
            
        }
        
        vector<int> rslt;
        if (a == 0) {
            if (b > 0) {
                for (int i = 0; i != nums.size(); i++)
                    rslt.push_back(b * nums[i] + c);
            }
            else if (b < 0) {
                for (int i = nums.size() - 1; i >= 0; i--)
                    rslt.push_back(b * nums[i] + c);
            }
            else {
                for (int i = 0; i != nums.size(); i++)
                    rslt.push_back(c);
            }
        }
        else {
            int i = nearest_indx;
            int left = nearest_indx - 1;
            int right = nearest_indx + 1;
            rslt.push_back(a * nums[i] * nums[i] + b * nums[i] + c);
            while (left >= 0 && right < nums.size()) {
                if (abs((double)nums[left] - axis) < abs((double)nums[right] - axis)) {
                    rslt.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                    left--;
                }
                else {
                    rslt.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                    right++;
                }
            }
            while (left >= 0) {
                rslt.push_back(a * nums[left] * nums[left] + b * nums[left] + c);
                left--;
            }
            while (right < nums.size()) {
                rslt.push_back(a * nums[right] * nums[right] + b * nums[right] + c);
                right++;
            }
            if (a < 0)  reverse(rslt.begin(), rslt.end());
        }
        return rslt;
    }
};

int main() {
    /*
     [-99,-94,-90,-88,-84,-83,-79,-68,-58,-52,-52,-50,-47,-45,-35,-29,-5,-1,9,12,13,25,27,33,36,38,40,46,47,49,57,57,61,63,73,75,79,97,98]
     -2
     44
     -56
     */
    Solution slt;
    int a = -2, b = 44, c = -56;
    int nums_arr[] = {-99,-94,-90,-88,-84,-83,-79,-68,-58,-52,-52,-50,-47,-45,-35,-29,-5,-1,9,12,13,25,27,33,36,38,40,46,47,49,57,57,61,63,73,75,79,97,98};
    vector<int> nums;
    for (auto i : nums_arr)
        nums.push_back(i);
    vector<int> rslt;
    rslt = slt.sortTransformedArray(nums, a, b, c);
    return 0;
}































