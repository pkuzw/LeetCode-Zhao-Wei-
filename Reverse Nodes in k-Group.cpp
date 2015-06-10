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

#include <iostream>
using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

class Solution 
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
	ListNode* reverseKGroup(ListNode* head, int k) {

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
				
				if (reverseNextGroupHead == nullptr)
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

int main()
{
	ListNode* l2 = nullptr;
	ListNode* l1 = new ListNode(1);
	//ListNode* l2 = new ListNode(3);
	Solution slt;
	for (int i = 2; i <= 7; i++)
	{
		slt.insertNode(l1, i);
		//slt.insertNode(l2, i + 1);
	}

	int k = 3;
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