///@file	Construct Binary Tree from Preorder and Inorder Traversal
/*
Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/
///@author	zhaowei
///@date	2015.07.22
///@version	1.0

///@date	2015.08.25
///@version	2.0

///@date	2016.01.03
///@version	2.1

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

class Solution_v1 {
public:
	///@brief	已知二叉树的前序序列和中序序列，构建二叉树。假设二叉树中元素均不重复
	///@param	preorder	前序序列
	///@param	inorder		中序序列
	///@return	返回构造的二叉树树根
	/* @note	通过观察可知，前序序列的首节点是根节点，先找到根节点，然后在中序序列中找到根节点的位置，在中序序列中的根节点之前的元素
				是左子树节点的中序序列，根节点之后的元素是右子树节点的中序序列。然后通过vector的迭代器来标记出前序、中序序列的左右子树
				部分，再递归调用建树函数即可。时间复杂度为O(n)，空间复杂度为O(1)。
	*/
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return buildTree_Recur(preorder, preorder.begin(), preorder.end(), preorder.size(), inorder, inorder.begin(), inorder.end(), inorder.size());
	}

private:
	///@brief	通过前中序序列，递归构造二叉树
	///@param	preorder	前序序列
	///@param	pstart		前序序列的起始迭代器
	///@param	pend		前序序列的终止迭代器，末尾元素的后一位
	///@param	plen		前序序列的长度
	///@param	inorder		中序序列
	///@param	istart		中序序列的起始迭代器
	///@param	iend		中序序列的终止迭代器，末尾元素的后一位
	///@param	ilen		中序序列的长度
	///@return	返回构造的二叉树树根
	///@note	通过将利用的前中序序列范围作为参数传入进函数，能够将空间降为O(1)。
	TreeNode* buildTree_Recur(vector<int>& preorder, vector<int>::iterator pstart, vector<int>::iterator pend, vector<int>::size_type plen, vector<int>& inorder, vector<int>::iterator istart, vector<int>::iterator iend, vector<int>::size_type ilen) 
	{
		if (pstart == pend && istart == iend)	return nullptr;	//	如果前中序序列为空，直接返回空指针

		TreeNode *root = new TreeNode(*pstart);	//	根节点为前序序列的首元素
		vector<int>::iterator it = find(inorder.begin(), inorder.end(), *pstart);	//	找到中序序列的根节点位置，时间复杂度为O(n)

		vector<int>::size_type lsub_len = 0;	//	左子树节点数
		vector<int>::iterator it_tmp = istart;
		while (it_tmp != it)
		{
			lsub_len++;
			it_tmp++;
		}

		vector<int>::size_type rsub_len = 0;	//	右子树节点数
		it_tmp = it+1;
		while (it_tmp != iend)
		{
			rsub_len++;
			it_tmp++;
		}

		//	递归调用构建二叉树函数
		root->left = buildTree_Recur(preorder, pstart+1, pstart+lsub_len+1, lsub_len, inorder, istart, it, lsub_len);
		root->right = buildTree_Recur(preorder, pend-rsub_len, pend, rsub_len, inorder, it+1, iend, rsub_len);

		return root;
	}
};

class Solution {
public:
	///@brief	从前序和中序遍历序列重建二叉树
	///@param	preorder	前序遍历序列
	///@param	inorder		中序遍历序列
	///@return	返回重建的二叉树根节点
	///@note	1. 递归；2. 前序遍历的首元素为当前子树的根节点，中序遍历的中间节点为当前子树的根节点，中序遍历根节点左边的子序列为左子树节点，
	//			根节点右边的子序列为右子树节点；3. 先找中序遍历中当前子树的根节点，然后递归调用即可；4. 递归调用时对于preorder数组，因为第一个元素
	//			是根节点，故对于左子树来说，pleft传入的实参应该为pl + 1，pright传入的实参为pl + i - il，即从pl开始的左子树的数目，ileft传入的实参为
	//			il, iright传入的实参为i - 1，其中i为子树根节点；对于右子树来说，pleft传入的实参为pl + i - il + 1，即左子树的pright的后一位，
	//			pright传入的实参为pr；ileft传入的实参为i + 1，iright传入的实参为ir。
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return helper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);	
	}

	///@brief	重构二叉树的递归辅助函数
	///@param	preorder	前序遍历的节点值数组
	///@param	pl, pr		当前子树在前序遍历数组中的起始和终止下标
	///@param	inorder		中序遍历的节点数组
	///@param	il, ir		当前子树在中序遍历数组中的起始和终止下标
	///@return	返回重构的二叉树根节点
	TreeNode* helper(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int il, int ir) {
		if (pl > pr || il > ir)	return nullptr;
		TreeNode* root = new TreeNode(preorder[pl]);
		int i = il;
		while (i <= ir) {
			if (inorder[i] == preorder[pl])	break;
			i++;
		}
		root->left = helper(preorder, pl + 1, pl + i - il, inorder, il, i - 1);
		root->right = helper(preorder, pl + i - il + 1, pr, inorder, i + 1, ir);
		return root;
	}
};

int main()
{
	vector<int> preorder, inorder;
	int preodr[7] = {1,2,4,5,3,6,7};
	int inodr[7] = {4,2,5,1,6,3,7};
	for (int i = 0; i != 7; i++)
	{
		preorder.push_back(preodr[i]);
		inorder.push_back(inodr[i]);
	}

	Solution slt;
	TreeNode *rslt = slt.buildTree(preorder, inorder);
	return 0;
}