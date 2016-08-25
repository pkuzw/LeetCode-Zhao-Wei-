//
//  Nested List Weight Sum II.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 16/8/25.
//  Copyright © 2016年 Zhao Wei. All rights reserved.
//

///@file    Nested List Weight Sum II
///@author  zhaowei
///@date    2016.08.25
///@version 1.0


#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger {
public:
    // Constructor initializes an empty nested list.
    NestedInteger();
 
    // Constructor initializes a single integer.
    NestedInteger(int value);
 
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;
 
    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;
 
    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);
 
    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);
 
    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution {
public:
    ///@brief   按照叶子节点权值为1，根节点权值为d的要求，累加所有节点的和
    ///@param   nestedList  嵌套链表
    ///@return  返回权值累加和
    ///@note    1. 递归；
    //          2. 先计算出嵌套的深度；
    //          3. 然后再按照深度从根向叶进行权重加和。
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int depth = 1;
        depth = getDepth(nestedList, 1);
        return depthSum(nestedList, depth);
    }
    
    ///@brief   计算嵌套的深度
    ///@param   nestedList  嵌套链表
    ///@param   depth   深度
    ///@return  返回嵌套深度
    int getDepth(vector<NestedInteger> nestedList, int curDepth) {
        int rslt = 0;
        for (NestedInteger i : nestedList) {
            if (!i.isInteger()) {
                rslt = max(rslt, getDepth(i.getList(), curDepth+1));
            }
        }
        return max(rslt, curDepth);
    }
    
    ///@brief   返回嵌套链表的权重和
    ///@param   nestedList  嵌套链表
    ///@param   depth       嵌套深度
    ///@return  返回嵌套权重和
    int depthSum(vector<NestedInteger> nestedList, int depth) {
        int rslt = 0;
        for (NestedInteger i : nestedList) {
            if (i.isInteger())  rslt += i.getInteger() * depth;
            else    rslt += depthSum(i.getList(), depth-1);
        }
        return rslt;
    }
};

int main() {
    
    return 0;
}






































