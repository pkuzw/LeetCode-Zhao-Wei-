///@file	Invert Binary Tree
/*
Invert a binary tree.

4
/   \
2     7
/ \   / \
1   3 6   9
to
4
/   \
7     2
/ \   / \
9   6 3   1
Trivia:
This problem was inspired by this original tweet by Max Howell:

Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.
*/
///@author	zhaowei
///@date	2015.07.24
///@version	1.0

///@date	2015.08.09
///@version	2.0
#include <algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution_v1 {
public:
	///@brief	翻转一棵二叉树
	///@param	root	二叉树的根节点
	///@return	返回翻转后的二叉树根节点
	/* @note	利用DFS的先序遍历，递归的转换左右孩子。时间复杂度为O(n)，空间复杂度为O(n)。*/
    TreeNode* invertTree(TreeNode* root) {
        invertTree_Recur(root);
		return root;
    }

private:
	///@brief	递归地翻转一棵二叉树
	///@param	root	二叉树的根节点
	///@return	返回翻转后的二叉树根节点
	void invertTree_Recur(TreeNode *root)
	{
		if (root == nullptr)	return;

		TreeNode *tmp = new TreeNode(0);
		tmp = root->left;
		root->left = root->right;
		root->right = tmp;

		if (root->left != nullptr)
			invertTree_Recur(root->left);
		if (root->right != nullptr)
			invertTree_Recur(root->right);

		return;
	}
};

class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (!root)	return root;
		swap(root->left, root->right);
		invertTree(root->left);		
		invertTree(root->right);
		return root;
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
	n[4]->right = n[8];
	n[5]->right = n[9];
	n[7]->right = n[10];

	TreeNode *root = n[1];

	Solution slt;
	TreeNode *rslt = slt.invertTree(root);
	return 0;
}