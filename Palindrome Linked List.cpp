///@file	Palindrome Linked List
/*
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.06
///@version	2.0

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	判断一个单链表是否是回文的
	///@param	head	链表头
	///@return	如果是回文的则返回true；否则返回false
	/* @note	用栈来保存链表的前半部分，用队来保存链表的后半部分。然后逐一比对栈顶和队首元素，如果二者不相等，则返回true，如果相等，
				则弹栈和出队。直到栈和队为空，返回true。时间复杂度为O(n)，空间复杂度为O(n)。*/
	bool isPalindrome(ListNode* head) {
		if (!head)			return true;

		int len = 0;
		ListNode *indx = head;
		while (indx)
		{
			indx = indx->next;
			len++;
		}

		int mid = len / 2;
		stack<ListNode*> stk;
		queue<ListNode*> que;
		indx = head;
		for (int i = 0; i != mid; i++)
		{
			stk.push(indx);
			indx = indx->next;
		}

		if (len % 2)	indx = indx->next;

		for (int i = 0; i != mid; i++)
		{
			que.push(indx);
			indx = indx->next;
		}

		while (!stk.empty() && !que.empty())
		{
			if (stk.top()->val == que.front()->val)
			{
				stk.pop();
				que.pop();
			}
			else
				return false;
		}
		return true;
	}
};

class Solution {
public:
	bool isPalindrome(ListNode* head) {
		if (!head || !head->next)	return true;

		ListNode *fast = head, *slow = head;

		while (fast->next && fast->next->next)	//	快慢节点法找链表中点
		{
			fast = fast->next->next;
			slow = slow->next;
		}

		fast = slow->next;	//	后半部分的起点
		slow->next = nullptr;
		slow = head;	//	前半部分（奇数长度时包含中点）的起点

		ListNode *fast_next = fast->next;	//	将后半部分翻转，翻转时用两个临时变量，保存fast的后续节点(fast_next)和后续节点的后续节点(indx)		
		ListNode *fast_next_next = fast_next ? fast_next->next : nullptr;
		fast->next = nullptr;
		while (fast_next)
		{
			fast_next->next = fast;
			fast = fast_next;
			fast_next = fast_next_next;
			fast_next_next = fast_next_next ? fast_next_next->next : nullptr;			
		}

		while (fast)
		{
			if (fast->val != slow->val)	return false;

			fast = fast->next;
			slow = slow->next;
		}
		return true;
	}
};

int main()
{
	ListNode* n[11];
	for (int i = 0; i != 11; i++)
	{
		n[i] = new ListNode(i);
		if (i > 0)
			n[i-1]->next = n[i];
	}

	for (int i = 6; i != 11; i++)
		n[i]->val = (10-i);
	//	n[0]->next = n[0];

	ListNode* head = n[1];
// 	n[0]->next = nullptr;
// 
// 	n[1]->val = 0;
// 	n[1]->next = nullptr;

	n[0]->val = 1;
	n[0]->next = n[1];

	n[1]->val = 1;
	n[1]->next = nullptr;

	head = n[0];



	Solution slt;
	bool rslt = slt.isPalindrome(head);
	return 0;
}