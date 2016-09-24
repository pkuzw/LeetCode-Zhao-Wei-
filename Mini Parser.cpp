//
//  Mini Parser.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 9/23/16.
//  Copyright © 2016 Zhao Wei. All rights reserved.
//

///@file    Mini Parser
///@author  Wei Zhao
///@date    2016.09.23
///@version 1.0
/*
 Given a nested list of integers represented as a string, implement a parser to deserialize it.
 
 Each element is either an integer, or a list -- whose elements may also be integers or other lists.
 
 Note: You may assume that the string is well-formed:
 
 String is non-empty.
 String does not contain white spaces.
 String contains only digits 0-9, [, - ,, ].
 Example 1:
 
 Given s = "324",
 
 You should return a NestedInteger object which contains a single integer 324.
 Example 2:
 
 Given s = "[123,[456,[789]]]",
 
 Return a NestedInteger object containing a nested list with 2 elements:
 
 1. An integer containing value 123.
 2. A nested list containing two elements:
 i.  An integer containing value 456.
 ii. A nested list with one element:
 a. An integer containing value 789.
 */

#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <stack>

using namespace std;

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 
 0
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
    ///@brief   deserilizing a string into a nested integer
    ///@param   s   string
    ///@return  a nested integer
    ///@note    https://discuss.leetcode.com/topic/55627/c-iterative-solution
    NestedInteger deserialize(string s) {
        stack<NestedInteger> st;
        int num = 0, sign = 1;
        bool numValid = false;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '-') {
                sign = -1;
            } else if (isdigit(s[i])) {
                numValid = true;
                num = num * 10 + (s[i] - '0');
            } else if (s[i] == '[') {
                // start a new nested list as current active nested list
                st.push(NestedInteger());
            } else {
                // meaning s[i] == ',' || s[i] == ']'
                // add the last interger into current active nested list, and clear num/sign
                if (numValid) { st.top().add(NestedInteger(sign * num)); }
                numValid = false; num = 0; sign = 1;
                
                // add current active nested list to its parent nested list if the parent exists
                if (s[i] == ']' && st.size() > 1) {
                    auto temp = st.top(); st.pop();
                    st.top().add(temp);
                }
            }
        }
        
        // if there's only one single integer, return it
        if (numValid) {
            return NestedInteger(sign * num);
        }
        // else return the nested list
        return st.top();
    }
};

int main() {
    
    return 0;
}






































