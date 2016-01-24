///@file	Remove Linked List Elements
/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.11
///@version	1.1

///@date	2016.01.24
///@version	1.2

#include <cstdlib>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution_v1 {
public:
	///@brief	删除链表中所有指定值的节点
	///@param	head	链表表头
	///@param	val		指定值
	///@return	返回删除所有链表指定值节点后的表头指针
	/* @note	注意指定值节点是否是头节点。时间复杂度为O(n)，空间复杂度为O(1)。*/
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *indx = head;
		ListNode *pre_indx = head;
		while (indx != nullptr)
		{
			if (indx->val == val)
			{
				if (indx == head)
				{
					head = head->next;					
					pre_indx = head;
					indx = head;
				}
				else
				{
					pre_indx->next = indx->next;	
					indx = indx->next;
				}
			}
			else
			{
				pre_indx = indx;
				indx = indx->next;
			}
		}
		return head;		
    }
};

/*
在删除链表中的指定节点时，需要注意该节点是否是头节点。因为链表的头节点比较特殊，是检索的起始点，如果按照一般方法删除会影响最后的返回值。
所以在删除前，先排除所有头节点是指定值的情形，保证待删除的链表的头节点一定不是指定值。然后设置两个临时变量，一个保存当前节点的前驱节点，
另一个保存当前节点的后继节点。如果当前节点是指定值，那么就将前驱节点指向其后继节点，然后将当前节点和后继节点后移。否则就直接将三个变量
直接后移。在后移时需要注意后继节点是否存在后继节点，需要先判断一下才行。
*/
class Solution_v1_1 {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//排除首节点是要删除节点的情形，因为在头节点，如果按照一般情况删除的话，会到最后找不到链表的起始节点
		while (head && head->val == val)
		{
			head = head->next;
		}

		if (!head)	return nullptr;
		ListNode* pre_indx = new ListNode(INT_MAX);
		pre_indx->next = head;
		ListNode* indx = head;
		ListNode* indx_next = indx->next;

		while (indx)
		{
			if (indx->val == val)
			{
				pre_indx->next = indx_next;
				indx->next = nullptr;				
			}
			else
			{
				pre_indx = indx;				
			}
			indx = indx_next;
			if (indx_next)
				indx_next = indx_next->next;
		}
		return head;
	}
};

class Solution {
public:
	///@brief	删除链表中的指定值节点
	///@param	head	头结点
	///@param	val		指定值
	///@return	返回链表头结点
	///@note	1. 注意考虑头节点为被删除节点的情形。
	ListNode* removeElements(ListNode* head, int val) {
		while (head && head->val == val)		head = head->next;
		if (!head)	return nullptr;

		ListNode* pre_indx = new ListNode(INT_MIN);
		pre_indx->next = head;
		ListNode* indx = head;
		ListNode* indx_nxt = head->next;
		while (indx) {
			if (indx->val == val) {
				pre_indx->next = indx_nxt;
				indx->next = nullptr;
			}
			else	pre_indx = indx;			
			indx = indx_nxt;
			indx_nxt = indx_nxt ? indx_nxt->next : nullptr;
		}
		return head;
	}
};

int main()
{
	ListNode *head = new ListNode(2);
	ListNode *n1 = new ListNode(2);
	ListNode *n2 = new ListNode(2);
	ListNode *n3 = new ListNode(2);
	ListNode *n4 = new ListNode(3);
	ListNode *n5 = new ListNode(2);

	head->next = n1;
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n1->next = n2;

	Solution slt;
	ListNode *rslt = slt.removeElements(head, 2);

	Solution_v1 slt_v1;
	rslt = slt_v1.removeElements(head, 1);

	return 0;
}