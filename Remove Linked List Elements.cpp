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

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
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

int main()
{
	ListNode *head = new ListNode(1);
	ListNode *n1 = new ListNode(2);
	ListNode *n2 = new ListNode(3);
	ListNode *n3 = new ListNode(2);
	ListNode *n4 = new ListNode(3);
	ListNode *n5 = new ListNode(3);

	head->next = n1;
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n1->next = n2;

	Solution slt;
	ListNode *rslt = slt.removeElements(head, 1);

	return 0;
}