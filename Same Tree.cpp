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
	///@brief	�ж����ö������Ƿ�һ��
	///@param	p	��һ����
	///@param	q	�ڶ�����
	///@return	�����������ͬ���򷵻�true�����򷵻�false
	///@note	���һ����ǰ�к�����������к���һ����һ��������������ͬ����Ϊ�ڵ�ֵ�п����ظ���OJ��WA��
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
	///@brief	ǰ�����������
	///@param	root	����
	///@param	�����Ľڵ�ֵ
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
	
	///@brief	�������������
	///@param	root	����
	///@param	�����Ľڵ�ֵ
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

	///@brief	�������������
	///@param	root	����
	///@param	�����Ľڵ�ֵ
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

	///@brief	�ж�����int��vector�Ƿ����
	///@param	a	����1
	///@param	b	����2
	///@return	�������򷵻�true�����򷵻�false
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