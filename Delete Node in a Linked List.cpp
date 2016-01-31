///@file	Delete Node in a Linked List
/*
Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.

Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3, the linked list 

should become 1 -> 2 -> 4 after calling your function.
*/
///@author	zhaowei
///@date	2015.07.25
///@version	1.0

///@date	2015.08.06
///@version	1.1

///@date	2016.01.31
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
	///@brief	只给定一个链表的某个节点，删除该节点
	///@param	链表结点
	///@return	无
	/* @note	如果不是尾结点，那么将该节点用后一个节点覆盖掉，然后指向再后面一个节点；否则直接赋为nullptr。时间复杂度为O(1)，空间复杂度为O(1)。
				It's too tricky!!!*/
	void deleteNode(ListNode* node) {
		if (node == nullptr)	return;

		if (node->next != nullptr)
		{
			node->val = node->next->val;
			node->next = node->next->next;
		}
		else
			node = node->next;
			//memset(node, NULL, sizeof(ListNode*));
		return;
	}
};

class Solution {
public:
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;
	}
};

int main()
{
	ListNode* n[4];
	for (int i = 0; i != 4; i++)
	{
		n[i] = new ListNode(i);
		if (i > 0)
			n[i-1]->next = n[i];
	}

	Solution slt;
	slt.deleteNode(n[3]);
	ListNode *head = n[0];
	return 0;
}