///@file	Convert Sorted List to Binary Search Tree
//			Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.0

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	将已经排好序的链表转换成高度平衡的BST树
	///@param	head	链表表头
	///@return	返回构造的高度平衡二叉搜索树的根节点
	/* @note	与"Convert Sorted Array to Binary Search Tree"类似，也是找链表中的中位数作为当前节点，其前半部分是左子树，右半部分是右子树。递归
				构造即可。时间复杂度为O(n)，空间复杂度为O(1)*/
    TreeNode* sortedListToBST(ListNode* head) {
        int len = 0;
		ListNode *indx = head;
		while(indx != nullptr)
		{
			indx = indx->next;
			len++;
		}
		return sortedListToBST_Recur(head, len);
    }

private:
	///@brief	递归构造高度平衡二叉搜索树
	///@param	head	链表表头
	///@param	len	待处理的链表长度
	///@return	返回构造的高度平衡二叉搜索树的根节点
	TreeNode* sortedListToBST_Recur(ListNode *head, int len)
	{
		if (len == 0)	return nullptr;

		int mid = len / 2;	//	中位数下标
		ListNode *indx = head;
		while (mid != 0)
		{
			indx = indx->next;
			mid--;
		}
		TreeNode *root = new TreeNode(indx->val);
		root->left = sortedListToBST_Recur(head, len/2);		//	因为int整型除法只保留整数部分，故当len为偶数时，中位数为后半部分的第一个，左半部分就是整个长度的一半。
		root->right = sortedListToBST_Recur(indx->next, (len-1)/2);

		return root;
	}
};

class Solution {
public:
	TreeNode* sortedListToBST(ListNode* head) {
		int len = 0;
		ListNode* indx = head;
		while (indx)
		{
			indx = indx->next;
			len++;
		}
		return convert(head, len);
	}
private:
	TreeNode* convert(ListNode* head, int len)
	{
		if (!len)	return nullptr;
		int m = len / 2;
		ListNode* mid = head;
		while (m--)
			mid = mid->next;		
		TreeNode* root = new TreeNode(mid->val);
		root->left = convert(head, len/2);
		root->right = convert(mid->next, (len-1)/2);
		return root;
	}
};

int main()
{
	ListNode* head = new ListNode(0);
	ListNode* ln[6];
	for (int i = 0; i != 6; i++)
	{
		ln[i] = new ListNode(i+1);
	}	
	for (int i = 0; i != 5; i++)
	{
		ln[i]->next = ln[i+1];
	}
	
	head = ln[0];
	head->next->next = nullptr;
	head->next->val = 3;

	Solution slt;
	TreeNode *root = slt.sortedListToBST(head);

	return 0;
}
