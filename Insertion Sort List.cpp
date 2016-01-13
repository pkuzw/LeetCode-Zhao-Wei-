///@file	Insertion Sort List 
/*
Sort a linked list using insertion sort.
*/
///@author	zhaowei
///@date	2015.08.03
///@version 1.0

///@date	2015.08.19
///@version	1.1

///@date	2016.01.13
///@version	1.2

#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	插入法排序
	///@param	head	链表首节点
	///@return	返回排好序的链表首节点
	///@note	插入法排序。新建一个链表，逐个插入。这样就简单多了。时间复杂度为O(n^2)，空间复杂度为O(n)。
	ListNode *insertionSortList(ListNode *head) {
		ListNode *res = new ListNode(INT_MIN);	//	首节点之前的那个节点
		ListNode *cur = res;
		while (head)
		{
			ListNode *next = head->next;
			cur = res;
			while (cur->next && cur->next->val <= head->val) //	找到应该插入的位置cur
			{
				cur = cur->next;
			}
			head->next = cur->next;
			cur->next = head;
			head = next;
		}
		return res->next;
	}
};

class Solution_v1_1 {
public:
	ListNode* insertionSortList(ListNode* head) {
		if (!head || !head->next)	return head;

		ListNode* rslt = new ListNode(INT_MIN);		//	这里必须要设置成最小值，以保证第一次插入的数肯定在rslt之后
		ListNode* indx = head;
		
		while (indx)
		{
			ListNode* indx_next = indx->next;
			ListNode* cur = rslt;	//	每次循环都要重置cur值
			while (cur->next && cur->next->val <= indx->val)
				cur = cur->next;
			indx->next = cur->next;
			cur->next = indx;
			indx = indx_next;
		}
		return rslt->next;
	}
};

class Solution {
public:
	///@brief	插入法给链表排序
	///@param	head	链表首节点
	///@return	返回排好序的链表首节点
	///@note	1. 设置一个哨兵节点dump(INT_MIN)，位于首节点之前；
	//			2. indx为当前待插入的节点，cur为比较的节点，从dump开始；
	//			3. 时间复杂度为O(n^2)，空间复杂度为O(1)。
	ListNode* insertionSortList(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode *dump = new ListNode(INT_MIN);
		ListNode* indx = head;		
		while (indx) {
			ListNode* cur = dump;
			ListNode* indx_nxt = indx->next;
			while (cur->next && cur->next->val <= indx->val) {
				cur = cur->next;
			}
			indx->next = cur->next;
			cur->next = indx;
			indx = indx_nxt;			
		}
		return dump->next;
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
	n[1]->val = 10;
	n[2]->val = 3;
	n[3]->val = 5;
	n[4]->val = 1;
	n[5]->val = 7;
	n[6]->val = 3;
	Solution slt;
	head = slt.insertionSortList(head);
	return 0;
}