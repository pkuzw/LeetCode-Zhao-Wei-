///@file	Binary Tree Preorder Traversal
/*
Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
     \
      2
     /
    3
return [1,2,3].

Note: Recursive solution is trivial, could you do it iteratively?
*/

///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.20
///@version	2.0

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
	///@brief	前序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回前序遍历的数组
	/* @note	递归。时间复杂度为O(n)，空间复杂度为O(n)。*/
	vector<int> preorderTraversal(TreeNode* root) {
		preOrder(root);
		return pre_seq;
	}

private:
	///@brief	前序遍历二叉树
	///@param	root	二叉树树根
	///@return	无
	void preOrder(TreeNode *root)
	{
		if (root == nullptr)	return;

		pre_seq.push_back(root->val);

		if (root->left != nullptr)
			preOrder(root->left);
		if (root->right != nullptr)
			preOrder(root->right);		
		return;
	}

	vector<int> pre_seq;	//	后序遍历的节点数组
};

class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		preorderTraversal_Recur(root);
		return rslt;
	}
private:
	vector<int> rslt;
	void preorderTraversal_Recur(TreeNode* root)
	{
		if (!root)	return;
		rslt.push_back(root->val);
		if (root->left)		preorderTraversal_Recur(root->left);
		if (root->right)		preorderTraversal_Recur(root->right);
	}
};

int main()
{
	TreeNode* n[20];
	for (int i = 0; i != 20; i++)
		n[i] = new TreeNode(i);

	n[1]->left = n[2];
	n[1]->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[3]->right = n[7];

	Solution slt;
	vector<int> rslt = slt.preorderTraversal(n[1]);
	return 0;
}