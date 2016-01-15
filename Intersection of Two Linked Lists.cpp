///@file	Intersection of Two Linked Lists
/*
Write a program to find the node at which the intersection of two singly linked lists begins.

For example, the following two linked lists:

A:          a1 → a2
↘
c1 → c2 → c3
↗            
B:     b1 → b2 → b3

begin to intersect at node c1.

Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
*/
///@author	zhaowei
///@date	2015.07.28
///@version	1.0

///@date	2015.08.14
///@version	1.1

///@date	2016.01.15
///@version	1.2

#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	计算两个链表融合的节点
	///@param	headA	链表A
	///@param	headB	链表B
	///@return	返回两个链表的交叉点，如果没有，则返回nullptr。在函数返回前，应该将两个链表的表头返回原值。
	/* @note	如果两个链表等长，逐一比对即可；如果不等长，将长的截短再逐一比对。时间复杂度为O(n)，空间复杂度为O(1)。*/
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB = 0;
		ListNode *indxA = headA, *indxB = headB;

		while (indxA)
		{
			indxA = indxA->next;
			lenA++;
		}
		while (indxB)
		{
			indxB = indxB->next;
			lenB++;
		}

		indxA = headA;
		indxB = headB;
		if (lenA > lenB)
		{
			for (int i = 0; i < lenA - lenB; i++)
			{
				indxA = indxA->next;
			}
		}
		if (lenB > lenA)
		{
			for (int i = 0; i < lenB - lenA; i++)
			{
				indxB = indxB->next;
			}
		}

		while (indxA && indxB && indxA != indxB)
		{
			indxA = indxA->next;
			indxB = indxB->next;
		}

		return indxA;
    }
};

class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		int lenA = 0, lenB = 0;
		ListNode* indxA = headA, *indxB = headB;
		while (indxA) {
			indxA = indxA->next;
			lenA++;
		}
		while (indxB) {
			indxB = indxB->next;
			lenB++;
		}
		indxA = headA;
		indxB = headB;
		if (lenA > lenB) 
			for (int i = 0; i < lenA - lenB; i++)	indxA = indxA->next;		
		else if (lenA < lenB) 
			for (int i = 0; i < lenB - lenA; i++)	indxB = indxB->next;		
		while (indxA != indxB) {
			indxA = indxA->next;
			indxB = indxB->next;
		}
		return indxA;
	}
};

int main()
{	
	return 0;
}