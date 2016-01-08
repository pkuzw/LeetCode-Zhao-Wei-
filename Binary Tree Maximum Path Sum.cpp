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

///@date	2015.08.22
///@version	1.1

///@date	2016.01.08
///@versin	1.2

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
	///@brief	计算二叉树中两个节点之间的最大路径和，起点和终点可以是任意节点
	///@param	root	根节点
	///@return	返回最大路径和
	/* @note	如果以某点p为起点的最大路径和sum(p) = max(p, p+sum(p->left), p+sum(p->right))，
				那么以该点为中间节点的最大路径和为sum(p->left)+sum(p->right)+p。
				故包含某点的最大路径和max_sum(p) = max(sum(p), sum(p->left)+sum(p->right)+p)。
				然后利用二叉树的后序遍历即可找到最大路径和。时间复杂度为O(n)，空间复杂度为O(n)。 */
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

///@note	在二叉树中，起始和终结点如果任意的话，那么对于每一个节点，可以分成两种情况，一种是以它为路径的起点，另一种是以它为路径的中间点。
//			如果某点是路径的起点，那么该路径的最大值应该为sum(p) = max(p, p + max(sum(p->left), sum(p->right)))；
//			如果以某点为路径的中间点，那么该路径的最大值应该为sum'(p) = p + sum(p->left) + sum(p->right)；
//			那么为了找到树中的最大路径，应该通过后序遍历树中的所有点，将最大值作为引用传入后续的递归参数，然后递归函数每次计算的是以该节点
//			为起点的最大路径值，并更新最大路径值。
class Solution_v1_1 {
public:
	int maxPathSum(TreeNode* root) {
		if (!root)	return 0;
		int max_path = INT_MIN;
		postorderTraversal(root, max_path);
		return max_path;
	}
private:
	int postorderTraversal(TreeNode* root, int& max_path)
	{
		int left_path = 0;
		int right_path = 0;
		if (root->left)		left_path = postorderTraversal(root->left, max_path);
		if (root->right)		right_path = postorderTraversal(root->right, max_path);
		int start_path = max(max(left_path, right_path) + root->val, root->val);
		int pass_path = left_path + root->val + right_path;
		max_path = max(max(start_path, pass_path), max_path);
		return start_path;
	}
};

class Solution {
public:
	///@brief	计算二叉树中两个节点之间的最大路径和，起点和终点可以是任意节点
	///@param	root	根节点
	///@return	返回最大路径和
	///@note	1. 递归版后序遍历二叉树中的每个节点；
	//			2. 对于二叉树中的每个节点，如果它是路径的起点，则sum(p) = max(p, p + max(sum(p->left), sum(p->right)))，
	//			   如果它是路径的中间点，则sum(p) = sum(p->left) + p + sum(p->right)。
	int maxPathSum(TreeNode* root) {
		if (!root)	return 0;
		int rslt = INT_MIN;
		helper(root, rslt);
		return rslt;
	}

	///@brief	后序遍历递归辅助函数
	///@param	root	节点
	///@param	rslt	路径最大值
	///@return	返回以当前节点为起始节点的路径最大值
	int helper(TreeNode* root, int& rslt) {
		if (!root)	return 0;
		int left = helper(root->left, rslt);
		int right = helper(root->right, rslt);
		int start_path = max(root->val, root->val + max(left, right));
		int pass_path = root->val + left + right;
		rslt = max(rslt, max(start_path, pass_path));
		return start_path;
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

	Solution_v1_1 slt1_1;
	int r1_1 = slt1_1.maxPathSum(n[1]);

	Solution slt;
	int rslt = slt.maxPathSum(n[1]);
	return 0;
}