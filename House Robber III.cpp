///@file	House Robber III
///@author	zhaowei
///@date	2016.03.29
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
	///@brief	给定一棵二叉树，求不相邻的节点的最大和
	///@param	root	根节点
	///@return	返回最大和
	///@note	1. dfs
	//			2. 对每个节点来说，都有两个值，一个是选择该点的最大和，另一个是不选择该点的最大和	
	int rob(TreeNode* root) {
		vector<int> rslt = dfs(root);
		return max(rslt[0], rslt[1]);
	}

	///@brief	递归辅助函数
	///@param	root	根节点
	///@return	返回选择或者不选择root节点的最大和
	vector<int> dfs(TreeNode* root) {
		if (!root)	return vector<int>(2, 0);
		vector<int> left = dfs(root->left);
		vector<int> right = dfs(root->right);
		vector<int> rslt(2, 0);
		rslt[0] = root->val + left[1] + right[1];	//val[0]：选择该点，val[1]：不选择该点
		rslt[1] = max(left[0], left[1]) + max(right[0], right[1]);
		return rslt;
	}
};

int main() {
	return 0;
}