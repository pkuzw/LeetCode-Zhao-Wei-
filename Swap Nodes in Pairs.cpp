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

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *pre = dummy, *cur = head, *next = head->next;
        int i = 0;
        while (cur) {
            ++i;
            if (i % 2 == 0) {
                ListNode *last = cur->next;
                cur->next = next;
                last->next = pre->next;
                pre->next = last;
                pre = cur;
                cur = next;
                if (next) next = next->next;
            } else {
                if (next) next = next->next;
                else break;
            }
        }
        return dummy->next;
    }
};

int main()
{
	ListNode* l1 = new ListNode(4);
	//ListNode* l2 = new ListNode(3);
	Solution_v1 slt;
	for (int i = 2; i <= 2; i++)
	{
		slt.insertNode(l1, i*3 - 1);
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