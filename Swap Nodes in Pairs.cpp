///@file	Swap Nodes in Pairs
/*			Given a linked list, swap every two adjacent nodes and return its head.

			For example, Given 1->2->3->4, you should return the list as 2->1->4->3.

			Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/		
///@version 1.0
///@author	zhaowei
///@date	2015.06.10

///@date    2015.09.07
///@version 2.0

///@date	2015.09.22
///@version	2.1

///@date	2016.04.06
///@version	2.2

///@date    September 6, 2018
///@version 3.0

#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {};
};

class Solution_v1 {
public:

	///@brief	交换链表中相邻的两个元素
	///@param	head	链表首部
	///@return	返回交换后的链表首部
	///@author	zhaowei
	///@date	2015.06.10
	///@note	一共用4个临时变量，一个用于保存链表首部；一个用于保存下一次准备交换的两个元素的第一个元素；另外两个保存准备交换的两个元素。
	ListNode* swapPairs(ListNode* head) {

		if (head == nullptr)
		{
			return head;
		}

 		ListNode node(0);	//	保存链表头
 		node.next = head;
		ListNode *l = head;	//	循环变量
		ListNode *t1, *t2;	//	保存待交换的两个元素

		bool flag = false;	//	用于标记链表头是否需要改变，其只需要改变一次

		while (l->next)		//	对于奇数个元素，只交换前n-1个元素。最后一个留下来
		{
			t1 = l;
			t2 = l->next;

			if (!flag)	//	改变链表头.这段代码应该放在前面，如果放在后面，会有可能出现只有两个元素的链表，在中途break出去，运行不到这里
			{
				node.next = t2;
				flag = true;
			}

			if (l->next->next)
			{
				l = l->next->next;
			}
			else
			{
				t2->next = t1;
				t1->next = nullptr;
				break;
			}

			t2->next = t1;	//	交换
			if (l->next)
			{
				t1->next = l->next;
			}
			else
				t1->next = l;			
 		}
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
};

class Solution_v2 {
public:
	///@brief	将链表中两个相邻元素交换位置
	///@param	head	链表首节点
	///@return	返回交换相邻两元素的新链表节点
	///@note	1. 需要在链表头设置一个表首前驱节点，用来返回；
	//			2. 在每次交换时，通过计数器的累加值是否为偶数来判断是否需要交换两个相邻元素；
	//			3. 需要一个指针来保存交换前这对节点的后继节点；
	//			4. 还需要一个临时变量来保存交换的后一个节点；
	//			5. 前一个节点可以通过交换节点对的前驱节点来访问；
	//			6. 时间复杂度为O(n)，空间复杂度为O(1)。
	ListNode* swapPairs(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		ListNode* pre = dummy;
		ListNode* cur = head;
		ListNode* next = head->next;
		int i = 0;
		while (cur) {
			i++;
			if (i % 2) {
				if (next) next = next->next;
				else break;
			}
			else {
				ListNode* last = cur->next;
				cur->next = next;
				last->next = pre->next;
				pre->next = last;
				pre = cur;
				cur = cur->next;
				if (next) next = next->next;
			}
		}
		return dummy->next;
	}
};

class Solution {
public:
	ListNode* swapPairs(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* dummy = new ListNode(0);
		dummy->next = head;
		ListNode* pre = dummy;
		ListNode* cur = head;
		ListNode* next = cur->next;
		int cnt = 0;
		while (cur) {
			cnt++;
			if (cnt % 2) {
				if (next)	next = next->next;
				else	break;
			}
			else {
				ListNode* last = cur->next;
				cur->next = next;
				last->next = pre->next;
				pre->next = last;
				pre = cur;
				cur = cur->next;
				if (next)	next = next->next;
			}
		}
		return dummy->next;
	}
};

class Solution_v3 {
public:
    ///@brief   交换链表中的每两个相邻元素
    ///@param   head    链表头
    ///@return  返回交换后的链表表头
    ///@note    1. 创建一个指针变量作为表头的前驱节点，便于返回;
    //          2. 在交换过程中设置三个变量，pre保存两个相邻变量的前驱节点; cur1保存第一个节点; cur2保存第二个节点;
    //          3. 只有当两个cur1和cur2都有效时才交换，避免处理剩余的奇数个节点;
    //          4. 在交换的时候小心顺序就好;
    //          5. 时间复杂度为O(n)，空间复杂度为O(1)，其中n为链表的长度。
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next)   return head;
        ListNode* preHead = new ListNode(0);
        preHead->next = head;
        ListNode* cur1 = head, *cur2 = head->next, *pre = preHead;
        while (cur1 && cur2) {
            cur1->next = cur2->next;
            cur2->next = cur1;
            pre->next = cur2;
            pre = cur1;
            cur1 = cur1->next;
            cur2 = cur1 ? cur1->next : nullptr;
        }
        return preHead->next;
    }
};

int main()
{
	ListNode* l1 = new ListNode(1);
	//ListNode* l2 = new ListNode(3);
	Solution_v1 slt;
	for (int i = 2; i <= 8; i++)
	{
		slt.insertNode(l1, i);
		//slt.insertNode(l2, i + 1);
	}

	ListNode* head = slt.swapPairs(l1);

	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;
	return 0;
}
