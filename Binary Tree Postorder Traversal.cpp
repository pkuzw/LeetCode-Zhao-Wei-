///@file	Binary Tree Postorder Traversal
/*
Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
	1
     \
	  2
     /
    3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	返回后序遍历的数组
	/* @note	递归。时间复杂度为O(n)，空间复杂度为O(n)。*/
    vector<int> postorderTraversal(TreeNode* root) {
        postOrder(root);
		return post_seq;
    }

private:
	///@brief	后序遍历二叉树
	///@param	root	二叉树树根
	///@return	无
	void postOrder(TreeNode *root)
	{
		if (root == nullptr)	return;

		if (root->left != nullptr)
			postOrder(root->left);
		if (root->right != nullptr)
			postOrder(root->right);

		post_seq.push_back(root->val);
	}

	vector<int> post_seq;	//	后序遍历的节点数组
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
	vector<int> rslt = slt.postorderTraversal(n[1]);
	return 0;
}