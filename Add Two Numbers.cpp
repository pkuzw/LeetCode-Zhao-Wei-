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
///@date    2015.09.09
///@version 1.0

///@date	2016.03.31
///@version	2.0

#include <stdio.h>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1 && l2)  return l2;
        else if (!l2 && l1)  return l1;
        else if (!l1 && !l2) return nullptr;
        int carry = 0;
        ListNode* i1 = l1, *i2 = l2;
        int len1 = 0, len2 = 0;
        while (i1) {
            i1 = i1->next;
            len1++;
        }
        while (i2) {
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
                
            }
            return l1;
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
					if (carry)	i1->val++;
					if (i1->val >= 10){
						i1->val %= 10;
						ListNode* n = new ListNode(1);
						i1->next = n;
						break;
					}
					else carry = 0;
                }
            }
            return l1;
        }
        else {
            while (i1){
                i2->val += i1->val;
                if (carry)  i2->val++;
                if (i2->val >= 10){
                    i2->val %= 10;
                    carry = 1;
                }
                else    carry = 0;
                i1 = i1->next;
                i2 = i2->next;
            }
            while (carry) {
                if (i2->next) {
                    i2->val++;
                    if (i2->val >= 10) {
                        i2->val %= 10;
                        carry = 1;
                    }
                    else carry = 0;
                    i2 = i2->next;
                }
                else {
					if (carry)	i2->val++;
					if (i2->val >= 10){
						i2->val %= 10;
						ListNode* n = new ListNode(1);
						i2->next = n;
						break;
					}
					else carry = 0;
                }                
            }
            return l2;
        }
    }
};

class Solution {
public:
	///@note	1. 遍历链表；
	//			2. 因为链表的长度可能不同，所以用一个标识符来标记较长的链表，便于较短的链表计算完成后继续向后进位；
	//			3. 计算出两个链表的长度；
	//			4. 先计算截短对齐后的链表，然后返回出来最后的节点；
	//			5. 然后继续把剩余的节点计算出来即可；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。其中n为节点数目。
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int len1 = 0, len2 = 0;
		ListNode* head1 = l1, *head2 = l2;
		if (!l1 && l2)	return l1;
		while (l1) {
			len1++;
			l1 = l1->next;
		}
		while (l2) {
			len2++;
			l2 = l2->next;
		}
		bool long_list_flg = len1 >= len2 ? false : true;
		int align_len = long_list_flg ? len1 : len2;
		int carry = 0;

		ListNode* leftover = addAlignLists(head1, head2, align_len, carry, long_list_flg);

		if (!leftover->next) {
			if (carry)	leftover->next = new ListNode(carry);		
		}
		else {			
			leftover->next->val += carry;
			while (leftover->next->val >= 10) {
				leftover->next->val %= 10;
				carry = 1;
				leftover = leftover->next;
				if (leftover->next)	leftover->next->val += carry;
				else	leftover->next = new ListNode(carry);
			}			
		}
		return long_list_flg ? head2 : head1;
	}

	///@brief	计算对齐的两个链表和
	///@param	l1, l2	两个链表
	///@param	len		对齐的长度
	///@param	carry	进位标记
	///@param	long_list_flg	较长的链表标记，l1: false, l2: true
	///@return	返回计算结果的最后一个节点，和是累加到较长的那个链表上的。
	ListNode* addAlignLists(ListNode* l1, ListNode* l2, int len, int& carry, bool& long_list_flg) {
		ListNode* last_node = long_list_flg ? l2 : l1;
		for (int i = 0; i != len; i++) {
			int bit_sum = l1->val + l2->val;
			bit_sum += carry;
			carry = bit_sum >= 10 ? 1 : 0;
			bit_sum %= 10;
			if (!long_list_flg)	l1->val = bit_sum;			
			else	l2->val = bit_sum;
			l1 = l1->next;
			l2 = l2->next;
			if (i < len - 1)		last_node = last_node->next;			
		}
		return last_node;
	}
};

int main() { 
    ListNode* l1 = new ListNode(0);
    
	 ListNode* l2 = new ListNode(0);
    //ListNode* n1 = new ListNode(9);    
 
//	l2->next = n1;
    Solution slt;
    ListNode* rslt = slt.addTwoNumbers(l1, l2);
    return 0;
}
