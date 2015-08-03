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

#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	///@brief	修改链表的顺序。将原来的n1, n2, n3, ..., nn改变为n1, nn, n2, nn-1, n3, nn-2...
	///@param	head	链表首节点
	///@return	无
	/* @note	用4个临时指针保存首末节点的指针和首末节点的后继与前驱指针。这个转置的规律是将首节点的指针指向尾结点，然后再将尾节点的指针
				指向首节点的下一个节点，然后再将该节点指向尾节点点的前一个节点。依次螺旋形向内收缩。分两种情况处理，一种是奇数个节点的情形，
				另一种是偶数个节点的情形。时间复杂度为O(n^2)，空间复杂度为O(1)。OJ报TLE。*/
    void reorderList(ListNode* head) {
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

	Solution slt;
	slt.reorderList(head);
	return 0;
}