///@file	Binary Tree Maximum Path Sum
/*
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

		1
       / \
	  2   3

Return 6.
*/
///@author	zhaowei
///@date	2015.07.25
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
	///@brief	计算二叉树中两个节点之间的最大路径和，起点和终点可以是任意节点
	///@param	root	根节点
	///@return	返回最大路径和
	/* @note	如果以某点p为起点的最大路径和sum(p) = max(p, p+sum(p->left), p+sum(p->right))，那么以该点为中间节点的最大路径和为sum(p->left)+sum(p->right)+p。
				故包含某点的最大路径和max_sum(p) = max(sum(p), sum(p->left)+sum(p->right)+p)。然后利用二叉树的后序遍历即可找到最大路径和。时间复杂度为O(n)，空间复杂度为O(n)。 */
	int maxPathSum(TreeNode *root)
	{
		if (root == nullptr)	return 0;
		int ms_path = INT_MIN;	//	最大路径和
		int start_from_root = postOrder(root, ms_path);
		return ms_path;
	}

	///@brief	后序遍历每个节点，计算经过该节点的最大路径
	///@param	root	根节点
	///@param	ms_path	经过当前节点的最大路径值	
	///@return	返回以当前节点作为起点的最大路径值
	int postOrder(TreeNode *root, int& ms_path)
	{
		int this_ms_path = 0;	//	以当前root节点作为起始节点的最大路径值
		int left_path = 0, right_path = 0;	//	以左右孩子作为起点的最大路径值

		if (root->left != nullptr)
			left_path = postOrder(root->left, ms_path);
		
		if (root->right != nullptr)
			right_path = postOrder(root->right, ms_path);		

		//	节点值有可能为负
		this_ms_path = max(max(left_path, right_path) + root->val, root->val);

		if (max(this_ms_path, left_path + right_path + root->val) > ms_path)
			ms_path = max(this_ms_path, left_path + right_path + root->val);

		return this_ms_path;
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
	int rslt = slt.maxPathSum(n[1]);
	return 0;
}