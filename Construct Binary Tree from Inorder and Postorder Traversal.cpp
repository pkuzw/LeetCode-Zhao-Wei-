///@file	Construct Binary Tree from Inorder and Postorder Traversal
/*
Given inorder and postorder traversal of a tree, construct the binary tree.

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
	///@brief	已知二叉树的后序序列和中序序列，构建二叉树。假设二叉树中元素均不重复	
	///@param	inorder		中序序列
	///@param	postorder	后序序列
	///@return	返回构造的二叉树树根
	/* @note	通过观察可知，后序序列的末节点是根节点，先找到根节点，然后在中序序列中找到根节点的位置，在中序序列中的根节点之前的元素
				是左子树节点的中序序列，根节点之后的元素是右子树节点的中序序列。然后通过vector的迭代器来标记出后序、中序序列的左右子树
				部分，再递归调用建树函数即可。时间复杂度为O(n)，空间复杂度为O(1)。
	*/
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return buildTree_Recur(inorder, inorder.begin(), inorder.end(), inorder.size(), postorder, postorder.begin(), postorder.end(), postorder.size());
	}

private:
	///@brief	通过中序，后序序列，递归构造二叉树	
	///@param	inorder		中序序列
	///@param	istart		中序序列的起始迭代器
	///@param	iend		中序序列的终止迭代器，末尾元素的后一位
	///@param	ilen		中序序列的长度
	///@param	postorder	后序序列
	///@param	pstart		后序序列的起始迭代器
	///@param	pend		后序序列的终止迭代器，末尾元素的后一位
	///@param	plen		后序序列的长度
	///@return	返回构造的二叉树树根
	///@note	通过将利用的中序和后序序列范围作为参数传入进函数，能够将空间降为O(1)。
	TreeNode* buildTree_Recur(vector<int>& inorder, vector<int>::iterator istart, vector<int>::iterator iend, vector<int>::size_type ilen, vector<int>& postorder, vector<int>::iterator pstart, vector<int>::iterator pend, vector<int>::size_type plen) 
	{
		if (pstart == pend && istart == iend)	return nullptr;	//	如果中序和后序序列为空，直接返回空指针

		TreeNode *root = new TreeNode(*(pend-1));	//	根节点为后序序列的末元素
		vector<int>::iterator it = find(inorder.begin(), inorder.end(), *(pend-1));	//	找到中序序列的根节点位置，时间复杂度为O(n)

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
		root->left = buildTree_Recur(inorder, istart, it, lsub_len, postorder, pstart, pstart+lsub_len, lsub_len);
		root->right = buildTree_Recur(inorder, it+1, iend, rsub_len, postorder, pend-rsub_len-1, pend-1, rsub_len);

		return root;
	}
};

int main()
{
	vector<int> preorder, inorder, postorder;
	int preodr[7] = {1,2,4,5,3,6,7};	//	
	int postodr[7] = {4,6,7,3,5,2,1};// 4,5,2,6,7,3,1    4,6,7,3,5,2,1
	int inodr[7] = {1,4,2,6,3,7,5};	//	4,2,5,1,6,3,7    1,4,2,6,3,7,5
	for (int i = 0; i != 7; i++)
	{
		preorder.push_back(preodr[i]);
		inorder.push_back(inodr[i]);
		postorder.push_back(postodr[i]);
	}

	Solution slt;
	TreeNode *rslt = slt.buildTree(inorder, postorder);
	return 0;
}
