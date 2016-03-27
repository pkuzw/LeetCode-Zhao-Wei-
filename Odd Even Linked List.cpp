///@file	Odd Even Linked List
///@author	zhaowei
///@date	2016.03.27
///@version	1.0

#include <cstdlib>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	///@brief	将单链表的奇数位放在最前面，后面是偶数位节点，相对顺序不能变。要求时间复杂度为O(n)，空间复杂度为O(1)
	///@param	head	链表头节点
	///@return	返回新链表的头节点
	///@note	1. 建立两个子链表的表头，分别是奇数位节点和偶数位节点，交叉向后移动，过程中注意判定是否存在该节点及其后继节点。
	//			2. 时间复杂度为O(n)，空间复杂度为O(1).

	ListNode* oddEvenList(ListNode* head) {
		if (!head || !head->next)	return head;
		ListNode* odd_head = head;
		ListNode* even_head = head->next;
		ListNode* odd_indx = head;
		ListNode* even_indx = head->next;
		while (odd_indx->next && even_indx->next) {
			odd_indx->next = even_indx && even_indx->next ? even_indx->next : nullptr;
			odd_indx = odd_indx->next ? odd_indx->next : odd_indx;
			even_indx->next = odd_indx && odd_indx->next ? odd_indx->next : nullptr;
			even_indx = even_indx->next ? even_indx->next : even_indx;
		}
		odd_indx->next = even_head;
		return odd_head;
	}
};

int main() {
	ListNode* n[7];
	for (int i = 0; i != 7; i++)	n[i] = new ListNode(i);
	for (int i = 0; i != 6; i++)	n[i]->next = n[i+1];
	Solution slt;
	ListNode* rslt = slt.oddEvenList(n[0]);
	return 0;
}