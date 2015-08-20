///@file	Reorder List
/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

////@date	2015.08.20
///@version	2.0

#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	修改链表的顺序。将原来的n1, n2, n3, ..., nn改变为n1, nn, n2, nn-1, n3, nn-2...
	///@param	head	链表首节点
	///@return	无
	/* @note	用4个临时指针保存首末节点的指针和首末节点的后继与前驱指针。这个转置的规律是将首节点的指针指向尾结点，然后再将尾节点的指针
				指向首节点的下一个节点，然后再将该节点指向尾节点点的前一个节点。依次螺旋形向内收缩。分两种情况处理，一种是奇数个节点的情形，
				另一种是偶数个节点的情形。时间复杂度为O(n^2)，空间复杂度为O(1)。OJ报TLE。*/
    void reorderList_Time_O_n2(ListNode* head) {
        if (!head)	return;

		ListNode *head_next = head->next;
		ListNode *tail_pre = head;
		ListNode *indx = head;
		int len = 1;
		while (indx->next)
		{
			tail_pre = indx;
			indx = indx->next;
			len++;
		}
		ListNode *tail = indx;
		indx = head;
		if (len % 2 == 0)
		{
			while (head_next != tail)
			{
				indx->next = tail;
				tail->next = head_next;
				indx = head_next;
				tail = tail_pre;
				head_next = head_next->next;
				ListNode *tindx = indx;
				while (tindx->next != tail)
				{
					tindx = tindx->next;
				}
				tail_pre = tindx;
			}
			tail->next = nullptr;
		}
		else
		{
			while (indx != tail)
			{
				indx->next = tail;
				tail->next = head_next;
				indx = head_next;
				tail = tail_pre;
				head_next = head_next->next;
				ListNode *tindx = indx;
				while (tindx->next != tail)
				{
					tindx = tindx->next;
				}
				tail_pre = tindx;
			}
			indx->next = nullptr;
		}
    }

	///@brief	修改链表的顺序。将原来的n1, n2, n3, ..., nn改变为n1, nn, n2, nn-1, n3, nn-2...
	///@param	head	链表首节点
	///@return	无
	/* @note	找到链表的中点，将链表一分为二，然后将后半部分链表翻转，依次插入到前半部分的链表节点之后即可。时间复杂度为O(n)，空间复杂度为O(1)。
	*/
	void reorderList(ListNode* head)
	{
		if (!head || !head->next)	return;
		ListNode *fast = head, *slow = head;
		while (fast->next && fast->next->next)	// 快慢指针法找链表中点
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		fast = slow->next;	//	后半部分链表的首节点
		slow->next = nullptr;	//	前半部分链表的尾结点
		fast = reverseList(fast);	//	翻转后半部分节点
		slow = head;
		while (fast)	//	将后半部分节点逐一插入前半部分节点的后面即可
		{
			ListNode *slow_next = slow->next;
			ListNode *fast_next = fast->next;
			slow->next = fast;
			fast->next = slow_next;
			fast = fast_next;
			slow = slow_next;
		}
	}

private:
	///@brief	翻转一个单链表
	///@param	head	链表表头
	///@return	返回翻转后的链表表头
	/* @note	从前到后依次翻转。利用两个临时变量，一个用来保存循环变量的前一个节点，另一个用来保存后一个节点，然后逐一翻转即可。
				时间复杂度为O(n)，空间复杂度为O(1)
	*/
	ListNode* reverseList(ListNode *head)
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
};

class Solution {
public:
	void reorderList(ListNode* head) {
		if (!head || !head->next)	return;
		ListNode* fast = head, *slow = head;
		while (fast->next && fast->next->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		fast = slow->next;
		slow->next = nullptr;
		slow = head;
		fast = reverseList(fast);

		while (fast)
		{
			ListNode* fast_next = fast->next;
			ListNode* slow_next = slow->next;			

			slow->next = fast;
			fast->next = slow_next;

			slow = slow_next;
			fast = fast_next;
		}
	}

private:
	ListNode* reverseList(ListNode* head)
	{
		if (!head || !head->next)	return head;

		ListNode* indx = head;
		ListNode* indx_next = head->next;
		ListNode* indx_next_next = head->next->next;
		
		indx->next = nullptr;
		while (indx_next)
		{
			indx_next->next = indx;
			indx = indx_next;
			indx_next = indx_next_next;
			if (indx_next_next)
				indx_next_next = indx_next_next->next;
		}
		return indx;
	}
};

int main()
{
	ListNode* n[6];
	for (int i = 0; i != 6; i++)
	{
		n[i] = new ListNode(i);
		if (i > 0)
			n[i-1]->next = n[i];
	}
	
	ListNode* head = n[0];

	Solution slt;
	slt.reorderList(head);
	return 0;
}