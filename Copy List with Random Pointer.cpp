///@file	Copy List with Random Pointer
/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the 

list or null.

Return a deep copy of the list. 
*/
///@author	zhaowei
///@date	2015.07.30
///@version	1.0

///@date	2015.08.21
///@version	1.1

///@date	2016.01.11
///@version	1.2

#include <iostream>
using namespace std;

struct RandomListNode {
	int label;
	RandomListNode *next, *random;
	RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution_v1 {
public:
	///@brief	构建一个新的链表，使得其与原链表一致
	///@param	head	原链表的首节点
	///@return	返回复制链表的首节点
	/* @note	在每一个原链表的节点后添加一个新结点，然后再断开其与原链表之间的连接即可。时间复杂度为O(n)，空间复杂度为O(1)。*/
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head)	return nullptr;

		RandomListNode* indx = head;
		RandomListNode* indx_next = head->next;
		while (indx)
		{	
			RandomListNode* new_node = new RandomListNode(indx->label);		// 给每个节点后插入一个新节点		
			indx->next = new_node;
			new_node->next = indx_next;		
			indx = indx_next;
			indx_next = indx_next ? indx_next->next : nullptr;
		}

		indx = head;
		while (indx)	//	设置新节点的random指针
		{
			RandomListNode* new_node = indx->next;
			if (indx->random)
				new_node->random = indx->random->next;
			indx = indx->next->next;
			new_node = new_node->next ? new_node->next->next : nullptr;
		}

		RandomListNode* new_head = head->next;
		indx = head;
		indx_next = head->next;
		while (indx)	//	断开新旧节点间的连接
		{
			indx->next = indx_next->next;
			indx_next->next = indx_next->next ? indx->next->next : nullptr;
			indx = indx->next;
			indx_next = indx_next ? indx_next->next : nullptr;
		}
		return new_head;
    }
};

class Solution {
public:
	///@brief	构建一个新的链表，使得其与原链表一致
	///@param	head	原链表的首节点
	///@return	返回复制链表的首节点
	/* @note	1. 在每一个原链表的节点后添加一个新结点，然后再断开其与原链表之间的连接即可；
				2. 在将一个节点后移至其后继节点时，只需判断该节点是否存在即可，不必判断其后继是否为nullptr；
				3. 在拷贝随机指针时，是指向原节点的随机指针的后继节点，这才是新节点的随机节点；
				4. 时间复杂度为O(n)，空间复杂度为O(1)。*/
	RandomListNode *copyRandomList(RandomListNode *head) {
		if (!head)	return nullptr;
		RandomListNode* indx = head;
		RandomListNode* indx_nxt = indx->next ? indx->next : nullptr;
		while (indx) {	//	复制每个节点
			RandomListNode* new_node = new RandomListNode(indx->label);
			indx->next = new_node;
			new_node->next = indx_nxt;
			indx = indx_nxt;
			indx_nxt = indx_nxt ? indx_nxt->next : nullptr;
		}

		indx = head;		
		while (indx) {	//	给新节点的随机指针赋值
			RandomListNode* new_node = indx->next;
			new_node->random = indx->random ? indx->random->next :nullptr;
			indx = new_node->next;
			new_node = new_node->next ? new_node->next->next : nullptr;
		}

		indx = head;
		indx_nxt = indx->next;
		RandomListNode* new_head = head->next;
		while (indx_nxt) {	//	断开新旧节点的连接
			indx->next = indx_nxt->next ? indx_nxt->next : nullptr;			
			indx = indx_nxt;
			indx_nxt = indx_nxt ? indx_nxt->next : nullptr;
		}
		return new_head;
	}
};

int main()
{
	
	RandomListNode* n[6];
	for (int i = 0; i != 6; i++)
	{
		n[i] = new RandomListNode(i);
		if (i >= 1)	
			n[i-1]->next = n[i];
	}
	n[2]->random = n[4];
	n[3]->random = n[1];
	RandomListNode* head = n[0];

	Solution slt;
	RandomListNode* new_head = slt.copyRandomList(head);
	return 0;
}