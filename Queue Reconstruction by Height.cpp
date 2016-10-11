//
//  Queue Reconstruction by Height.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 10/10/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Queue Reconstruction by Height
///@author  Wei Zhao
///@date    10.10.2016
///@version 1.0

/*
 Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.
 
 Note:
 The number of people is less than 1,100.
 
 Example
 
 Input:
 [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
 
 Output:
 [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
 */

#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace  std;

class Solution {
public:
    /*
     @note
     1. resort the queue by given order. the first element must be in descending order and the if they are same then the second element will be ordered ascendingly.
     2. after resorting, insert the element by the second element in the pair.
     3. https://discuss.leetcode.com/topic/60470/6-lines-concise-c
     */
    
    ///@brief   the self-define comparison
    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first  || (a.first == b.first && a.second < b.second);
    }
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), cmp);
        vector<pair<int, int>> rslt;
        for (int i = 0; i < people.size(); i++) {
            rslt.insert(rslt.begin() + people[i].second, people[i]);
        }
        return rslt;
    }
};

int main() {
    
    return 0;
}
