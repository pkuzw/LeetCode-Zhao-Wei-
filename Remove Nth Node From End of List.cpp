/* @file	Given a linked list, remove the nth node from the end of list and return its head.

			For example,

			Given linked list: 1->2->3->4->5, and n = 2.

			After removing the second node from the end, the linked list becomes 1->2->3->5.
   
   @Note	Given n will always be valid. Try to do this in one pass.
*/
///@author	zhaowei
///@date	2015.06.05
///@version 1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.21
///@version	2.1

///@date	2016.04.05
///@version	2.2

///@date    July 17, 2018
///@version 2.3

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}	// 构造函数参数列表只有1个，所以在初始化ListNode时应该带一个参数val
};

class Solution_v1 {
public:
	///@brief	移除链表中距离尾结点n的节点
	///@param	head	链表首指针
	///@param	n	距离尾结点的距离
	///@return	返回链表的首指针
	///@note	若想要一遍遍历链表就找到距离末尾指定距离的节点，应该先算好该节点与迭代指针的距离，建立哨兵节点。
	//			当该节点为末尾节点时，则迭代指针所指向的节点就是应该删除的节点。
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		
		ListNode *r_node, *h_node, *pr_node;
		pr_node = new ListNode(INT_MIN);	// 标记迭代节点的前一个节点，用于删除目标节点，需要初始化
		pr_node->next = head;				
		h_node = head;
		r_node = h_node;

		for (int i = 0; i < n-1; i++)	// 找到迭代节点到末尾节点的距离, r_node相当于一个哨兵节点
		{				
			r_node = r_node->next;		
		}

		while (h_node != nullptr)		// 注意，这里不是h_node->next != nullptr，这样会漏掉最后一个末尾节点
		{			
			
			if (r_node->next == nullptr)	
			{
				pr_node->next = h_node->next;	// 删除指定结点			
				h_node->next = nullptr;
				if (pr_node->val == INT_MIN)	// 处理需要删除的节点是首节点的特殊情况
					head = pr_node->next;
				break;
			}
			pr_node = h_node;		// 遍历链表
			h_node = h_node->next;
			r_node = r_node->next;
		}
		return head;
	}

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
	///@brief	删除距离链表末尾n个节点的节点，要求只能遍历链表一遍
	///@param	head	链表首指针
	///@param	n		距离尾结点的距离（尾结点算作1）
	///@return	返回链表首节点
	///@note	如果只能遍历一遍，那么应该建立一个哨兵元素，该哨兵元素距离首节点的距离为n，当哨兵元素是链表尾节点时，就将遍历元素的后一个元素删除即可。时间复杂度为O(n)，空间复杂度为O(1)。
    ListNode* removeNthFromEnd(ListNode* head, int n) {
		if (!head)		return nullptr;
		ListNode* pre = head;	//	待删除元素的前驱节点
		ListNode* cur = head;	//	哨兵节点
		for (int i = 0; i != n; i++)	cur = cur->next;
		if (!cur)	return head->next;
		while (cur->next) {
			cur = cur->next;
			pre = pre->next;
		}
		pre->next = pre->next->next;
		return head;
    }
};

class Solution {
public:
    ///@brief   给定一个单向链表，在只能遍历一遍的条件下，删除距离尾结点为n的节点。
    ///@param   head    链表首节点
    ///@param   n       待删除节点到尾结点的距离
    ///@return  删除节点后返回链表表头
    ///@note    1. 先从表头开始往后数n个节点，然后开始遍历，当之前往后数n的那个节点到链表尾部时，删除当前节点即可。
    ///         2. 时间复杂度为O(m)，空间复杂度为O(1)，其中m为链表中的节点数目。
	ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head)  return head;
        ListNode* cur = head;
        ListNode* sentinel = head;
        for (int i = 0; i < n; i++) sentinel = sentinel->next;
        if (!sentinel)  return cur->next;
        while (sentinel->next) {
            cur = cur->next;
            sentinel = sentinel->next;
        }
        cur->next = cur->next->next;
        return head;
	}
};

int main()
{
	ListNode* head = new ListNode(1);
	Solution_v1 slt;
	for (int i = 2; i <= 5; i++)
	{
		slt.insertNode(head, i);
	}
	
	head = slt.removeNthFromEnd(head, 1);

	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}
