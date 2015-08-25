///@file	Same Tree
/*
Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
*/
///@author	zhaowei
///@date	2015.07.21
///@version	1.0

///@date	2015.08.25
///@version	2.0

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	 };

class Solution_v1 {
public:
	///@brief	判断两棵二叉树是否一样
	///@param	p	第一棵树
	///@param	q	第二棵树
	///@return	如果两棵树相同，则返回true；否则返回false
	/*/@note	如果一个树前中后序遍历的序列和另一个树一样，则两棵树相同。因为节点值有可能重复，OJ报WA。
				在遍历二叉树时，如果节点的左子树为空，将INT_MIN入队，如果节点的右子树为空，则将INT_MAX入队。这样就能够解决节点值重复的问题。
	*/
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
		if (root == nullptr) return;

		sequence.push_back(root->val);

		if (root->left == nullptr)
			sequence.push_back(INT_MIN);
		else		
			preOrder(root->left, sequence);
		
		
		if (root->right == nullptr)
			sequence.push_back(INT_MAX);
		else
			preOrder(root->right, sequence);
		
		return;
	}
	
	///@brief	中序遍历二叉树，如果节点的左子树为空，将INT_MIN入队，如果节点的右子树为空，则将INT_MAX入队。这样就能够解决节点值重复的问题。
	///@param	root	树根
	///@param	遍历的节点值
	void inOrder(TreeNode* root, vector<int>& sequence)
	{			
		if (root == nullptr) return;

		if (root->left == nullptr)
			sequence.push_back(INT_MIN);
		else		
			preOrder(root->left, sequence);

		sequence.push_back(root->val);

		if (root->right == nullptr)
			sequence.push_back(INT_MAX);
		else
			preOrder(root->right, sequence);

		return;
	}

	///@brief	后序遍历二叉树
	///@param	root	树根
	///@param	遍历的节点值
	void afterOrder(TreeNode* root, vector<int>& sequence)
	{
		if (root == nullptr) return;

		if (root->left == nullptr)
			sequence.push_back(INT_MIN);
		else		
			preOrder(root->left, sequence);
				
		if (root->right == nullptr)
			sequence.push_back(INT_MAX);
		else
			preOrder(root->right, sequence);

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

class Solution {
public:
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (!p && !q)	return true;
		if ((!p && q) || (p && !q) || (p->val != q->val))	return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
};

int main()
{
	TreeNode *r1 = nullptr;
	TreeNode *n1 = new TreeNode(1);
	

	TreeNode *r2 = nullptr;

	Solution slt;
	cout << slt.isSameTree(r1, r2) << endl;

	Solution_v1 slt_v1;
	cout << slt_v1.isSameTree(r1, r2) << endl;
	return 0;
}