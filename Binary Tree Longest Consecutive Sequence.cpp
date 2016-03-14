///@file	Binary Tree Longest Consecutive Sequence
///@author	zhaowei
///@date	2016.03.14
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
	///@brief	计算二叉树中连续递增的子树序列
	///@param	root	根节点
	///@return	返回最长连续递增子树的路径长度
	///@note	1. 递归；
	//			2. dfs
	int longestConsecutive(TreeNode* root) {
		return dfs(root, nullptr, 0);
	}

	///@brief	递归辅助函数
	///@param	root	根节点
	///@param	parent	当前节点的父节点
	///@paramt	len		到达当前节点时的最长连续子树路径长度
	int dfs(TreeNode* root, TreeNode* parent, int len) {
		if (!root)	return len;
		len = (parent && root->val == parent->val + 1) ? len + 1 : 1;
		return max(len, max(dfs(root->left, root, len), dfs(root->right, root, len)));
	}
};

int main() {
	TreeNode* n[11];
	for (int i = 0; i <= 10; i++)	n[i] = new TreeNode(i);
	n[1]->left = n[3];
	n[1]->right = n[2];
	n[3]->left = n[4];
	n[2]->left = n[8];
	n[8]->right = n[9];
	n[9]->right = n[10];

	Solution slt;
	int rslt = slt.longestConsecutive(n[1]);
	return 0;
}