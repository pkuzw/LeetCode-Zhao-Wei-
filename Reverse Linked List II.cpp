///@file	Reverse Linked List II
/*
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.
*/

///@author	zhaowei
///@date	2015.07.20
///@version	1.0

///@author	zhaowei
///@date	2015.07.21
///@version	1.1

///@date	2015.08.25
///@version	2.0

#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution_v1 {
public:
	///@brief	给定一个链表，在O(1)的空间复杂度，O(n)的时间复杂度的限制下反转指定范围的节点
	///@param	head	链表表头
	///@param	m	指定范围的起点
	///@param	n	指定范围的终点
	///@return	返回翻转后新链表的表头
	/* @note	先找到应该翻转的第一个节点和最后一个节点，然后调用翻转链表的方法（时间复杂度为O(n)，空间复杂度为O(n)，用到了栈，还是用到了
				额外的空间，不符合题意）。需要注意的是翻转的范围是否包含第一个节点，即表头，因为表头之前没有别的元素，跟其他情形不同，
				需要单独处理。
				时间复杂度为O(n)，空间复杂度为O(n)
	*/
    ListNode* reverseBetween_Space_O_n(ListNode* head, int m, int n) {
		if (head == nullptr || m == n)
		{
			return head;
		}
		ListNode *indx = head;
		while (m-- > 1)
			indx = indx->next;		
		ListNode *r_beg = indx;	//	反转的起始节点

		indx = head;
		while (n-- > 1)
			indx = indx->next;
		ListNode *r_end = indx;	//	反转的终止节点

		indx = head;
		if (indx == r_beg)	// 当反转的范围包括首元素时，因为它之前没有别的元素，需要单独处理
		{
			ListNode *after_range = r_end->next;
			r_end->next = nullptr;
			ListNode *rlist = reverseList_Space_O_n(head);
			ListNode *tmp = rlist;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			tmp->next = after_range;
			head = rlist;
		}
		else
		{
			while (indx->next != r_beg)
				indx = indx->next;
			indx->next = r_end->next;	//	将旋转的两侧先连起来，等反转后再重新连接
			r_end->next = nullptr;      

			ListNode *rlist = reverseList_Space_O_n(r_beg);	//	翻转中间的节点

			ListNode *tmp = rlist;	//	将翻转后的节点与之前的节点连接起来
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			tmp->next = indx->next;
			indx->next = rlist;			
		}			
		return head;
    }

	///@brief	给定一个链表，在O(1)的空间复杂度，只能遍历一遍链表的限制下反转指定范围的节点
	///@param	head	链表表头
	///@param	m	指定范围的起点
	///@param	n	指定范围的终点
	///@return	返回翻转后新链表的表头
	/* @note	找到开始翻转的首结点，利用两个临时变量，一个存储循环变量的前一个节点，另一个存储后一个节点，逐一进行翻转。时间复杂度为O(n)，
				空间复杂度为O(1)。 
	*/
    ListNode* reverseBetween_Space_O_1(ListNode* head, int m, int n) {
		if (head == nullptr || m == n)	return head;
		ListNode *indx = head;
		ListNode *pre_indx = head;
		ListNode *after_indx = new ListNode(0);

		int i = m, j = n;
						
		while (m-- > 1)
		{
			if (indx != nullptr)
			{
				pre_indx = indx;
				indx = indx->next;
			}			
		}
		ListNode *r_beg = indx;	//	翻转的首节点		
		ListNode *pre_r_beg = pre_indx;	//	翻转的首节点的前一个节点

		pre_indx = r_beg;
		indx = r_beg->next;
		if (indx != nullptr)
			after_indx = indx->next;
		
		int k = j-i;
		while (k-- > 0)
		{				
			indx->next = pre_indx;
			pre_indx = indx;
			indx = after_indx;
			if (after_indx != nullptr)
				after_indx = after_indx->next;
		}
		r_beg->next = indx;

		if (r_beg == head)	//	如果翻转的首节点是链表的首节点，则pre_r_beg也是head，此时直接返回pre_indx即可
			return pre_indx;
		
		pre_r_beg->next = pre_indx;
		return head;		
	}
	///@brief	插入新节点
	///@param	head	原链表的首节点
	///@param	val		新节点值
	///@return	无
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
	///@brief	翻转一个单链表
	///@param	head	链表表头
	///@return	返回翻转后的链表表头
	/* @note	从前到后依次翻转。利用两个临时变量，一个用来保存循环变量的前一个节点，另一个用来保存后一个节点，然后逐一翻转即可。
				时间复杂度为O(n)，空间复杂度为O(1)
	*/
	ListNode* reverseList_Space_O_1(ListNode *head)
	{
		if (head == nullptr)	return head;	//	边界情况
		ListNode *indx = head->next;
		ListNode *pre_indx = head;
		head->next = nullptr;

		ListNode *after_indx = new ListNode(0);
		if (indx != nullptr)	//	边界情况
			after_indx = indx->next;

		while (indx != nullptr)	//	翻转操作
		{			
			indx->next = pre_indx;	
			pre_indx = indx;
			indx = after_indx;

			if (after_indx != nullptr)
				after_indx = after_indx->next;			
		}
		return pre_indx;
	}

	///@brief	反转一个单链表
	///@param	head	链表表头
	///@return	返回翻转后的链表表头
	///@note	利用了栈来进行临时存储，空间复杂度为O(n)，时间复杂度为O(n)
	ListNode* reverseList_Space_O_n(ListNode *head)
	{
		ListNode *indx = head;		
		stack<ListNode*> s;
		while (indx->next != nullptr)
		{			
			s.push(indx);
			indx = indx->next;
		}
		ListNode *new_head = indx;
		while (!s.empty())
		{
			ListNode *tmp = s.top();
			s.pop();
			tmp->next = nullptr;

			indx->next = tmp;
			indx = indx->next;
		}
		indx->next = nullptr;
		return new_head;
	}
};

