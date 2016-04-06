///@file	Reverse Nodes in k-Group
/*			Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

			If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

			You may not alter the values in the nodes, only nodes itself may be changed.

			Only constant memory is allowed.

			For example,
			Given this linked list: 1->2->3->4->5

			For k = 2, you should return: 2->1->4->3->5

			For k = 3, you should return: 3->2->1->4->5
*/
///@author	zhaowei
///@date	2015.06.10
///@version 1.0

///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@versin	2.1

///@date	2016.04.06
///@version	2.2

#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution_v1
{
public:
	///@brief	将链表按照每组k个的长度在组内进行反转
	///@param	head	链表头
	///@param	k		分组长度
	///@return	返回翻转后的链表头
	///@author	zhaowei
	///@date	2015.06.10
	///@note	利用Swap Nodes in Pairs题中的思想，为组内的每个元素申请一个临时变量进行保存，然后在组内进行反转。
	//			另外，需要在每次翻转后判断剩余的元素是否足够分组。
	ListNode* reverseKGroup(ListNode* head, int k) 
	{
		if (head == nullptr || k == 1)
		{
			return head;
		}

		ListNode node(0);
		node.next = head;
		ListNode *l = head;
		ListNode **t = new ListNode* [k];	//	动态临时指针数组
		bool flag = false;					//	标记新链表的首节点

		while (l)
		{			
			ListNode* nextGroup = nextKNode(l, k);	//	进入新的一组
			if (l == nextGroup)	//	如果剩余元素不够新的一组，直接返回新链表的首结点
			{
				return node.next;				
			}
			else
			{
				if (!flag)
				{
					ListNode* newHead = nextKNode(l, k-1);	//	更新新链表的首节点，只需更改一次。
					node.next = newHead;
					flag = true;
				}

				for (int i = 0; i != k; i++)
				{
					t[i] = l;
					l = l->next;
				}
				
				for (int i = k-1; i != 0; i--)	//	反转组内元素
				{
					t[i]->next = t[i-1];
				}

				ListNode *reverseNextGroupHead = nextKNode(l, k-1);	//	翻转后的下一组首节点
				
				if (reverseNextGroupHead == nullptr)	//	需要注意尾结点的next为空，也会被计算在剩余元素是否能够组成一组当中。此时需要单独处理
				{
					t[0]->next = l;
				}
				else
					t[0]->next = reverseNextGroupHead;
			}
		}
		delete []t;
		return node.next;
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
private:
	///@brief	寻找当前节点后的第k个节点
	///@param	node	当前节点
	///@param	k		当前节点向后的个数
	///@return	如果当前节点后的第k个节点存在，则返回该节点；否则返回当前节点
	ListNode* nextKNode(ListNode *node, const int k)
	{
		int cnt = 0;
		if (node == nullptr)	
		{
			return node;
		}

		ListNode *l = node;
		while (l && cnt != k)
		{
			l = l->next;
			cnt++;
		}
		return cnt == k ? l : node;
	}
};

class Solution_v2 {
public:
    ///@brief   翻转指定长度小组内的元素
	///@param	head	链表首节点
	///@param	k		翻转的小组长度
	///@return	返回翻转后的链表首节点
	///@note	1. 需要设置一个首节点的前驱节点来返回翻转后的首节点；
	//			2. 中间主要的计算部分依赖翻转函数来完成；
	//			3. 通过设置一个计数器来计算是否满足到达小组的长度；
	//			4. 时间复杂度为O(n)，空间复杂度为O(1)。
    ListNode *reverseKGroup(ListNode *head, int k) {
		if (!head || !head->next || k == 1)	return head;
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		ListNode* pre = dummy;
		ListNode* cur = head;
		int i = 0;	//	计数器
		while (cur) {
			i++;
			if (i % k)	
				cur = cur->next;
			else {
				pre = reverseOneGroup(pre, cur->next);
				cur = pre->next;
			}
		}
		return dummy->next;
    }
    
    ///@brief   翻转pre之后和next之前的元素，即一个小组内的元素
	///@param	pre		一个小组在未翻转之前的首元素的前驱节点
	///@param	next	一个小组在未翻转之前的末元素的后继节点
	///@return	返回翻转后的组内新尾结点
	///@note	需要一个变量记录翻转后的新尾结点，还需要一个变量保存当前节点的前驱节点，另外一个变量遍历组内元素。时间复杂度为O(n)，空间复杂度为O(1)。
    ListNode *reverseOneGroup(ListNode *pre, ListNode *next) {
		ListNode* last = pre->next;	//	翻转后的新尾元素
		ListNode* cur = last->next;	//	当前元素
		while (cur != next) {
			last->next = cur->next;	
			cur->next = pre->next;
			pre->next = cur;
			cur = last->next;
		}
		return last;
    }
};

class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (!head || !head->next || k == 1)	return head;
		int cnt = 0;
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		ListNode* cur = head;
		ListNode* pre = dummy;
		while (cur) {
			cnt++;
			if (cnt % k)	cur = cur->next;			
			else {
				pre = reverseList(pre, cur->next);
				cur = pre->next;
			}
		}
		return dummy->next;
	}

	ListNode* reverseList(ListNode* pre, ListNode* tail) {
		ListNode* last = pre->next;
		ListNode* cur = last->next;
		while (cur != tail) {
			last->next = cur->next;
			cur->next = pre->next;
			pre->next = cur;
			cur = last->next;
		}
		return last;
	}
};

int main()
{
	ListNode* l2 = nullptr;
	ListNode* l1 = new ListNode(1);
	//ListNode* l2 = new ListNode(3);
	Solution_v1 slt_v1;
	for (int i = 2; i <= 2; i++)
	{
		slt_v1.insertNode(l1, i);
		//slt.insertNode(l2, i + 1);
	}

	int k = 2;
	Solution slt;
	ListNode* head = slt.reverseKGroup(l1, k);

	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}