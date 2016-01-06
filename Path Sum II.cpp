///@file	Path Sum II
/*
Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
			5
		   / \
		  4   8
		 /   / \
		11  13  4
	   /  \    / \
	  7    2  5   1
return
[
[5,4,11,2],
[5,8,4,5]
]
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	1.1

///@date	2016.01.06
///@version	1.2

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
	///@brief	在二叉树中计算出每一条节点和为指定值的路径
	///@param	root	根节点
	///@param	sum		指定值
	///@return	返回所有和为指定值的节点数组
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<int> path;
		pathSum_Recur(root, sum, path);
		return paths;
	}

private:
	///@brief	递归的计算所有和为指定值的路径
	///@param	root	根节点
	///@param	sum		指定值
	///@return	无
	/* @note	递归的求解，利用前序遍历的思想，遇到节点就将其入队，如果找到了满足条件的路径，就加入结果数组，否则就出队。时间复杂度为O(n)，
				空间复杂度为O(n)。 */
	void pathSum_Recur(TreeNode* root, int sum, vector<int> &path)
	{
		if (root == nullptr)	return;

		path.push_back(root->val);
		if (root->val == sum && root->left == nullptr && root->right == nullptr)
			paths.push_back(path);
		
		if (root->left != nullptr)
			pathSum_Recur(root->left, sum-root->val, path);
		if (root->right != nullptr)
			pathSum_Recur(root->right, sum-root->val, path);

		path.pop_back();
		return;
	}

	vector<vector<int>> paths;
};

class Solution_v1_1 {
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<int> path;
		pathRecur(root, sum, path);
		return rslt;
	}
private:
	vector<vector<int>> rslt;
	void pathRecur(TreeNode* root, int sum, vector<int>& path)
	{
		if (!root)	return;
		path.push_back(root->val);
		if (root->val == sum && !root->left && !root->right)		rslt.push_back(path);
		if (root->left)		pathRecur(root->left, sum - root->val, path);
		if (root->right)		pathRecur(root->right, sum- root->val, path);
		path.pop_back();
	}
};

class Solution {
public:
	///@brief	计算出所有从根节点到叶子节点路径和为指定值的路径
	///@param	root	根节点
	///@param	sum		指定值
	///@return	返回所有可能的节点值数组
	///@note	1. 递归；2. 与"Path Sum"类似，可以用先序遍历来递归求解；3. 每当遍历到一个节点时就将其压入一条路径，然后递归调用其左右子树，
	//			目标值也要相应扣除该节点值；4. 当到达叶节点时恰好等于指定值，则将路径压入结果数组；5. 否则从路径中弹出节点值。
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> rslt;
		vector<int> path;
		helper(root, sum, path, rslt);
		return rslt;
	}

	///@brief	递归辅助函数
	///@param	root	根节点
	///@param	sum		指定值
	///@param	path	路径
	///@param	rlst	结果数组
	///@return	无
	void helper(TreeNode* root, int sum, vector<int>& path, vector<vector<int>>& rslt) {
		if (!root)	return;

		path.push_back(root->val);

		if (root->val == sum && !root->left && !root->right)		rslt.push_back(path);		
		helper(root->left, sum - root->val, path, rslt);
		helper(root->right, sum - root->val, path, rslt);
		path.pop_back();
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
	n[6]->val = 1;
	n[8]->val = -1;
	root->left = n[2];
	root->right = n[3];
	n[2]->left = n[4];
	n[2]->right = n[5];
	n[3]->left = n[6];
	n[4]->left = n[8];

	Solution_v1 slt_v1;
	vector<vector<int>> rslt1 = slt_v1.pathSum(root, -1);
	Solution slt;
	vector<vector<int>> rslt = slt.pathSum(root, -1);
	return 0;
}