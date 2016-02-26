///@file	Closest Binary Search Tree Value
///@author	zhaowei
///@date	2016.02.26
///@version	1.0

#include <vector>
#include <algorithm>
using namespace std;
/**
 * Definition for a binary tree node.
**/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	寻找距离目标值最近的节点
	///@param	root	BST的根节点
	///@param	target	目标值，为双精度浮点数
	///@return	返回距离目标值最近的节点值
	///@note	1. 先中序遍历二叉树，得到有序的节点序列，然后通过二分查找寻找距离其最近的节点。
	//			2. 时间复杂度为O(n)。
	//			3. 应该能够有更好的办法，不需要遍历整个二叉树。
    int closestValue(TreeNode* root, double target) {
        vector<double> nums;
		inorderTraversal(root, nums);
		int l = 0, r = nums.size() - 1;
		if (target <= nums[l])	return (int)nums[l];
		else if (target >= nums[r])	return (int)nums[r];
		while (l <= r) {
			int mid = (l + r) / 2;
			if (target == nums[mid])	return (int)nums[mid];
			if (target < nums[mid])	r = mid;
			if (target > nums[mid])	l = mid;
			if (r - l == 1)		break;
		}
		return abs(nums[l] - target) <= abs(nums[r] - target) ? (int)nums[l] : (int)nums[l+1];
    }

	///@brief	中序遍历二叉树
	///@param	root	根节点
	///@param	中序序列
	void inorderTraversal(TreeNode* root, vector<double>& nums) {
		if (!root)	return;
		inorderTraversal(root->left, nums);
		nums.push_back((double)root->val);
		inorderTraversal(root->right, nums);
	}
};

int main() {
	TreeNode *n[7];
	for (int i = 0; i != 7; i++)	n[i] = new TreeNode(i);
	n[0]->val = 10;
	n[1]->val = 5;
	n[2]->val = 15;
	n[3]->val = 1;
	n[4]->val = 8;
	n[5]->val = 12;
	n[6]->val = 18;
	n[0]->left = n[1];
	n[0]->right = n[2];
	n[1]->left = n[3];
	n[1]->right = n[4];
	n[2]->left = n[5];
	n[2]->right = n[6];
	Solution slt;
	int r = slt.closestValue(n[0], 17.9);
	return 0;
}