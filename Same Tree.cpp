///@file	Same Tree
/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

#include <iostream>
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
	///@brief	判断两棵二叉树是否一样
	///@param	p	第一棵树
	///@param	q	第二棵树
	///@return	如果两棵树相同，则返回true；否则返回false
	///@note	如果一个树前中后序遍历的序列和另一个树一样，则两棵树相同。因为节点值有可能重复，OJ报WA。
	bool isSameTree(TreeNode* p, TreeNode* q) {
		vector<int> pseq, qseq;
		preOrder(p, pseq);
		preOrder(q, qseq);
		if (!isSameVec(pseq, qseq))
			return false;

		pseq.clear();
		qseq.clear();
		inOrder(p, pseq);
		inOrder(q, qseq);
		if (!isSameVec(pseq, qseq))
			return false;

		pseq.clear();
		qseq.clear();
		afterOrder(p, pseq);
		afterOrder(q, qseq);
		if (!isSameVec(pseq, qseq))
			return false;

		return true;
	}
private:	
	///@brief	前序遍历二叉树
	///@param	root	树根
	///@param	遍历的节点值
	void preOrder(TreeNode* root, vector<int>& sequence)
	{
		sequence.push_back(root->val);

		if (root->left != nullptr)
		{
			preOrder(root->left, sequence);
		}

		if (root->right != nullptr)
		{
			preOrder(root->right, sequence);
		}
		return;
	}
	
	///@brief	中序遍历二叉树
	///@param	root	树根
	///@param	遍历的节点值
	void inOrder(TreeNode* root, vector<int>& sequence)
	{		
		if (root->left != nullptr)
		{
			inOrder(root->left, sequence);
		}

		sequence.push_back(root->val);

		if (root->right != nullptr)
		{
			inOrder(root->right, sequence);
		}
		return;
	}

	///@brief	后序遍历二叉树
	///@param	root	树根
	///@param	遍历的节点值
	void afterOrder(TreeNode* root, vector<int>& sequence)
	{
		if (root->left != nullptr)
		{
			afterOrder(root->left, sequence);
		}
		
		if (root->right != nullptr)
		{
			afterOrder(root->right, sequence);
		}

		sequence.push_back(root->val);
		return;
	}

	///@brief	判断两个int型vector是否相等
	///@param	a	数组1
	///@param	b	数组2
	///@return	如果相等则返回true，否则返回false
	bool isSameVec(vector<int> &a, vector<int> &b)
	{
		if (a.size() != b.size())
			return false;		

		for (vector<int>::size_type i = 0; i != a.size(); i++)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}
};

int main()
{
	return 0;
}