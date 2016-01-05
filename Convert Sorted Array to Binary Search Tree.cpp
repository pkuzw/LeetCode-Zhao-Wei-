///@file	Convert Sorted Array to Binary Search Tree
/*
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/
///@author	zhaowei
///@date	2015.07.23
///@version	1.0

///@date	2015.08.24
///@version	2.0

///@date	2016.01.05
///@version	2.1

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_v1 {
public:
	///@brief	给定一个已经按照升序排好序的数组，用它构建出一个高度平衡的二叉搜索树
	///@param	nums	数组
	///@return	返回一个高度平衡的二叉搜索树树根
	/* @note	因为二叉搜索树要求左子树节点小于当前节点，右子树节点大于当前节点。故递归的寻找数组的中位数，让它成为根节点。
				时间复杂度为O(n)，空间复杂度为O(1)。*/
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBST_Recur(nums, 0, nums.size());
	}

private:
	///@brief	递归的转换BST
	///@param	nums	有序数组
	///@param	start	开始转换的起始下标
	///@param	end	数组候选范围的末元素的后一位下标
	///@return	返回转换后的BST根节点	
	TreeNode* sortedArrayToBST_Recur(vector<int>& nums, vector<int>::size_type start, vector<int>::size_type end)
	{
		if (start == end)	return nullptr;

		vector<int>::size_type mid = (start + end) / 2;
		TreeNode *root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBST_Recur(nums, start, mid);
		root->right = sortedArrayToBST_Recur(nums, mid+1, end);

		return root;
	}
};

class Solution {
public:
	///@brief	给定一个已经按照升序排好序的数组，用它构建出一个高度平衡的二叉搜索树
	///@param	nums	数组
	///@return	返回一个高度平衡的二叉搜索树树根
	///@note	1. 递归；2. 因为BST的性质是左子树的节点都小于当前节点，右子树的节点都大于当前节点。故通过限定数组的左右边界，就能确定中位数是
	//			当前根节点；3. 时间复杂度为O(n)，空间复杂度为O(n)，其中n为节点数目。
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return helper(nums, 0, nums.size());
	}

	///@brief	辅助递归函数
	///@param	nums	排好序的数组
	///@param	start	数组的起始下标
	///@param	end		数组的终止下标
	///@return	返回当前子树的根节点
	TreeNode* helper(vector<int>& nums, int start, int end) {
		if (start >= end)	return nullptr;
		int mid = (start + end) / 2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = helper(nums, start, mid);
		root->right = helper(nums, mid + 1, end);
		return root;
	}
};

int main()
{	
	vector<int> nums;
	for (int i = 1; i <= 30 ; i++)
	{
		nums.push_back(i);
	}
	//nums.clear();
	Solution slt;
	TreeNode *root = slt.sortedArrayToBST(nums);

	return 0;
}