///@file	Rotate List
/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
*/
///@author	zhaowei
///@date	2015.07.07
///@version	1.0

///@date    2015.08.30
///@version 2.0

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
	///@brief	将一个链表向右移指定位数
	///@param	head	链表头
	///@param	k		移位数
	///@return	返回新链表的表头
	///@note	先计算出链表的长度，然后将链表组成一个循环链表，再找到新的表头位置，向后数出链表的长度，将循环链表恢复成单链表即可。
	//			时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* rotateRight(ListNode* head, int k) 
	{
		if (head == nullptr)
		{
			return head;
		}
		int list_size = 0;	//	计算链表的长度，以便对k求模
		ListNode *indx = head;

		while (indx != nullptr)	//	求链表长
		{
			list_size++;
			indx = indx->next;
		}
		if (k >= list_size)	//	对k求模
		{
			k %= list_size;
		}

		if (k == 0) return head;

		indx = head;
		while (indx->next != nullptr)
		{
			indx = indx->next;
		}
		indx->next = head;	//	将单链表变为循环链表

		int new_head = list_size - k;	//	新表头应为链表长度减去右移位数
		while (new_head != 0)	//	计算新表头
		{
			head = head->next;
			new_head--;
		}

		int cnt = list_size-1;	//	找到新的尾结点，断开循环链表，将其恢复成单链表
		indx = head;
		while (cnt != 0)
		{
			indx = indx->next;
			cnt--;
		}
		indx->next = NULL;

		return head;
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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!k || !head || !head->next)   return head;
        int len = 0;
        ListNode* indx = head;
        while (indx)
        {
            len++;
            indx = indx->next;
        }
        k = k % len;
        if (!k) return head;
        indx = head;
        int a = len - k;
        while (a > 1)
        {
            indx = indx->next;
            a--;
        }
        ListNode* b = indx->next;
        indx->next = nullptr;
        indx = b;
        while (indx->next)
            indx = indx->next;
        indx->next = head;
        return b;
    }
};

int main()
{
    
    Solution_v1 slt_v1;
	
	Solution slt;
	
    ListNode* n[5];
    for (int i = 0; i != 5; i++)
        n[i] = new ListNode(i+1);
    for (int i = 0; i != 4; i++)
        n[i]->next = n[i+1];

	int k = 1;
    ListNode* l = n[0];

    l = slt.rotateRight(l, k);
    
	return 0;
}