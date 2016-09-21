//
//  Kth Smallest Element in a Sorted Matrix.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/21/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Kth Smallest Element in a Sorted Matrix
///@author  Wei Zhao
///@date    2016.09.21
///@version 1.0

/*
 Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
 
 Note that it is the kth smallest element in the sorted order, not the kth distinct element.
 
 Example:
 
 matrix = [
 [ 1,  5,  9],
 [10, 11, 13],
 [12, 13, 15]
 ],
 k = 8,
 
 return 13.
 Note:
 You may assume k is always valid, 1 ≤ k ≤ n2.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    ///@brief   find the Kth smallest element in the matrix
    ///@param   matrix
    ///@param   k
    ///@note    1. binary search
    ///         2. use std::upper_bound to cound the number of elements smaller than middle value
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int left = matrix[0][0];
        int right = matrix[n-1][n-1];
        
        while (left < right) {
            int mid = (left + (right - left) / 2);
            int count = 0;
            for (int i = 0; i < n; i++) {
                count += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            }
            if (count < k) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    Solution slt;
    int rslt = slt.kthSmallest(matrix, 8);
    return 0;
}






























