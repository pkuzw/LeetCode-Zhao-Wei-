///@file	Kth Smallest Element in a BST
/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};

class Solution {
public:
	///@brief	计算二叉搜索树中的第k小的数
	///@param	root	根节点
	///@param	k		第k小的节点
	///@return	返回第k小的节点的值
	/* @note	因为二叉搜索树的中序遍历是有序的，所以只需要记录第k次递归即可获得第k小的数。时间复杂度为O(n)，空间复杂度为O(n)。*/
	int kthSmallest(TreeNode* root, int& k) {
		inOrder(root);
		return in_order[k-1];
	}
 
 private:
	 ///@brief	中序遍历二叉搜索树
	 ///@param	root	根节点
 	void inOrder(TreeNode* root)
	{
		if (root == nullptr)	return;

		if (root->left)
			inOrder(root->left);

		in_order.push_back(root->val);

		if (root->right)
			inOrder(root->right);
	}

	vector<int> in_order;	//	存放中序遍历的序列
};

int main()
{
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
		n[i] = new TreeNode(i);

	n[4]->left = n[2];
	n[4]->right = n[6];
	n[2]->left = n[1];
	n[2]->right = n[3];
	n[6]->left = n[5];
	n[6]->right = n[7];
	// 	n[4]->right = n[8];
	// 	n[5]->right = n[9];
	// 	n[7]->right = n[10];

	TreeNode *root = n[4];

	Solution slt;
	int k = 2;
	int rslt = slt.kthSmallest(root, k);
	return 0;
}