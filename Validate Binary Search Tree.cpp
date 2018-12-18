///@file	Validate Binary Search Tree
/*
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

///@date	2015.08.25
///@version	2.0

///@date	2015.12.31
///@version 2.1

///@date    December 17, 2018
///@version 2.2

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
	///@brief	判断二叉搜索树是否合法
	///@param	node	树节点
	///@param	min_num	最小值
	///@param	max_num	最大值
	///@return	如果以node为根的BST合法，则返回true；否则返回false
	/* @note	通过在递归时保存子树不能超过的上下限来判定是否满足BST的条件。另外还有一种思路：中序遍历的BST树应该是升序的。
	*/
    bool isValidBST(TreeNode* root) {
		if (root == nullptr)	return true;
		long long min_num = -21474836480;
		long long max_num = 21474836470;
		return isValidBST_Recursive(root, min_num, max_num);
	}

private:
	///@brief	递归的判断二叉搜索树是否合法
	///@param	node	树节点
	///@param	min_num	最小值
	///@param	max_num	最大值
	///@return	如果以node为根的BST合法，则返回true；否则返回false
	/* @note	递归实现：二叉搜索树应该满足左子树小于根节点，右子树大于根节点。所以用两个参数限制节点的值，一旦超过就判错
	*/
	bool isValidBST_Recursive(TreeNode *node, long long min_num, long long max_num)
	{		
		if (node == nullptr)	return true;

		if (node->val < max_num && node->val > min_num 
			&& isValidBST_Recursive(node->left, min_num, node->val)
			&& isValidBST_Recursive(node->right, node->val, max_num))
			return true;
		
		return false;
	}
};

class Solution {
public:
	///@brief	判断一棵二叉树是否满足BST的性质
	///@param	root	根节点
	///@return	如果这棵二叉树是BST，则返回true；否则返回false
	///@note	1. 递归；
    //          2. 通过遍历二叉树节点时其值是否满足上下限来进行判断；
    //          3. 上下限用LONG_MAX和LONG_MIN来做初始值，这样可以包含比INT_MAX和INT_MIN更大的值。
	bool isValidBST(TreeNode* root) {		
		return helper(root, LONG_MAX, LONG_MIN);
	}

	///@brief	递归判断一棵二叉树是否满足BST性质
	///@param	root	根节点
	///@param	max		节点值的上限
	///@param	min		节点值的下限
	///@return	如果这棵二叉树是BST，则返回true；否则返回false
	bool helper(TreeNode* root, long max, long min) {		
		if (!root || 
			(root->val < max && root->val > min &&
			helper(root->left, root->val, min) &&
			helper(root->right, max, root->val)))
			return true;
		return false;
	}
};

int main()
{
	TreeNode *root = new TreeNode(INT_MAX);
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
	{
		n[i] = new TreeNode(i);
	}
// 	root->left = n[4];
// 	n[4]->left = n[3];
// 	n[4]->right = n[8];
// 	root->right = n[10];
// 	n[10]->left = n[1];

	Solution slt;
	cout << slt.isValidBST(root) << endl;
	return 0;
}
