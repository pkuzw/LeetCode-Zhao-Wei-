//
//  Data Stream as Disjoint Intervals.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/4.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Data Stream as Disjoint Intervals
///@author  zhaowei
///@date    2016.08.14
///@version 1.0

#include <iostream>
#include <vector>
#include <set>
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
    
    ///@brief    构造函数
    SummaryRanges() {
        
    }
    
    ///@brief   向数据结构中添加一个数字
    ///@param   val 数字
    ///@return  无
    ///@note    1. 利用STL中的set模板，采用红黑二叉树存储数字，这样在插入的时候时间复杂度为O(logn)
    void addNum(int val) {
        tree.insert(val);
    }
    
    ///@brief   获取当前数字串的不连续区间
    ///@param   无
    ///@return  不连续数字区间
    ///@note    1. 分三种情况处理，如果是首元素，则将区间的起止元素设为该元素；
    //          2. 如果是非首元素的间隔数字，则将之前的收尾元素设置成一个区间，压入结果数组，然后将首尾元素设为当前元素；
    //          3. 如果是非首元素的区间内的数字，则只需要更新尾元素即可；
    //          4. 最后将首尾元素设置成一个区间，压入结果数组即可。
    //          5. 插入时的空间复杂度为O(logn)，查找的时间复杂度为O(n)。
    vector<Interval> getIntervals() {
        vector<Interval> rslt;
        bool isFirst = true;
        int begin = 0, end = 0;
        for (set<int>::iterator i = tree.begin(); i != tree.end(); i++) {
            if (isFirst) {
                isFirst = false;
                begin = *i;
                end = *i;
            }
            else {
                if (*i > end + 1) {
                    rslt.push_back(Interval(begin, end));
                    begin = *i;
                    end = *i;
                }
                else {
                    end = *i;
                    
                }
            }
        }
        rslt.push_back(Interval(begin, end));
        return rslt;
    }
    
private:
    set<int> tree;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * vector<Interval> param_2 = obj.getIntervals();
 */

int main() {
    SummaryRanges sr;
    sr.addNum(1);
    vector<Interval> rslt = sr.getIntervals();
    sr.addNum(3);
    rslt= sr.getIntervals();
    sr.addNum(7);
    rslt = sr.getIntervals();
    sr.addNum(2);
    rslt = sr.getIntervals();
    sr.addNum(6);
    rslt = sr.getIntervals();
    return 0;
}