///@file	Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
///@author	zhaowei
///@date	2015.06.08
///@version	1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@version	2.1

#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	归并两个已排好序的链表
	///@param	l1	链表1
	///@param	l2	链表2
	///@return	返回合并后的链表
	///@author	zhaowei
	///@date	2015.06.09
	///@note	依次比较两链表的首部节点，将较小的节点归入新链表，同时将其后移，时间复杂度O(n)，空间复杂度O(1)。

	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
	{
		ListNode node(0), *p = &node;
		while (l1 && l2)
		{
			if (l1->val < l2->val)
			{
				p->next = l1;	//	先设置p->next
				l1 = l1->next;	//	再移动l1
			}
			else
			{
				p->next = l2;	//	同上
				l2 = l2->next;
			}
			p = p->next;
		}
		if (l1)		//	如果l1多余出来，将其归入p的尾部
			p->next = l1;		
		else		//	如果l2多出来，同上
			p->next = l2;
		return node.next;
	}

	///@brief	将两个已经排好序的链表合二为一
	///@param	l1	链表1
	///@param	l2	链表2
	///@return	返回合并后的链表
	///@author	zhaowei
	///@date	2015.06.08
	///@note	对于每一个原始的节点都新建一个节点来保存，时间复杂度O(n)，空间复杂度O(n)。应该能够优化到空间复杂度O(1)才对。

	ListNode* mergeTwoLists_zw(ListNode* l1, ListNode* l2) 
	{
		ListNode* indx1 = l1, *indx2 = l2;
		ListNode* newList = new ListNode(0);	//	新链表的首指针
		ListNode* preNode = newList;
		int cnt = 0;
		while (indx1 != nullptr && indx2 != nullptr)
		{
			ListNode* tmp = new ListNode(0);	//	新结点

			if (indx1->val < indx2->val)
			{				
				tmp = indx1;
				preNode->next = tmp;
				indx1 = indx1->next;
			}
			else
			{
				tmp = indx2;
				preNode->next = tmp;
				indx2 = indx2->next;
			}
			preNode = tmp;
		}

		//	如果一个链表已经归并完毕，则将其剩余部分归并到另一个链表的后面即可。
		if (indx1 == nullptr)
		{
			preNode->next = indx2;
		}
		else if (indx2 == nullptr)
		{
			preNode->next = indx1;
		}
		return newList->next;		
	}

	///@brief	在新链表中插入节点
	///@param	head	新链表的首结点
	///@param	链表的值
	///@note	用于生成测试数据
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
	///@brief	归并两个已经排好序的链表
	///@param	l1	链表1
	///@param	l2	链表2
	///@return	返回已经排好序的链表表头
	///@note	建立一个排好序的链表表头的前驱节点，然后从两个链表的表首互相向后比较，如果遇到较小的节点，就将结果链表节点的后继指针指向它。对于剩余的链表，接上已经比较完毕的
	//			结果链表。时间复杂度为O(n)，空间复杂度为O(1)。
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
		ListNode* rslt = new ListNode(0);
		ListNode* cur = rslt;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				cur->next = l1;
				cur = cur->next;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				cur = cur->next;
				l2 = l2->next;
			}
		}
		if (!l1) cur->next = l2;
		else	 cur->next = l1;
		return rslt->next;
    }
};

int main()
{
	ListNode* l1 = new ListNode(4);
	ListNode* l2 = new ListNode(3);
 	Solution_v1 slt;
 	for (int i = 2; i <= 5; i++)
 	{
 		slt.insertNode(l1, i*3 - 1);
 		slt.insertNode(l2, i + 1);
 	}

	ListNode* head = slt.mergeTwoLists(l1, l2);

	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}