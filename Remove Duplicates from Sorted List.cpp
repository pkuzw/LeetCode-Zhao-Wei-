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

///@date	2015.08.26
///@version	2.0

///@date	2015.12.09
///@version	1.1

///@date	2016.04.30
///@version	1.2

#include <iostream>
#include <queue>

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

///@note	1. 用队列来保存其中不重复的元素，然后再将它们逐个串起来；
//			2. 时间复杂度为O(n)，空间复杂度为O(n)。
class Solution_v2 {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next)	return head;
		queue<ListNode*> que;
		ListNode* indx = head;
		while (indx)
		{
			if (que.empty() || indx->val != que.back()->val)		que.push(indx);
			indx = indx->next;
		}
		while (!que.empty())
		{
			indx = que.front();
			que.pop();
			indx->next = que.empty() ? nullptr : que.front();
		}
		return head;
	}
};

class Solution {
public:
	///@brief	给定一个有序链表，删除其中的重复出现的元素的多余部分，每个元素只能出现一次
	///@param	head	链表首元素
	///@return	返回链表的首元素
	///@note	1. 遍历；2. 遇到重复的元素跳过即可；3. 时间复杂度为O(n)，空间复杂度为O(1)，n为链表的元素数目。
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* indx = head;
		ListNode* nxt_indx = indx->next;
		while (nxt_indx) {
			if (indx->val == nxt_indx->val) {
				indx->next = nxt_indx->next;
				nxt_indx = indx->next;
			}
			else {
				indx = indx->next;
				nxt_indx = nxt_indx->next;
			}
		}
		return head;
	}
};

class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* indx = head;
		ListNode* indx_nxt = indx->next;
		while (indx_nxt) {
			if (indx->val == indx_nxt->val) {
				indx_nxt = indx_nxt->next;
				indx->next = indx_nxt;
			}
			else {
				indx = indx->next;
				indx_nxt = indx_nxt->next;
			}
		}
		return head;
	}
};

int main()
{
	ListNode* n[5];
	for (int i = 0; i != 5; i++)
		n[i] = new ListNode(i);			
	for (int i = 0; i != 4; i++)
		n[i]->next = n[i+1];
	n[0]->val = 1;
	n[1]->val = 1;
	n[2]->val = 2;
	n[3]->val = 3;
	n[4]->val = 3;
	Solution_v2 slt_v2;
	ListNode* rslt = slt_v2.deleteDuplicates(n[0]);

	Solution slt_v1_1;

	ListNode* head = new ListNode(1);
	Solution_v1 slt;
	for (int i = 2; i <= 5; i++)
	{
		slt.insertNode(head, i);
 		slt.insertNode(head, i);
 		slt.insertNode(head, i);
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


//	head = slt.deleteDuplicates(display);
	head = slt_v1_1.deleteDuplicates(display);
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