///@file	Construct Binary Tree from Preorder and Inorder Traversal
/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/
///@author	zhaowei
///@date	2015.07.22
///@version	1.0

#include <vector>
#include <algorithm>	//	find
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	///@brief	已知二叉树的前序序列和中序序列，构建二叉树。假设二叉树中元素均不重复
	///@param	preorder	前序序列
	///@param	inorder		中序序列
	///@return	返回构造的二叉树树根
	/* @note	通过观察可知，前序序列的首节点是根节点，先找到根节点，然后在中序序列中找到根节点的位置，在中序序列中的根节点之前的元素
				是左子树节点的中序序列，根节点之后的元素是右子树节点的中序序列。然后通过vector的构造函数来截去出前序、中序序列的左右子树
				部分，再递归调用建树函数即可。时间复杂度为O(n)，空间复杂度为O(2^n)。
	*/
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() && inorder.empty())	return nullptr;	//	如果前中序序列为空，直接返回空指针

		TreeNode *root = new TreeNode(preorder[0]);	//	根节点为前序序列的首元素
		vector<int>::iterator it = find(inorder.begin(), inorder.end(), preorder[0]);	//	找到中序序列的根节点位置，时间复杂度为O(n)
		
		vector<int> inorder_lsub(inorder.begin(), it);	//	利用vector的构造函数来截取左右子树的前中序序列，截取参数应为左闭右开区间
		vector<int> preorder_lsub(preorder.begin()+1, preorder.begin()+inorder_lsub.size()+1);
		
		++it;
		vector<int> inorder_rsub(it, inorder.end());
		vector<int> preorder_rsub(preorder.end()-inorder_rsub.size(), preorder.end());

		root->left = buildTree(preorder_lsub, inorder_lsub);	//	递归调用构建二叉树函数
		root->right = buildTree(preorder_rsub, inorder_rsub);

		return root;
	}
};

int main()
{
	vector<int> preorder, inorder;
	int preodr[7] = {1,2,4,5,3,6,7};
	int inodr[7] = {1,4,2,6,3,7,5};
	for (int i = 0; i != 7; i++)
	{
		preorder.push_back(preodr[i]);
		inorder.push_back(inodr[i]);
	}

	Solution slt;
	TreeNode *rslt = slt.buildTree(preorder, inorder);
	return 0;
}