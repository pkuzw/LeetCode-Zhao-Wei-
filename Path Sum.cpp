///@file	Path Sum
/*Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values 
along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
		 5
		/ \
	   4   8
	  /   / \
	11  13   4
	/ \       \
   7   2       1
	return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.0

#include <iostream>
#include <queue>
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
	///@brief	判断二叉树中是否存在一条从根节点到叶节点的路径，路径上的各节点之和为指定值
	///@param	root	根节点
	///@param	sum		指定值
	///@return	如果存在该路径，则返回true；否则返回false
	/* @note	利用先序遍历的思想，对每条路径进行检查。需要注意，节点值有可能为负。
				时间复杂度为O(n)，空间复杂度为O(n)。*/
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == nullptr)	return false;

		if (root->val == sum && root->left == nullptr && root->right == nullptr)
			return true;
		else
		{
			if (root->left != nullptr)
				if (hasPathSum(root->left, sum-root->val))
					return true;
			if (root->right != nullptr)
				if (hasPathSum(root->right, sum-root->val))
					return true;			
		}		
		return false;
	}
};

class Solution {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (!root)	return false;
		if (root->val == sum && !root->left && !root->right)		return true;
		if (root->left && hasPathSum(root->left, sum - root->val))	return true;
		if (root->right && hasPathSum(root->right, sum - root->val))return true;
		return false;
	}
};

int main()
{
	TreeNode *root = new TreeNode(1);
	TreeNode *n[20];
	for (int i = 0; i != 20; i++)
	{
		n[i] = new TreeNode(i);
	}
	n[2]->val = -2;
	n[3]->val = -3;
	n[4]->val = 1;
	n[5]->val = 3;
	n[6]->val = -2;
	n[8]->val = -1;
 	root->left = n[2];
 	root->right = n[3];
 	n[2]->left = n[4];
 	n[2]->right = n[5];
 	n[3]->left = n[6];
 	n[4]->left = n[8];
	
// 	n[2]->val = -2;
// 	n[3]->val = -3;
// 	n[2]->right = n[3];

	Solution slt;
	bool rslt = slt.hasPathSum(root, -1);

	return 0;
}