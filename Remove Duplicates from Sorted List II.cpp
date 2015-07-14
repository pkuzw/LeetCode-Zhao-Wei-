///@file	Remove Duplicates from Sorted List II
/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/
///@author	zhaowei
///@date	2015.07.14
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
	///@brief	删除已经排好序的链表中的重复节点
	///@param	head	链表表头
	///@return	返回删除重复元素后的链表头
	///@note	因为链表已经有序，故只需要遍历一遍，将重复元素删去即可。在删除时需要向前返回到不重复的元素为止。故需要在原始链表头加入一个首节点指针。时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* deleteDuplicates(ListNode* head) {
		ListNode *first = new ListNode(INT_MAX);		
		first->next = head;

		ListNode *indx = head;
		ListNode *next_indx = indx->next;
		ListNode *pre_indx = first;
		bool flg = false;	//	标记pre_indx后面的节点indx是否存在过重复元素
		while (next_indx != nullptr)
		{
			if (indx->val == next_indx->val)
			{
				indx->next = next_indx->next;
				next_indx->next = nullptr;
				next_indx = indx->next;
				flg = true;
			}
			else
			{
				if (flg)
				{
					pre_indx->next = indx->next;
					indx->next = nullptr;
					indx = pre_indx->next;					
				}
				else
				{
					indx = indx->next;
				}
				next_indx = next_indx->next;				
			}
		}
		return first->next;
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
	ListNode* head = new ListNode(1);
	Solution slt;
	for (int i = 2; i <= 5; i++)
	{
		slt.insertNode(head, i);
		slt.insertNode(head, i);
		slt.insertNode(head, i);
	}
	slt.insertNode(head, 7);

	ListNode* display = head;
	cout << "Before delete: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;


	head = slt.deleteDuplicates(display);
	cout << "After delete: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}