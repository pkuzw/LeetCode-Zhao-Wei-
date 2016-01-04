///@file	Construct Binary Tree from Inorder and Postorder Traversal
/*
Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
*/
///@author	zhaowei
///@date	2015.07.22
///@version	1.0

///@date	2015.08.25
///@version	2.0

///@date	2016.01.04
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

class Solution_v2 {
public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return buildRecur(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
	}
private:
	TreeNode* buildRecur(vector<int>& inorder, int ileft, int iright, vector<int>& postorder, int pleft, int pright)
	{
		if (ileft > iright || pleft > pright)	return nullptr;
		TreeNode* node = new TreeNode(postorder[pright]);
		int i = 0;
		for (i = ileft; i != inorder.size(); i++)
			if (inorder[i] == postorder[pright])	break;		
		
		node->left = buildRecur(inorder, ileft, i - 1, postorder, pleft, pleft + i - ileft - 1);
		node->right = buildRecur(inorder, i + 1, iright, postorder, pleft + i - ileft, pright - 1);
		return node;
	}
};

class Solution {
public:
	///@brief	通过中序遍历序列和后序遍历序列来重建二叉树
	///@param	inorder		中序遍历序列
	///@param	postorder	后序遍历序列
	///@return	返回重建的二叉树根节点
	///@note	1. 递归；2. 后序遍历序列的尾结点是当前子树的根节点，故先找后序序列的尾结点，然后在中序序列中寻找该节点，以便确定左右子树的长度；
	//			3. 本题与Construct Binary Tree from Inorder and Postorder Traversal类似，也是通过辅助递归函数来求解，参数的设置把根节点改动一下即可；
	//			4. 另外注意，postorder的左子树pright和右子树pleft实参都比上一题少1。
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return helper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
	}

	///@brief	辅助递归函数
	///@param	inorder	中序遍历序列
	///@param	il, ir	中序遍历序列的起始与终结下标
	///@param	postorder	后序遍历序列
	///@param	pl, pr	后序遍历序列的起始与终结下标
	///@return	重建的当前子树根节点
	TreeNode* helper(vector<int>& inorder, int il, int ir, vector<int>& postorder, int pl, int pr) {
		if (il > ir || pl > pr)	return nullptr;
		TreeNode* root = new TreeNode(postorder[pr]);
		int root_indx = il;
		while (root_indx <= ir) {
			if (inorder[root_indx] == root->val)		break;
			root_indx++;
		}
		root->left = helper(inorder, il, root_indx - 1, postorder, pl, pl + root_indx - il - 1);
		root->right = helper(inorder, root_indx + 1, ir, postorder, pl + root_indx - il, pr - 1);
		return root;
	}
};

int main()
{
	vector<int> preorder, inorder, postorder;
	int preodr[7] = {1,2,4,5,3,6,7};	//	
	int postodr[7] = {4,5,2,6,7,3,1};//{4,6,7,3,5,2,1};//     4,6,7,3,5,2,1
	int inodr[7] = {4,2,5,1,6,3,7};//{1,4,2,6,3,7,5};	//	    1,4,2,6,3,7,5
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
