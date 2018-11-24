///@file	Partition List
/*
Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
///@author	zhaowei
///@date	2015.07.15
///@version	1.0

///@date	2015.08.26
///@version	2.0

///@date	2015.12.10
///@version	1.1

///@date	2016.05.02
///@version	1.2

///@date    November 24, 2018
///@version 2.1

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
	///@brief	在链表中根据指定值将链表改变为指定值左侧的元素均小于指定值，右侧的元素均不小于指定值。左右两侧的元素顺序要保持不变
	///@param	head	链表头
	///@param	x		轴值
	///@return	返回改变后的链表表头
	///@note	此题是快速排序中的划分步骤。存储数据的结构由数组变成了链表。用两个链表分别保存比轴值小的元素和比轴值大的元素，然后再将二者合并。
	//			时间复杂度为O(n)，空间复杂度为O(n)。
	ListNode* partition(ListNode* head, int x) {
		if (head == nullptr)
		{
			return head;
		}
		ListNode *lpart = new ListNode(INT_MAX);	//	比轴值小的元素组成的链表
		ListNode *nlpart = new ListNode(INT_MAX);	//	不比轴值小的元素组成的链表

		ListNode *indx = head;
		ListNode *lstart = lpart;
		ListNode *nlstart = nlpart;
		while (indx != nullptr)
		{
			if (indx->val < x)
			{
				lpart->next = indx;	
				lpart = lpart->next;
			}
			else
			{
				nlpart->next = indx;
				nlpart = nlpart->next;
			}
			indx = indx->next;
		}
		lpart->next = nlstart->next;
		nlpart->next = nullptr;

		return lstart->next;
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

//@note	利用队列来维护大于等于x值和小于x值的两部分，然后再将它们依次弹出。
//		空间复杂度为O(n)
class Solution_v2 {
public:
	ListNode* partition(ListNode* head, int x) {
		if (!head || !head->next)	return head;
		queue<ListNode*> que1, que2;
		ListNode* indx = head;
		while (indx)
		{
			if (indx->val < x)	que1.push(indx);
			else				que2.push(indx);
			indx = indx->next;
		}
		ListNode* new_head = que1.empty() ? que2.front() : que1.front();
		que1.empty() ? que2.pop() : que1.pop();
		indx = new_head;
		while (!que1.empty())
		{
			indx->next = que1.front();
			que1.pop();
			indx = indx->next;
		}
		while (!que2.empty())
		{

			indx->next = que2.front();
			que2.pop();
			indx = indx->next;
		}
		indx->next = nullptr;
		return new_head;
	}
};

class Solution_v1_1 {
public:
	///@brief	将链表划分成两部分，左半部分小于指定值x，有半部分大于等于x
	///@param	head	原始链表
	///@param	x		指定值
	///@return	返回划分好的链表起点
	///@note	1. 枚举；
	//			2. 遍历链表，如果小于x，则将其归为前半部分链表，如果大于等于x，则将其归为后半部分链表；
	//			3. 然后将前后两部分连接起来；
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* partition(ListNode* head, int x) {
		if (!head)	return nullptr;
		ListNode* lhead = new ListNode(INT_MAX);
		ListNode* rhead = new ListNode(INT_MAX);
		ListNode* indx = head;
		ListNode* lindx = lhead;
		ListNode* rindx = rhead;
		while (indx) {
			if (indx->val < x) {
				lindx->next = indx;
				lindx = lindx->next;
			}
			else {
				rindx->next = indx;
				rindx = rindx->next;
			}
			indx = indx->next;
		}
		lindx->next = rhead->next;
		rindx->next = nullptr;
		return lhead->next;
	}
};

class Solution {
public:
    ///@brief   给定一个链表和给定值，使得所有小于该值的节点都位于该值之前，所有大于等于该值的节点都位于该值之后。
    ///@param   head    链表表头
    ///@param   x       给定值
    ///@return  返回怀分后的链表表头。
	ListNode* partition(ListNode* head, int x) {
        
	}
};

int main()
{
	Solution_v1 slt_v1;
	ListNode* head = new ListNode(1);
	slt_v1.insertNode(head, 1);
 	slt_v1.insertNode(head, 3);
 	slt_v1.insertNode(head, 2);
 	slt_v1.insertNode(head, 5);
 	slt_v1.insertNode(head, 2);

// 	
// 	ListNode* rslt = slt_v1.partition(head);
	Solution slt;	
	ListNode* display = head;
	head = slt.partition(display, 3);

	return 0;
}
