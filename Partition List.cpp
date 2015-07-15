///@file	Partition List
/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
///@author	zhaowei
///@date	2015.07.15
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
	///@brief	在链表中根据指定值将链表改变为指定值左侧的元素均小于指定值，右侧的元素均不小于指定值。左右两侧的元素顺序要保持不变
	///@param	head	链表头
	///@param	x		轴值
	///@return	返回改变后的链表表头
	///@note	此题是快速排序中的划分步骤。存储数据的结构由数组变成了链表。用两个链表分别保存比轴值小的元素和比轴值大的元素，然后再将二者合并。
	//			时间复杂度为O(n)，空间复杂度为O(n)。
	ListNode* partition(ListNode* head, int x) {
		if (head == nullptr)
		{
			return head;
		}
		ListNode *lpart = new ListNode(INT_MAX);	//	比轴值小的元素组成的链表
		ListNode *nlpart = new ListNode(INT_MAX);	//	不比轴值小的元素组成的链表

		ListNode *indx = head;
		ListNode *lstart = lpart;
		ListNode *nlstart = nlpart;
		while (indx != nullptr)
		{
			if (indx->val < x)
			{
				lpart->next = indx;	
				lpart = lpart->next;
			}
			else
			{
				nlpart->next = indx;
				nlpart = nlpart->next;
			}
			indx = indx->next;
		}
		lpart->next = nlstart->next;
		nlpart->next = nullptr;

		return lstart->next;
	}

	///@brief	插入新节点
	///@param	head	原链表的首节点
	///@param	val		新节点值
	///@return	无
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
	Solution slt;
	ListNode* head = new ListNode(1);
	slt.insertNode(head, 4);
	slt.insertNode(head, 3);
	slt.insertNode(head, 2);
	slt.insertNode(head, 5);
	slt.insertNode(head, 2);

	
	ListNode* display = head;
	cout << "Before: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;


	head = slt.partition(display, 5);
	cout << "After: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;

	return 0;
}
