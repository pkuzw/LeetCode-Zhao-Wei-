//
//  Data Stream as Disjoint Intervals.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/4.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Data Stream as Disjoint Intervals
///@author  zhaowei
///@date    2016.08.04
///@version 1.0

#include <iostream>
#include <vector>
using namespace std;

/**
 * Definition for an interval.
*/
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class SummaryRanges {
public:
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        
    }
    
    vector<Interval> getIntervals() {
        
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */

int main() {
    return 0;
}