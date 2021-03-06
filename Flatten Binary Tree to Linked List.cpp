﻿///@file	Flatten Binary Tree to Linked List
/*
Given a binary tree, flatten it to a linked list in-place.

For example,
Given

			1
		   / \
		  2   5
		 / \   \
		3   4   6
The flattened tree should look like:
	1
	 \
	  2
	   \
		3
		 \
		  4
		   \
			5
			 \
			  6
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version 1.1

///@date	2016.01.06
///@version	2.0

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	将二叉树转换成每个节点只有右孩子的链表。链表的顺序按照二叉树先序排列。
	///@param	root	根节点
	///@return	无
	/* @note	先将二叉树转换成每个节点只有左孩子的链表，然后将该链表再转换成只有右孩子的形式。二者都是利用了DFS先序遍历的思想，
				时间复杂度为O(n)，空间复杂度为O(1)。*/
	void flatten(TreeNode* root) {		
		flattenLeftChild(root);
		reverseTree(root);
		return;
	}

private:
	///@brief	将二叉树转换成每个节点只有左孩子的链表
	///@param	root	根节点
	///@return	无
	void flattenLeftChild(TreeNode *root)
	{		
		if (root == nullptr)	return;

		first_leaf = root;	//	需要对first_leaf进行初始化，否则对于只有右子树的情形会指针越界

		if (root->left == nullptr && root->right == nullptr)
			first_leaf = root;	//	找到先序遍历的第一个叶节点
		
		if (root->left != nullptr)	//	如果有左孩子，就继续向后找
			flattenLeftChild(root->left);
		if (root->right != nullptr)	//	如果有右孩子，则将该右孩子移到第一个叶节点的左孩子处，并继续向下递归
		{
			first_leaf->left = root->right;
			flattenLeftChild(root->right);
			root->right = nullptr;	//	递归出来后要将右孩子置为空
		}
		return;
	}

	///@brief	将该链表转换成只有右孩子的形式
	///@param	root	根节点
	///@return	无
	void reverseTree(TreeNode *root)
	{
		if (root == nullptr)	return;

		if (root->left != nullptr)
		{
			root->right = root->left;
			reverseTree(root->left);
			root->left = nullptr;
		}
		return;
	}

	TreeNode* first_leaf;	//	记录先序遍历时第一个叶节点
};

class Solution_v1_1 {
public:
	void flatten(TreeNode* root) {
		preorderTraversal(root);
		reverse(root);
	}
private:
	void preorderTraversal(TreeNode* root)
	{
		if (!root)	return;
		first_leaf = root;
		if (!root->left && !root->right)		first_leaf = root;
	
		if (root->left)	preorderTraversal(root->left);
		if (root->right)
		{
			first_leaf->left = root->right;
			preorderTraversal(root->right);	
			root->right = nullptr;
		}
	}
	void reverse(TreeNode* root)
	{
		if (!root)	return;
		if (root->left)
		{
			root->right = root->left;
			reverse(root->left);
			root->left = nullptr;
		}
	}

	TreeNode* first_leaf;
};

class Solution {
public:
	///@brief	将二叉树压缩成扁平的只有右孩子的单链表
	///@param	root	根节点
	///@return	无
	///@note	1. 递归；2. 将当前节点的左孩子置为空，将右孩子置为原先的左孩子，然后在新的右子树中寻找最右子节点，将其右孩子置为原本的右孩子即可。
	void flatten(TreeNode* root) {
		helper(root);
	}

	///@brief	递归辅助函数
	///@param	root	根节点
	///@return	返回新的二叉树根节点
	TreeNode* helper(TreeNode* root) {
		if (!root)	return root;
		TreeNode* cur = root;
		TreeNode* left = helper(root->left);
		TreeNode* right = helper(root->right);

		if (left) {
			cur->left = nullptr;
			cur->right = left;
			while (cur->right)	cur = cur->right;
		}
		cur->right = right;
		return root;
	}
};

int main()
{
	TreeNode *root = new TreeNode(1);
	TreeNode *n1 = new TreeNode(1);
	TreeNode *n2 = new TreeNode(2);
	TreeNode *n3 = new TreeNode(3);
	TreeNode *n4 = new TreeNode(4);
	TreeNode *n5 = new TreeNode(5);
	TreeNode *n6 = new TreeNode(6);
	TreeNode *n7 = new TreeNode(7);

//	n1->left = n2;
	n1->right = n2;
	
// 	n2->left = n4;
 	n2->right = n3;
 	n3->left = n4;
 	n3->right = n5;
	n5->right = n6;

	root = n1;

	Solution slt;
	slt.flatten(root);

	return 0;
}