///@file	Remove Duplicates from Sorted List 
/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
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
	///@note	因为链表已经有序，故只需要遍历一遍，将重复元素删去即可。时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr)
		{
			return head;
		}
		ListNode *indx = head;
		ListNode *nextNode = head->next;
		while (nextNode != nullptr)
		{
			if (nextNode->val == indx->val)
			{
				indx->next = nextNode->next;
				nextNode->next = nullptr;
				nextNode = indx->next;
			}
			else
			{
				indx = indx->next;
				nextNode = nextNode->next;
			}
		}
		return head;
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
// 		slt.insertNode(head, i);
// 		slt.insertNode(head, i);
	}

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