///@file	Lowest Common Ancestor of a Binary Search Tree
/*
Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

		_______6______
       /              \
    ___2__          ___8__
   /      \        /      \
  0       _4      7        9
 / \
3   5

For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
*/
///@author	zhaowei
///@date	2015.07.27
///@version	1.0

///@date	2015.08.06
///@version	2.0

///@date	2016.01.30
///@version	2.1

#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};

class Solution_v1 {
public:
	///@brief	找一个二叉搜索树的两个节点的最低公共祖先节点
	///@param	root	根节点
	///@param	p		子节点
	///@param	q		子节点
	///@return	返回p和q的最低公共祖先节点
	/* @note	首先想到的方法就是在二叉树中找最低公共祖先节点的方法。但是这种方法没有利用到BST的左小右大的性质，应该还有优化的空间。时间复杂度为O(n)，空间复杂度为O(n)。*/
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root || !p || !q)	return nullptr;

		if (root == p || root == q)	return root;

		TreeNode *lsub = lowestCommonAncestor(root->left, p, q);
		TreeNode *rsub = lowestCommonAncestor(root->right, p, q);

		if (lsub && rsub)	return root;

		return lsub ? lsub : rsub;			
	}	
};

class Solution_v2 {
public:
	TreeNode* lowestCommonAncestor_recur(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root)	return nullptr;

		if (root->val < min(p->val, q->val))		return lowestCommonAncestor_recur(root->right, p, q);
		else if (root->val > max(p->val, q->val)) return lowestCommonAncestor_recur(root->left, p, q);
		else return root;
	}

	TreeNode* lowestCommonAncestor_iter(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		if (!root)	return nullptr;

		while (true)
		{
			if (root->val < min(p->val, q->val))		root = root->right;
			else if (root->val > max(p->val, q->val))	root = root->left;
			else	break;
		}
		return root;
	}
};

class Solution_v2_1 {
public:
	///@note	1. 递归；
	//			2. 如果两节点都比当前节点小，则进入左子树；
	//			3. 如果两节点都比当前节点大，则进入右子树；
	//			4. 否则当前节点就是它们的最低公共祖先。
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root)	return nullptr;
		if (root->val > max(p->val, q->val))			return lowestCommonAncestor(root->left, p, q);
		else if (root->val < min(p->val, q->val))	return lowestCommonAncestor(root->right, p, q);
		else return root;
	}
};

class Solution {
public:
	///@note	1. 迭代实现；
	///			2. 原理与递归实现一样，通过一个while(1)循环来向下查找。
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root)	return nullptr;
		while (1) {
			if (root->val > max(p->val, q->val))			root = root->left;
			else if (root->val < min(p->val, q->val))	root = root->right;
			else	return root;
		}
	}
};

int main()
{
	return 0;
}