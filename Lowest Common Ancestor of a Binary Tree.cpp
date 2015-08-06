///@file	Lowest Common Ancestor of a Binary Tree
/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

_______3______
/              \
___5__          ___1__
/      \        /      \
6      _2       0       8
/  \
7   4

For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
*/
///@author	zhaowei
///@date	2015.07.26
///@version	1.0

///@date	2015.08.06
///@version	2.0

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
	///@brief	计算二叉树中的最低公共祖先（Lowest Common Ancestor, LCA）
	///@param	root	二叉树根节点
	///@param	p	子节点p
	///@param	q	子节点q
	///@return	返回p和q在二叉树中的最低公共祖先节点
	/* @note	如果某个节点就是p或q，则该节点就是它的最低公共祖先；如果某个节点的左右子树各含有p或q，那么该节点就是它们的最低公共祖先，否则就是它的左子树或者右子树。递归的向下遍历。
				时间复杂度为O(n)，空间复杂度为O(1)。*/
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == nullptr || p == nullptr || q == nullptr)	
			return nullptr;

		if (root == p || root == q)	//	如果某个节点就是p或q，则该节点就是它的最低公共祖先
			return root;

		TreeNode *lsub = lowestCommonAncestor(root->left, p, q);		//递归	
		TreeNode *rsub = lowestCommonAncestor(root->right, p, q);

		if (lsub != nullptr && rsub != nullptr)	//	如果某个节点的左右子树各含有p或q，那么该节点就是它们的最低公共祖先
			return root;
		else if (rsub == nullptr && lsub != nullptr)
			return lsub;
		else if (lsub == nullptr && rsub != nullptr)	//	否则就在其左子树或右子树
			return rsub;
		else
			return nullptr;
	}
};

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

	}
};

int main()
{
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
		n[i] = new TreeNode(i);

	n[1]->left = n[2];
	n[1]->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];
// 	n[4]->right = n[8];
// 	n[5]->right = n[9];
// 	n[7]->right = n[10];

	TreeNode *root = n[1];

	Solution slt;
	TreeNode *rslt = slt.lowestCommonAncestor(root, n[2], n[6]);
	return 0;
}