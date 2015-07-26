///@file	Linked List Cycle
/*
Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space? 
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	///@brief	判断一个单链表是否有环
	///@param	head	链表头节点
	///@return	如果单链表有环，则返回true；否则返回false
	/* @note	用两个指针遍历单链表，每个指针的前进步长不等，如果指针能够重合，则说明有环，如果指针能够到达尾结点，则说明没有环。时间复杂度为O(n)，空间复杂度为O(1)。*/
	bool hasCycle(ListNode *head) {
		if (!head || !head->next)	return false;

		ListNode* indx1 = head;
		ListNode* indx2 = head->next;

		while (indx1 != indx2)
		{
			if (!indx2 || !indx1)	return false;

			indx1 = indx1->next;

			if (indx2->next)
				indx2 = indx2->next->next;
			else
				return false;
		}
		return true;
	}
};

int main()
{
	ListNode* n[3];
	for (int i = 0; i != 3; i++)
	{
		n[i] = new ListNode(i);
		if (i > 0)
			n[i-1]->next = n[i];
	}

//	n[0]->next = n[0];

	ListNode* head = n[0];

	Solution slt;
	bool rslt = slt.hasCycle(head);
	return 0;
}