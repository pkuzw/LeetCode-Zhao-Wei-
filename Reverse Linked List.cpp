///@file	Reverse Linked List
/*
Reverse a singly linked list.

click to show more hints.

Hint:
A linked list can be reversed either iteratively or recursively. Could you implement both?
*/
///@author	zhaowei
///@date	2015.07.20
///@version	1.0

///@author	zhaowei
///@date	2015.07.21
///@version	1.1

///@date	2015.08.11
///@version	2.0

///@date	2015.10.15
///@version	2.1

#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	翻转一个单链表
	///@param	head	链表表头
	///@return	返回翻转后的链表表头
	///@note	迭代法：利用了栈来进行临时存储，空间复杂度为O(n)，时间复杂度为O(n)。
	ListNode* reverseList_Space_O_n(ListNode *head)
	{
		if (head == nullptr)
			return head;
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

	///@brief	翻转一个单链表
	///@param	head	链表表头
	///@return	返回翻转后的链表表头
	/* @note	从前到后依次翻转。利用两个临时变量，一个用来保存循环变量的前一个节点，另一个用来保存后一个节点，然后逐一翻转即可。
				时间复杂度为O(n)，空间复杂度为O(1)
	*/
	ListNode* reverseList_Space_O_1(ListNode *head)
	{
		if (head == nullptr)	return head;	//	边界情况
		ListNode *indx = head->next;
		ListNode *pre_indx = head;
		head->next = nullptr;

		ListNode *after_indx = new ListNode(0);
		if (indx != nullptr)	//	边界情况
			after_indx = indx->next;

		while (indx != nullptr)	//	翻转操作
		{			
			indx->next = pre_indx;	
			pre_indx = indx;
			indx = after_indx;

			if (after_indx != nullptr)
				after_indx = after_indx->next;			
		}
		return pre_indx;
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

class Solution {
public:
	///@brief	翻转链表
	///@param	head	链表头指针
	///@return	返回翻转后链表的首节点
	///@note	用两个临时变量来保存当前节点的后一个节点和当前节点的后一个节点的后一个节点。在翻转前，对只有0个或1个节点的情形直接返回头结点；然后处理普遍的
	//			情形。如果有两个以上的节点，先将头结点指向空指针，然后以当前节点的后继节点是否为空来进行循环的判定条件，将后继节点的指针指向当前节点，然后
	//			依次后移当前节点和后继节点，对于后继节点的后继节点，再后移时要判断一下其是否有后继节点。最后退出循环后返回当前节点作为翻转后的头节点。
	ListNode* reverseList(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* indx = head;
		ListNode* indx_next = indx->next;
		ListNode* indx_next_next = indx_next->next;
		indx->next = nullptr;

		while (indx_next) {
			indx_next->next = indx;
			indx = indx_next;
			indx_next = indx_next_next;
			if (indx_next_next)	indx_next_next = indx_next_next->next;
		}
		return indx;
	}
};

int main()
{
	Solution_v1 slt_v1;
	ListNode* head = new ListNode(1);
 	slt_v1.insertNode(head, 2);
 	slt_v1.insertNode(head, 3);
 	slt_v1.insertNode(head, 4);
 	slt_v1.insertNode(head, 5);

	ListNode* display = head;
	cout << "Before: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;

	head = slt_v1.reverseList_Space_O_1(display);
	cout << "After: ";
	display = head;
	while (display != nullptr)
	{
		cout << display->val;
		cout << ' ';
		display = display->next;
	}
	cout << endl;

	Solution slt;
	ListNode* rslt = slt.reverseList(head);
	display = rslt;
	cout << "Reverse again: "; 
	while (display) {
		cout << display->val << " ";
		display = display->next;
	}
	cout << endl;

	return 0;
}