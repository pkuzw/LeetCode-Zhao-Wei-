///@file	Sort List
//			Sort a linked list in O(n log n) time using constant space complexity.
///@author	zhaowei
///@date	2015.08.03
///@version	1.0

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
	///@brief	对链表进行O(nlogn)的排序，空间复杂度为O(1)。用归并排序实现。
	///@param	head	头节点
	///@return	返回排好序的链表头节点
	///@note	对链表不断进行折半划分，直到每个子链表只剩一个元素，然后再逐层归并。时间复杂度为O(nlogn)，空间复杂度为O(1)。
	ListNode* sortList(ListNode* head) {
		if (!head || !head->next)
			return head;

		ListNode *fast = head, *slow = head;	//快慢指针法查找中点
		while (fast->next && fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		fast = slow->next;
		slow->next = nullptr;
		slow = head;

		slow = sortList(slow);
		fast = sortList(fast);
		return merge(slow, fast);
	}
private:
	///@brief	归并函数
	///@param	head1	子链表1
	///@param	head2	子链表2
	///@return	返回归并好的链表
	ListNode* merge(ListNode* head1, ListNode* head2)
	{
		ListNode* rslt = new ListNode(INT_MIN);
		ListNode* cur = rslt;

		while (head1 && head2)
		{
			if (head1->val > head2->val)
			{
				cur->next = head2;
				head2 = head2->next;
			}
			else
			{
				cur->next = head1;
				head1 = head1->next;
			}
			cur = cur->next;
		}

		if (head1)	cur->next = head1;
		if (head2)	cur->next = head2;

		return rslt->next;
	}
};

class Solution {
public:
	ListNode* sortList(ListNode* head) {
		if (!head || !head->next) return head;
		ListNode* fast = head, *slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		fast = slow->next;
		slow->next = nullptr;
		slow = head;
		slow = sortList(slow);
		fast = sortList(fast);
		return merge(slow, fast);
	}
private:
	ListNode* merge(ListNode* head1, ListNode* head2) {
		ListNode* rslt = new ListNode(INT_MIN);
		ListNode* cur = rslt;
		while (head1 && head2) {
			if (head1->val < head2->val) {
				cur->next = head1;
				head1 = head1->next;
			}
			else {
				cur->next = head2;
				head2 = head2->next;
			}
			cur = cur->next;
		}
		cur->next = head1 ? head1 : head2;
		return rslt->next;
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
	head = slt.sortList(head);
	return 0;
}