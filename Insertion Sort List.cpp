///@file	Insertion Sort List 
/*
Sort a linked list using insertion sort.
*/
///@author	zhaowei
///@date	2015.08.03
///@version 1.0

#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	///@brief	插入法排序
	///@param	head	链表首节点
	///@return	返回排好序的链表首节点
	///@note	插入法排序。新建一个链表，逐个插入。这样就简单多了。时间复杂度为O(n^2)，空间复杂度为O(n)。
	ListNode *insertionSortList(ListNode *head) {
		ListNode *res = new ListNode(INT_MIN);	//	首节点之前的那个节点
		ListNode *cur = res;
		while (head)
		{
			ListNode *next = head->next;
			cur = res;
			while (cur->next && cur->next->val <= head->val) //	找到应该插入的位置cur
			{
				cur = cur->next;
			}
			head->next = cur->next;
			cur->next = head;
			head = next;
		}
		return res->next;
	}
};

int main()
{
	ListNode* n[7];
	for (int i = 0; i != 7; i++)
	{
		n[i] = new ListNode(i);
		if (i > 0)
			n[i-1]->next = n[i];
	}

	ListNode* head = n[0];
	n[1]->val = 10;
	n[2]->val = 3;
	n[3]->val = 5;
	n[4]->val = 1;
	n[5]->val = 7;
	n[6]->val = 3;
	Solution slt;
	head = slt.insertionSortList(head);
	return 0;
}