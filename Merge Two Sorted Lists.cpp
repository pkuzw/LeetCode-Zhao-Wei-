﻿///@file	Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
///@author	zhaowei
///@date	2015.06.08
///@version	1.0

#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	///@brief	将两个已经排好序的链表合二为一
	///@param	l1	链表1
	///@param	l2	链表2
	///@return	返回合并后的链表
	///@author	zhaowei
	///@date	2015.06.08
	///@note	对于每一个原始的节点都新建一个节点来保存，时间复杂度O(n)，空间复杂度O(n)。应该能够优化到空间复杂度O(1)才对。

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
	{
		ListNode* indx1 = l1, *indx2 = l2;
		ListNode* newList = new ListNode(0);	//	新链表的首指针
		ListNode* preNode = newList;
		int cnt = 0;
		while (indx1 != nullptr && indx2 != nullptr)
		{
			ListNode* tmp = new ListNode(0);	//	新结点

			if (indx1->val < indx2->val)
			{				
				tmp = indx1;
				preNode->next = tmp;
				indx1 = indx1->next;
			}
			else
			{
				tmp = indx2;
				preNode->next = tmp;
				indx2 = indx2->next;
			}
			preNode = tmp;
		}

		//	如果一个链表已经归并完毕，则将其剩余部分归并到另一个链表的后面即可。
		if (indx1 == nullptr)
		{
			preNode->next = indx2;
		}
		else if (indx2 == nullptr)
		{
			preNode->next = indx1;
		}
		return newList->next;		
	}

	///@brief	在新链表中插入节点
	///@param	head	新链表的首结点
	///@param	链表的值
	///@note	用于生成测试数据
	void insertNode(ListNode *head, int val)
	{
		ListNode *node = new ListNode(val);

		while (head->next != nullptr)
		{
			head = head->next;
		}
		head->next = node;
	}
};

int main()
{
	ListNode* l1 = new ListNode(4);
	ListNode* l2 = new ListNode(3);
 	Solution slt;
 	for (int i = 2; i <= 5; i++)
 	{
 		slt.insertNode(l1, i*3 - 1);
 		slt.insertNode(l2, i + 1);
 	}

	ListNode* head = slt.mergeTwoLists(l1, l2);

	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}