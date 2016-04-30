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

///@date	2015.08.26
///@version	2.0

///@date	2015.12.09
///@version	1.1

///@date	2016.04.30
///@version	3.0

#include <deque>
#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	删除已经排好序的链表中的重复节点
	///@param	head	链表表头
	///@return	返回删除重复元素后的链表头
	///@note	因为链表已经有序，故只需要遍历一遍，将重复元素删去即可。在删除时需要向前返回到不重复的元素为止。故需要在原始链表头加入一个首节点指针。时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* deleteDuplicates(ListNode* head) {
		if (head == nullptr)	//	如果输入链表本身就为空，则直接返回
		{
			return head;
		}
		ListNode *first = new ListNode(INT_MAX);	//	添加在原始链表头前的初始元素	
		first->next = head;

		ListNode *indx = head;	//	遍历循环变量
		ListNode *next_indx = indx->next;	//	循环变量的后一个元素
		ListNode *pre_indx = first;	//	循环变量的前一个元素

		bool flg = false;	//	标记pre_indx后面的节点indx是否存在过重复元素
		while (next_indx != nullptr)
		{
			if (indx->val == next_indx->val)
			{
				indx->next = next_indx->next;	//	删除除了第一个重复元素外的剩余剩余元素
				next_indx->next = nullptr;
				next_indx = indx->next;
				flg = true;	//	将标志置为true
			}
			else
			{
				if (flg)	//	说明该元素曾经也是重复元素
				{					
					pre_indx->next = next_indx;	//	删除该元素							
					flg = false;	// 恢复标志
				}
				else	//	如果该元素不是重复元素，则照常向后遍历
					pre_indx = pre_indx->next;								
				indx = indx->next;
				next_indx = next_indx->next;				
			}
		}
		if (flg)	// 除去最后一个元素曾经也是重复元素的情况
			pre_indx->next = next_indx;
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

class Solution_v2 {
public:
	///@note	时间复杂度为O(n)，空间复杂度为O(n)。不如算法1效率高。
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next)	return head;
		deque<ListNode*> que;
		ListNode* indx = head;		
		while (indx)
		{
			if (que.empty() || indx->val != que.back()->val)		que.push_back(indx);
			else
			{
				bool flg = false;	//	是否为重复元素
				while (indx && indx->val == que.back()->val)		//	在使用指针时要注意判定其是否有效
				{
					flg = true;
					indx = indx->next;
				}
				if (flg)
				{
					que.pop_back();
					continue;
				}
			}
			indx = indx->next;
		}
		if (que.empty())	return nullptr;

		ListNode* rslt = que.front();
		while (!que.empty())
		{
			indx = que.front();
			que.pop_front();
			indx->next = que.empty() ? nullptr : que.front();
		}
		return rslt;
	}
};

class Solution_v1_1 {
public:
	///@brief	删除有序链表中的重复元素
	///@param	head	链表表头
	///@return	返回去除重复元素的链表表头
	///note		1. 设置三个变量来删除重复元素，一个是循环变量indx，一个是indx的前驱元素pre_indx，另一个是indx的后继元素next_indx；
	//			2. 在删除时，先删除重复出现的后续元素，再删除第一次出现的元素；
	//			3. 要对遍历时最后一个元素是否是重复元素进行单独处理；
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* first = new ListNode(INT_MAX);
		first->next = head;
		ListNode* indx = head;
		ListNode* pre_indx = first;
		ListNode* next_indx = indx->next;
		bool flg = false;	//	 indx是否是重复元素
		while (next_indx) {
			if (indx->val == next_indx->val) {
				indx->next = next_indx->next;
				next_indx = indx->next;
				flg = true;
			}
			else {
				if (flg) {
					pre_indx->next = indx->next;
					indx = pre_indx;
					flg = false;
				}
				else {
					pre_indx = pre_indx->next;
				}
				indx = indx->next;
				next_indx = next_indx->next;
			}
		}
		if (flg) pre_indx->next = next_indx;
		return first->next;
	}
};

class Solution {
public:
	///@note	1. 设置虚拟头结点；
	//			2. 在遍历过程中找有重复的元素，找到其所有的重复区间，直接跳过；
	//			3. 时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* preHead = new ListNode(0);
		preHead->next = head;
		ListNode* i = head;
		ListNode* pre = preHead;
		while (i) {
			ListNode* nxt = i->next;
			if (nxt && i->val == nxt->val) {
				while (nxt && i->val == nxt->val)	nxt = nxt->next;
				pre->next = nxt;
				i = nxt;
			}
			else {
				pre = i;
				i = nxt;
			}
		}
		return preHead->next;
	}
};

int main()
{
	ListNode* head = new ListNode(1);
	Solution_v1 slt;	
	slt.insertNode(head, 1);
// 	slt.insertNode(head, 2);
// 	slt.insertNode(head, 2);
// 	slt.insertNode(head, 2);
// 	slt.insertNode(head, 3);
// 	slt.insertNode(head, 4);
// 	slt.insertNode(head, 4);
// 	slt.insertNode(head, 5);
// 	for (int i = 6; i <= 9; i++)
// 	{
// 		slt.insertNode(head, i);
// 		slt.insertNode(head, i);
// 		slt.insertNode(head, i);
// 	}
// 	slt.insertNode(head, 10);
// 	slt.insertNode(head, 11);

	//v2
	Solution slt_v2;
	ListNode* rslt = slt_v2.deleteDuplicates(head);

	ListNode* display = head;
	cout << "Before delete: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;


	head = slt.deleteDuplicates(head);
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