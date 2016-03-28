///@file	Largest BST Subtree
///@author	zhaowei
///@date	2016.03.28
///@version 1.0

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
	///@brief	寻找二叉树中的最大BST子树
	///@param	root	根节点
	///@return	返回最大BST子树的节点数目
	///@note	1. 递归；
	//			2. 时间复杂度为O(nlogn)。
	int largestBSTSubtree(TreeNode* root) {
		if (!root)	return 0;
		if (isValid(root, INT_MIN, INT_MAX))	return countNode(root);
		else	return max(largestBSTSubtree(root->left), largestBSTSubtree(root->right));
	}

	///@brief	计算二叉树的节点数目
	///@param	root	根节点
	///@return	返回以root为根节点的二叉树节点数目
	int countNode(TreeNode* root) {
		if (!root)	return 0;
		return 1 + countNode(root->left) + countNode(root->right);
	}

	///@brief	判断二叉树是否为BST
	///@param	root	根节点
	///@param	min_num	该二叉树的最小值
	///@param	max_num	该二叉树的最大值
	bool isValid(TreeNode* root, int min_num, int max_num) {
		if (!root)	return true;
		if (root->val > min_num && root->val < max_num)	
			return isValid(root->left, min_num, root->val) && isValid(root->right, root->val, max_num);
		else
			return false;
	}
};

int main() {
	return 0;
}