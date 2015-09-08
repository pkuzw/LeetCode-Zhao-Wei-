//
//  Add Two Numbers.cpp
//  LeetCode by zhaowei
//
//  Created by Zhao Wei on 15/9/8.
//  Copyright (c) 2015年 Zhao Wei. All rights reserved.
//

/* @file
 You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 
 Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 Output: 7 -> 0 -> 8
*/
///@author  zhaowei
///@date    2015.09.08
///@version 1.0

#include <stdio.h>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1 && l2)  return l2;
        else if (!l2 && l1)  return l1;
        else if (!l1 && !l2) return nullptr;
        int carry = 0;
        ListNode* i1 = l1, *i2 = l2;
        int len1 = 0, len2 = 0;
        while (l1) {
            i1 = i1->next;
            len1++;
        }
        while (l2) {
            i2 = i2->next;
            len2++;
        }
        i1 = l1;
        i2 = l2;
        
        if (len1 == len2) {
            while (i1->next && i2->next){
                i1->val += i2->val;
                if (carry)  i1->val++;
                if (i1->val >= 10){
                    i1->val %= 10;
                    carry = 1;
                }
                else    carry = 0;
                i1 = i1->next;
                i2 = i2->next;
            }
            i1->val += i2->val;
            if (carry)  i1->val++;
            if (i1->val >= 10){
                i1->val %= 10;
                carry = 1;
            }
            else    carry = 0;
            if (carry) {
                ListNode* n = new ListNode(1);
                i1->next = n;
                return l1;
            }
        }
        else if (len1 > len2) {
            while (i2){
                i1->val += i2->val;
                if (carry)  i1->val++;
                if (i1->val >= 10){
                    i1->val %= 10;
                    carry = 1;
                }
                else    carry = 0;
                i1 = i1->next;
                i2 = i2->next;
            }
            while (carry) {
                if (i1->next) {
                    i1->val++;
                    if (i1->val >= 10) {
                        i1->val %= 10;
                        carry = 1;
                    }
                    else carry = 0;
                    i1 = i1->next;
                }
                else {
                    ListNode* n = new ListNode(1);
                    i1->next = n;
                    return l1;
                }
            }
        }
        else {
            
        }
        return i1;
    }
};

int main() {
    return 0;
}