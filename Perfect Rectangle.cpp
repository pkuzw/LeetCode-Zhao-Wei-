//
//  Perfect Rectangle.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/24/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Perfect Rectangle
///@author  Wei Zhao
///@version 1.0
///@date    2016.09.24
/*
 Given N axis-aligned rectangles where N > 0, determine if they all together form an exact cover of a rectangular region.
 
 Each rectangle is represented as a bottom-left point and a top-right point. For example, a unit square is represented as [1,1,2,2]. (coordinate of bottom-left point is (1, 1) and top-right point is (2, 2)).
 
 
 Example 1:
 
 rectangles = [
 [1,1,3,3],
 [3,1,4,2],
 [3,2,4,4],
 [1,3,2,4],
 [2,3,3,4]
 ]
 
 Return true. All 5 rectangles together form an exact cover of a rectangular region
 
 Example 2:
 
 rectangles = [
 [1,1,2,3],
 [1,3,2,4],
 [3,1,4,2],
 [3,2,4,4]
 ]
 
 Return false. Because there is a gap between the two rectangular regions.
 */

#include <vector>
using namespace std;

class Solution {
    public:
    ///@brief   judge whether an array of rectangles can assemble a bigger rectangle or not
    ///@param   rectangles  an array of rectangles
    ///@return  true if the little rectangle could assemble a bigger rectangle, or return false
    ///@note    1. enumeration
    //          2. find the most left-bottom point and the most right-top point in the array, then we could get the large rectangle's area
    //          3. accumulate every small rectangle's area in the array. if it is equal to the big rectangle, then return true. Or return false
    //          4. wa - [[0,0,1,1],[0,1,3,2],[1,0,2,2]]
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        if (rectangles.empty() || rectangles[0].empty())    return true;
        vector<vector<int>> left_most, right_most;
        
        int left = INT_MAX;
        int right = INT_MIN;
        for (int i = 0; i < rectangles.size(); i++) {
            if (left >= rectangles[i][0]) {
                vector<int> left_candidates;
                left_candidates.push_back(rectangles[i][0]);
                left_candidates.push_back(rectangles[i][1]);
                left_most.push_back(left_candidates);
                left = rectangles[i][0];
            }
            if (right <= rectangles[i][2]) {
                vector<int> right_candidates;
                right_candidates.push_back(rectangles[i][2]);
                right_candidates.push_back(rectangles[i][3]);
                right_most.push_back(right_candidates);
                right = rectangles[i][2];
            }
        }
        
        int bottom = INT_MAX;
        int top = INT_MIN;
        for (int i = 0; i < left_most.size(); i++) {
            if (bottom >= left_most[i][0])  bottom = left_most[i][0];
        }
        for (int i = 0; i < right_most.size(); i++) {
            if (top <= right_most[i][1])    top = right_most[i][1];
        }
        int large_rect_area = (top - bottom) * (right - left);
        
        int accum_area = 0;
        for (int i = 0; i < rectangles.size(); i++) {
            accum_area += (rectangles[i][2] - rectangles[i][0]) * (rectangles[i][3] - rectangles[i][1]);
        }
        
        return large_rect_area == accum_area;
    }
};

int main() {
    Solution slt;
    vector<vector<int>> rectangles = {{1,1,3,3}, {3,1,4,2}, {1,3,2,4}, {2,2,4,4}};
    bool rslt = slt.isRectangleCover(rectangles);
    return 0;
}


























