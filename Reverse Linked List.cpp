///@file	Reverse Linked List
/*
Reverse a singly linked list.

click to show more hints.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?
*/
///@author	zhaowei
///@date	2015.07.20
///@versio	1.0

#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	///@brief	翻转一个单链表
	///@param	head	链表表头
	///@return	返回翻转后的链表表头
	///@note	迭代法：利用了栈来进行临时存储，空间复杂度为O(n)，时间复杂度为O(n)。
	ListNode* reverseList(ListNode *head)
	{
		ListNode *indx = head;		
		stack<ListNode*> s;
		while (indx->next != nullptr)
		{			
			s.push(indx);
			indx = indx->next;
		}
		ListNode *new_head = indx;
		while (!s.empty())
		{
			ListNode *tmp = s.top();
			s.pop();
			tmp->next = nullptr;
			
			indx->next = tmp;
			indx = indx->next;
		}
		indx->next = nullptr;
		return new_head;
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
 	slt.insertNode(head, 2);
 	slt.insertNode(head, 3);
 	slt.insertNode(head, 4);
 	slt.insertNode(head, 5);

	ListNode* display = head;
	cout << "Before: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;

	head = slt.reverseList(display);

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