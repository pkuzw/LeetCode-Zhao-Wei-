//
//  Max Sum of Rectangle No Larger Than K.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/25.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Max Sum of Rectangle No Larger Than K
///@author  zhaowei
///@date    2016.08.25
///@version 1.0
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    ///@brief   计算和不超过k的最大子矩形值
    ///@param   matrix  矩形
    ///@param   k       最大值
    ///@return  返回子矩形的最大值
    ///@note    1. 参考https://discuss.leetcode.com/topic/48875/accepted-c-codes-with-explanation-and-references/2
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (matrix.empty()) return 0;
        int row = matrix.size(), col = matrix[0].size(), res = INT_MIN;
        for (int l = 0; l < col; ++l) {
            vector<int> sums(row, 0);
            for (int r = l; r < col; ++r) {
                for (int i = 0; i < row; ++i) {
                    sums[i] += matrix[i][r];
                }
                
                // Find the max subarray no more than K
                set<int> accuSet;
                accuSet.insert(0);
                int curSum = 0, curMax = INT_MIN;
                for (int sum : sums) {
                    curSum += sum;
                    set<int>::iterator it = accuSet.lower_bound(curSum - k);
                    if (it != accuSet.end()) curMax = std::max(curMax, curSum - *it);
                    accuSet.insert(curSum);
                }
                res = std::max(res, curMax);
            }
        }
        return res;
    }
};

int main() {
    vector<int> row;
    row.push_back(1);
    row.push_back(0);
    row.push_back(1);
    vector<vector<int>> matrix;
    matrix.push_back(row);
    
    row.clear();
    row.push_back(0);
    row.push_back(-2);
    row.push_back(3);
    matrix.push_back(row);
    
    Solution slt;
    int r = slt.maxSumSubmatrix(matrix, 2);
    return 0;
}
