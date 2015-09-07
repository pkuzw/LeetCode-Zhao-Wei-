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

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head->next) return NULL;
        ListNode *pre = head, *cur = head;
        for (int i = 0; i < n; ++i) cur = cur->next;
        if (!cur) return head->next;
        while (cur->next) {
            cur = cur->next;
            pre = pre->next;
        }
        pre->next = pre->next->next;
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