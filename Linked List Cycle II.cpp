///@file	Linked List Cycle II
/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Follow up:
Can you solve it without using extra space?
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

///@date	2015.08.20
///@version	2.0

#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution_v1 {
public:
	///@brief	检查一个链表是否有环
	///@param	head	头指针
	///@return	如果有环，则返回环开始的节点；否则返回nullptr
	/* @note	设链表长度为len，表头到环起点的长度为a，快指针和满指针相遇点到环起点的长度为b，环长度为r，快指针每次移动2步，慢指针
				每次移动1步，则相遇的时候慢指针移动了s的长度，快指针移动了2s的长度。且2s = k*r + s. k为快指针多跑的圈数。所以
				s = kr = (k-1)r + r. 又因为r = len - a. 所以s = (k-1)r + len - a. 又因为s = a + b。所以a + b = (k-1)r + len - a，
				a = (k-1)r + len - a - b. 这个等式的左边是链表首节点到环起点的距离，右边是相遇点到尾结点即环起点的距离。所以如果在
				链表首节点和相遇点各放置一个指针，以每次一步的速度向前移动，则必定会在环起点出相遇。时间复杂度为O(n)，空间复杂度为O(1)。*/
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next)	return nullptr;

		ListNode *fast = head, *slow = head;	//	设置快慢指针
		while (fast && fast->next)	//	找到相遇点
		{
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)	break;
		}

		if (fast == slow)
		{
			fast = head;	//	从链表首节点出发
			while (fast != slow)
			{
				fast = fast->next;
				slow = slow->next;	//	从相遇点出发
			}
			return fast;	//	返回环起点
		}
		else
			return nullptr;	//	不存在环
    }
};

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if (!head || !head->next)	return nullptr;
		ListNode *fast = head, *slow = head;
		while (fast && fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
			if (slow == fast)	break;
		}
		if (slow == fast)
		{
			slow = head;
			while (slow != fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
		else
			return nullptr;
	}
};

int main()
{
	ListNode* n[15];
	for (int i = 0; i != 15; i++)
	{
		n[i] = new ListNode(i);
		if (i > 0)
			n[i-1]->next = n[i];
	}

	n[14]->next = n[3];

	ListNode* head = n[0];

	Solution slt;
	ListNode* rslt = slt.detectCycle(head);
	return 0;
}