/*
1. 在链表表头处添加一个表头节点，以防起始翻转下标为首节点时无法找到起始遍历下标；
2. 主要的翻转代码还是利用两个后续指针依次进行翻转；
3. 用一个指针保存开始翻转的节点，该节点是翻转后的尾结点；
4. 时间复杂度为O(k)，空间复杂度为O(1)。
*/
class Solution {
public:
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (!head || !head->next || m >= n)	return head;
		ListNode* pre_head = new ListNode(INT_MAX);
		pre_head->next = head;
		ListNode* indx = head;		
		int i = 1;
		while (i < m)
		{
			indx = indx->next;			
			i++;
		}
		ListNode* indx_next = indx->next;
		ListNode* indx_next_next = indx_next;
		indx->next = nullptr;
		ListNode* r_tail = indx;
		while (i < n)
		{
			if (indx_next)	indx_next_next = indx_next->next;
			indx_next->next = indx;
			indx = indx_next;
			indx_next =  indx_next ? indx_next_next : indx_next;
			
			i++;
		}
		ListNode* pre = pre_head;
		int j = 1;
		while (j < m)
		{
			pre = pre->next;
			j++;
		}
		pre->next = indx;
		r_tail->next = indx_next;
		return pre_head->next;
	}
};

int main()
{
	Solution_v1 slt_v1;
	ListNode* head = new ListNode(1);
 	slt_v1.insertNode(head, 2);
//  	slt_v1.insertNode(head, 3);
//  	slt_v1.insertNode(head, 4);
//  	slt_v1.insertNode(head, 5);

	ListNode* display = head;
	cout << "Before: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;

//	head = slt.reverseList(display);

	
//	head = slt_v1.reverseBetween_Space_O_1(display, 1, 2);
	
	Solution slt;
	ListNode* rslt = slt.reverseBetween(display, 1, 2);
	cout << "After: ";
	while (head != nullptr)
	{
		cout << head->val;
		cout << ' ';
		head = head->next;
	}
	cout << endl;

	return 0;
}